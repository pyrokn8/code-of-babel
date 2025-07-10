void modInverse(mpz_t result, const mpz_t p, const mpz_t n) {
    // Extended Euclidean algorithm to find the modular inverse of p mod n
    // https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
    mpz_t a, b, x0, x1, q, temp, temp2;
    mpz_inits(a, b, x0, x1, q, temp, temp2, NULL);

    mpz_set(a, p);
    mpz_set(b, n);
    mpz_set_ui(x0, 1);
    mpz_set_ui(x1, 0);

    while (mpz_cmp_ui(b, 0) != 0) {
        mpz_fdiv_q(q, a, b); // q = a / b

        // (a, b) = (b, a % b)
        mpz_set(temp, b);
        mpz_mod(b, a, b);
        mpz_set(a, temp);

        // (x0, x1) = (x1, x0 - q*x1)
        mpz_mul(temp, q, x1);      // temp = q * x1
        mpz_sub(temp2, x0, temp);  // temp2 = x0 - temp
        mpz_set(x0, x1);
        mpz_set(x1, temp2);
    }

    // Ensure result is positive
    if (mpz_sgn(x0) < 0) {
        mpz_add(x0, x0, n);
    }

    mpz_set(result, x0);

    mpz_clears(a, b, x0, x1, q, temp, temp2, NULL);
}

unsigned long long findI(unsigned long long k, const mpz_t p) {
    // https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
    // This function finds the value of i such that i = (k * pow(p, -1, n)) % n
    // k = (i * p) mod n
    // i = (k * p^-1) mod n
    mpz_t result, n, pInv, k_mpz;
    mpz_inits(result, n, pInv, k_mpz, NULL);
    mpz_ui_pow_ui(n, 2, 64);// n is maximum possible unsigned long long integer type
    ulltompz(k_mpz, k); // Convert unsigned long long to mpz_t
    modInverse(pInv, p, n);
    mpz_mul(result, pInv, k_mpz);
    mpz_mod(result, result, n);// i = (k * pow(p, -1, n)) % n
    unsigned long long i = mpztoull(result);// Convert mpz to unsigned long long properly
    mpz_clears(result, n, pInv, k_mpz, NULL);
    return i;
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

char *searchwithtext(char *text[3], unsigned short numberofbytes, mpz_t *seed, bool decompile, bool store) {
    unsigned long long k, i;
    unsigned char bytes[numberofbytes];

    char *lineofcode = malloc(19+2+24);
    for (short i = 0; i < numberofbytes; i++) {
        bytes[i] = hextobyte(text[i]);
    }
    
    k = randull();

    unsigned char *ptr = (unsigned char *)&k;
    for (short i = randrang(numberofbytes-1, 7), j = 0; j < numberofbytes; i--, j++) {
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
    lineofcode[44] = '\n';
    if (decompile) {
        strcat(lineofcode, "\nAssembly Code Conversion:\n");
        strcat(lineofcode, disasseble(k));
    }
    strcat(lineofcode, "\0");

    if (store) {
        FILE *fptr = fopen("code.bin", "ab");
        if (fptr != NULL) {
            fwrite(&k, sizeof(unsigned long long), 1, fptr);
        }
        fclose(fptr);
    }

    return lineofcode;
}