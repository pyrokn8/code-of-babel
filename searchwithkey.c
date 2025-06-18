
char *searchwithkey(unsigned long long key, unsigned long long seed) {
    // https://youtu.be/WFFi9zVtvsw?t=308
    unsigned long long i = key;// user input page number
    unsigned long long p = seed;//any prime number
    unsigned long long n = ULLONG_MAX;// n is maximum possible unsigned long long interger type
    unsigned long long k = i * p % n;// where i and k between 0 and n
    // printf("%f\n", (double)(k % n) / p);
    /*
    I think p needs to be greater than n for better psudorandomness
    since when i = 1, i * p % n = p
    however this is not possible since n is at the 64 bit limit

    If you are reading this then you are cool :)
    */

    unsigned char *ptr = (unsigned char *)&k;
    char *lineofcode = malloc(19+2+24);
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


    /*
    find total length of output string
    16^x=2^64
    log16(2^64)=x
    x=16

    total combinations:
    16^16=2^64
    */
}