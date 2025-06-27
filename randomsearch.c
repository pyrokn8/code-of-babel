char* randomsearch(mpz_t *seed) {
    unsigned long long i = randull();
    return searchwithkey(i, seed);
}

// char* randomsearch(mpz_t *seed) {
//     unsigned long long k = randull();
//     unsigned long long i = findI(k, *seed);

//     char *lineofcode = malloc(45*2+1);
//     strcpy(lineofcode, longtohex(i));
//     strcat(lineofcode, ": ");

//     unsigned char *ptr = (unsigned char *)&k;
//     for (int index = 7; index >= 0; index--) {
//         char *hex = bytetohex(ptr[index]);
//         strcat(lineofcode, hex);
//         strcat(lineofcode, " ");
//         free(hex);
//     }

//     strcat(lineofcode, "\n");
//     strcat(lineofcode, searchwithkey(i, seed));

//     lineofcode[91] = '\0';
//     return lineofcode;
// }