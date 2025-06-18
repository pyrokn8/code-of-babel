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

char *searchwithtext(char *text[3], unsigned short numberofbytes, unsigned long long seed) {
    unsigned long long k, i;
    unsigned char bytes[numberofbytes];

    unsigned long long n = ULLONG_MAX;
    unsigned long long p = seed;

    char *lineofcode = malloc(19+2+24);
    for (short i = 0; i < numberofbytes; i++) 
    {  bytes[i] = hextobyte(text[i]);  }
    
    k = randull();

    unsigned char *ptr = (unsigned char *)&k;
    for (short i = randrang(numberofbytes-1, 8-1), j = 0; j < numberofbytes; i--, j++) {
        ptr[i] = bytes[j];
    }

    i = (unsigned long long)((k % n) / p);

    // for (unsigned long long pos = (ULLONG_MAX/2)+1, neg = ULLONG_MAX/2; pos != ULLONG_MAX || neg != 0; pos++, neg--) {
    //     if (k == pos * p % n) {
    //         i = pos;
    //         break;
    //     }
    //     if (k == neg * p % n) {
    //         i = neg;
    //         break;
    //     }
    // }
    // printf("%f\n", (double)(k % n) / p);

    /*
    k = i * p % n
    i = (k % n) / p
    It is posiable to find i with k, however k must equal i * p % n.
    These two equations cannot be found in the opisite way (k first, then i).
    I'm losing my mind over this since it's like the chicken and egg question.
    Which one came first, the chicken or the egg?
    In the searchwithkey context I can prove i, but not in this context. :(

    i = k / p since k < n
    */

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