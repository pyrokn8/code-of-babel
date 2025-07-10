unsigned long long findk(unsigned long long i, const mpz_t p) {
    mpz_t result, n, i_mpz;
    mpz_inits(result, n, i_mpz, NULL);
    mpz_ui_pow_ui(n, 2, 64);// n is maximum possible unsigned long long integer type
    ulltompz(i_mpz, i); // Convert unsigned long long to mpz_t
    mpz_mul(result, p, i_mpz);// result = i * p
    mpz_mod(result, result, n);// k = i * p % n
    unsigned long long k = mpztoull(result);// Convert mpz to unsigned long long properly
    mpz_clears(result, n, i_mpz, NULL);
    return k;
}
/*
I think p needs to be greater than n for better psudorandomness
since when i = 1, i * p % n = p
however this is not possible since n is at the 64 bit limit

If you are reading this then you are cool :)
*/

char *searchwithkey(unsigned long long key, mpz_t *seed, bool decompile, bool store) {
    // https://youtu.be/WFFi9zVtvsw?t=308
    unsigned long long k = findk(key, *seed);
    unsigned char *ptr = (unsigned char *)&k;
    char *lineofcode = malloc(45+212);

    strcpy(lineofcode, longtohex(key));
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