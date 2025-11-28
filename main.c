#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <gmp.h>
#include <capstone/capstone.h>

#include "./convert.c"
#include "./help.c"
#include "./searchwithkey.c"
#include "./searchwithtext.c"
#include "./randomsearch.c"

void randomprime(mpz_t *result) {
    mpz_t n;
    mpz_init(n);
    mpz_ui_pow_ui(*result, 2, 64); // result is maximum possible unsigned long long integer type

    unsigned long long random_num = randull();// random number in the range [0, 2^64]
    ulltompz(n, random_num); // Convert unsigned long long to mpz_t    
    mpz_add(*result, *result, n);
    mpz_nextprime(*result, *result);

    mpz_clear(n);
}

mpz_t* getseed() {
    mpz_t *seed = malloc(sizeof(mpz_t));
    mpz_init(*seed);
    
    FILE *fptr = fopen("./seed.txt", "r");
    if (fptr == NULL) {
        printf("Not able to open the seed file. Creating a new one instead...\n");
        fptr = fopen("./seed.txt", "w");
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
    mpz_t *seed = getseed();
    
    printf(" __\n");
    printf("/  \\ The Code of Babel by pyrokn8\n");
    gmp_printf("\\__/ Current seed: %Zd\n\n", *seed);

    if (argc < 2) {
        printf("You have not entered any arguments...\n");
        help();
        return 1; 
    }

    const char swt[5] = "-swt\0";// change these to search with code and search with index
    const char swk[5] = "-swk\0";
    const char rand[3] = "-r\0";
    const char assembly[5] = "-asm\0";
    const char save[6] = "-save\0";

    bool decompile = false;
    bool store = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], assembly) == 0) {
            decompile = true;
            for (int j = i; j < argc - 1; j++) {
                argv[j] = argv[j + 1];
            }
            argc--;
        }
        if (strcmp(argv[i], save) == 0) {
            store = true;
            for (int j = i; j < argc - 1; j++) {
                argv[j] = argv[j + 1];
            }
            argc--;
        }
    }
    // check/make if code.asm exists
    if (decompile) {
        FILE *asmfile = fopen("code.asm", "r");
        if (asmfile == NULL) {
            printf("code.asm does not exist. Creating a new one...\n");
            asmfile = fopen("code.asm", "w");
            fprintf(asmfile, ".global _start\n\n_start:\n");
            if (asmfile == NULL) {
                printf("Failed to create code.asm file.\n");
                return 1;
            }
            fclose(asmfile);
        } else {
            fclose(asmfile);
        }
    }

    if (strcmp(argv[1], swt) == 0) {// search with text
        if (argc-2 > 8) {
            printf("You can't input that many hexadecimal numbers!");
        } else {
            char *bytes[3];
            for (short i = 0; i < argc-2; i++) {
                bytes[i] = argv[i+2];
                strcat(bytes[i], "\0");
            }
            char *line = searchwithtext(bytes, (unsigned short)argc-2, seed, decompile, store);
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
        char *line = searchwithkey(key, seed, decompile, store);
        printf("%s\n", line);
        free(line);
    } else if (strcmp(argv[1], rand) == 0) {// random search
        char *line = randomsearch(seed, decompile, store);
        printf("%s\n", line);
        free(line);
    } else {
        printf("You have not entered any valid arguments...\n");
    }
    
    return 0;
}