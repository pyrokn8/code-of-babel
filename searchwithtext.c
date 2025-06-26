void modInverse(mpz_t result, const mpz_t p, const mpz_t n) {
    mpz_t a, b, x0, x1, q, temp_a, temp_x0;
    
    mpz_inits(a, b, x0, x1, q, temp_a, temp_x0, NULL);
    
    mpz_set(a, p);
    mpz_set(b, n);
    mpz_set_ui(x0, 1);
    mpz_set_ui(x1, 0);
    
    while (mpz_cmp_ui(b, 0) != 0) {
        mpz_fdiv_q(q, a, b);
        
        mpz_set(temp_a, a);
        mpz_set(a, b);
        mpz_mod(b, temp_a, b);
        
        mpz_set(temp_x0, x0);
        mpz_set(x0, x1);
        mpz_mul(x1, q, x1);
        mpz_sub(x1, temp_x0, x1);
    }
    
    // Ensure positive result
    mpz_add(result, x0, n);
    mpz_mod(result, result, n);
    
    mpz_clears(a, b, x0, x1, q, temp_a, temp_x0, NULL);
}

unsigned long long findI(unsigned long long k, const mpz_t p) {
    mpz_t result, n, pInv;
    mpz_inits(result, n, pInv, NULL);
    mpz_ui_pow_ui(n, 2, 64);// n is maximum possible unsigned long long integer type
    
    modInverse(pInv, p, n);
    mpz_mul_ui(result, pInv, k);
    mpz_mod(result, result, n);
    
    // Convert mpz to unsigned long long properly
    unsigned long long val = 0;
    if (mpz_fits_ulong_p(result)) {
        val = mpz_get_ui(result);
    } else {
        // Handle large numbers by extracting parts
        mpz_t temp;
        mpz_init(temp);
        
        // Get lower 32 bits
        mpz_fdiv_r_2exp(temp, result, 32);
        val = mpz_get_ui(temp);
        
        // Get upper 32 bits
        mpz_fdiv_q_2exp(temp, result, 32);
        val |= ((unsigned long long)mpz_get_ui(temp) << 32);
        mpz_clear(temp);
    }
    mpz_clears(result, n, pInv, NULL);
    return val;
}

unsigned long long randull() {
    unsigned long long result = 0;
    result |= (unsigned long long)rand() << 48;
    result |= (unsigned long long)rand() << 32;
    result |= (unsigned long long)rand() << 16;
    result |= (unsigned long long)rand();
    return result;
}

short randrang(short min, short max) {
    return (short)(rand() % (max - min + 1) + min);
}

char *searchwithtext(char *text[3], unsigned short numberofbytes, mpz_t *seed) {
    unsigned long long k, i;
    unsigned char bytes[numberofbytes];

    char *lineofcode = malloc(19+2+24);
    for (short i = 0; i < numberofbytes; i++) {
        bytes[i] = hextobyte(text[i]);
    }
    
    k = randull();

    unsigned char *ptr = (unsigned char *)&k;
    for (short i = randrang(numberofbytes-1, 8-1), j = 0; j < numberofbytes; i--, j++) {
        ptr[i] = bytes[j];
    }

    i = findI(k, *seed);

    strcpy(lineofcode, longtohex(i));
    strcat(lineofcode, ": ");

    for (int index = 7; index >= 0; index--) {
        char *hex = bytetohex(ptr[index]);
        strcat(lineofcode, hex);
        strcat(lineofcode, " ");
        free(hex);
    }
    lineofcode[45] = '\0';
    return lineofcode;
}