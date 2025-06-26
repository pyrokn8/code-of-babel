unsigned long long findk(unsigned long long i, const mpz_t p) {
    mpz_t result, n;
    mpz_inits(result, n, NULL);
    mpz_ui_pow_ui(n, 2, 64);// n is maximum possible unsigned long long integer type
    mpz_mul_ui(result, p, i);
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

    // return mpz_get_ui(result);
    mpz_clears(result, n, NULL);
    return val;
}
/*
I think p needs to be greater than n for better psudorandomness
since when i = 1, i * p % n = p
however this is not possible since n is at the 64 bit limit

If you are reading this then you are cool :)
*/

char *searchwithkey(unsigned long long key, mpz_t *seed) {
    // https://youtu.be/WFFi9zVtvsw?t=308
    unsigned long long k = findk(key, *seed);
    unsigned char *ptr = (unsigned char *)&k;
    char *lineofcode = malloc(19+2+24);
    strcpy(lineofcode, longtohex(key));
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