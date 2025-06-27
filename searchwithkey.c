unsigned long long findk(unsigned long long i, const mpz_t p) {
    mpz_t result, n, i_mpz;
    mpz_inits(result, n, i_mpz, NULL);
    mpz_ui_pow_ui(n, 2, 64);// n is maximum possible unsigned long long integer type
    ulltompz(i_mpz, i); // Convert unsigned long long to mpz_t
    mpz_mul(result, p, i_mpz);// result = i * p
    mpz_mod(result, result, n);// k = i * p % n
    return mpztoull(result);// Convert mpz to unsigned long long properly
    mpz_clears(result, n, i_mpz, NULL);
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