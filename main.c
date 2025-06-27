#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <gmp.h>
#include <assert.h>

#include "./convert.c"
#include "./help.c"
#include "./searchwithkey.c"
#include "./searchwithtext.c"
#include "./randomsearch.c"

void randomprime(mpz_t *result) {
    mpz_t n;
    mpz_init(n);
    mpz_ui_pow_ui(n, 2, 64); // n is maximum possible unsigned long long integer type

    unsigned long long random_num = randull();// random number in the range [0, 2^64]
    ulltompz(n, random_num); // Convert unsigned long long to mpz_t    
    mpz_set(*result, n);
    mpz_nextprime(*result, *result);

    mpz_clear(n);
}

mpz_t* getseed(char *argv[]) {
    mpz_t *seed = malloc(sizeof(mpz_t));
    mpz_init(*seed);
    
    char path[50];
    strcpy(path, argv[0]);
    path[strlen(path)-7] = '\0';
    strcat(path, "seed.txt");
    
    FILE *fptr = fopen(path, "r");
    if (fptr == NULL) {
        printf("Not able to open the seed file. Creating a new one instead...\n");
        fptr = fopen(path, "w");
        mpz_t n, gcd;
        mpz_inits(n, gcd, NULL);
        mpz_ui_pow_ui(n, 2, 64);
        do {
            randomprime(seed); // Generate a random prime number as the seed
            mpz_gcd(gcd, *seed, n);// Extended Euclidean algorithm only works if gcd(seed, n) == 1
        } while (mpz_cmp_ui(gcd, 1) != 0);
        mpz_clears(n, gcd, NULL);
        gmp_fprintf(fptr, "%Zd", *seed);
    } else {
        gmp_fscanf(fptr, "%Zd", *seed);
    }
    fclose(fptr);
    return seed;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    mpz_t *seed = getseed(argv);
    
    printf(" __\n");
    printf("/  \\ The Library of Babel by pyrokn8\n");
    gmp_printf("\\__/ Current seed: %Zd\n\n", *seed);

    if (argc < 2) {
        printf("You have not entered any arguments...\n");
        help();
        return 1; 
    }

    const char swt[5] = "-swt\0";
    const char swk[5] = "-swk\0";
    const char rand[3] = "-r\0";
    if (strcmp(argv[1], swt) == 0) {// search with text
        if (argc-2 > 8) {
            printf("You can't input that many hexadecimal numbers!");
        } else {
            char *bytes[3];
            for (short i = 0; i < argc-2; i++) {
                bytes[i] = argv[i+2];
                strcat(bytes[i], "\0");
            }
            char *line = searchwithtext(bytes, (unsigned short)argc-2, seed);
            printf("%s\n", line);
            free(line);
        }
    } else if (strcmp(argv[1], swk) == 0) {// search with key
        unsigned long long key;
        if (argv[2][1] == 'x') {
            key = hextolong(argv[2]);// Convert string hexadecimal input to unsigned long long
        } else {
            key = strtoull(argv[2], NULL, 10); // Convert string number to unsigned long long
        }
        char *line = searchwithkey(key, seed);
        printf("%s\n", line);
        free(line);
    } else if (strcmp(argv[1], rand) == 0) {// random search
        char *line = randomsearch(seed);
        printf("%s\n", line);
        free(line);
    } else {
        printf("You have not entered any valid arguments...\n");
    }
    
    return 0;
}