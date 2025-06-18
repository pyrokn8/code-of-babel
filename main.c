#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>
#include <gmp.h>

#include "./hex.c"
#include "./help.c"
#include "./searchwithkey.c"
#include "./searchwithtext.c"

int prime(int n) {
    // All prime numbers are odd except two
    if (n & 1)
        n -= 2;
    else
        n--;
 
    int i, j;
    for (i = n; i >= 2; i -= 2) {
        if (i % 2 == 0)
            continue;
        for (j = 3; j <= sqrt(i); j += 2) {
            if (i % j == 0)
                break;
        }
        if (j > sqrt(i))
            return i;
    }
 
    // It will only be executed when n is 3
    return 2;
}


unsigned long long getseed(char *argv[]) {
    unsigned long long seed;
    char path[50];
    strcpy(path, argv[0]);
    path[strlen(path)-7] = '\0';
    strcat(path, "seed.txt");
    // Open a file in read mode
    FILE *fptr = fopen(path, "r");
    // Print some text if the file does not exist
    if (fptr == NULL) {
        printf("Not able to open the seed file. Creating a new one instead...\n");
        fptr = fopen(path, "w");
        seed = prime(rand());// find the closest prime number
        fprintf(fptr, "%lld", seed);
    } else {
        fscanf(fptr, "%llu", &seed);
    }
    // Close the file
    fclose(fptr);
    return seed;
}


int main(int argc, char *argv[]) {
    srand(time(NULL));
    unsigned long long seed = getseed(argv);

    printf(" __\n");
    printf("/  \\ The Library of Babel by pyrokn8\n");
    printf("\\__/ Current seed: %llu\n\n",seed);

    if (argc < 2) {
        printf("You have not entered any arguments...\n");
        help();
        return 1; 
    }

    char swt[5] = "-swt\0";
    char swk[5] = "-swk\0";
    char rand[3] = "-r\0";
    if (strcmp(argv[1], swt) == 0) {
        if (argc-2 > 8) {
            printf("You can't input that many hexadecimal numbers!");
        } else {
            char *bytes[3];
            for (short i = 0; i < argc-2; i++) {
                // printf("%d, %d\n", i+2, argc);
                bytes[i] = argv[i+2];// strcpy(bytes[i], argv[i+2]);
                strcat(bytes[i], "\0");
                // printf("%s %s %d\n", bytes[i], argv[i+2], i);
            }
            char *line = searchwithtext(bytes, (unsigned short)argc-2, seed);
            printf("%s\n", line);
            free(line);
        }
    } else if (strcmp(argv[1], swk) == 0) {
        unsigned long long key;
        if (argv[2][1] == 'x') {
            key = hextolong(argv[2]);// Convert string hexadecimal input to unsigned long long
        } else {
            key = strtoull(argv[2], nullptr, 10); // Convert string number to unsigned long long
        }
        // printf("Input Key: %llu\n", key);
        if (key > ULLONG_MAX-1 || key == 0) {
            printf("You can't input the number %llu!\n", key);
        } else {
            char *line = searchwithkey(key, seed);
            printf("%s\n", line);
            free(line);
        }
    } else if (strcmp(argv[1], rand) == 0) {
        // unsigned long long key = randomsearch();
        // printf("Key: %llu\n", key);
    } else {
        printf("You have not entered any valid arguments...\n");
    }
    

    return 0; // Return success
}