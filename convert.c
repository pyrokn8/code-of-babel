char *longtohex(unsigned long long number) {
    char hexdecimal[16] = "0123456789ABCDEF";
    char *hex_string = malloc(17);
    for (int i = 15; i >= 0; i--) {
        hex_string[i] = hexdecimal[number % 16];
        number /= 16;
    }
    hex_string[16] = '\0'; // Null-terminate the string
    char *temp = malloc(19);
    strcpy(temp, "0x");
    strcat(temp, hex_string);
    free(hex_string);
    return temp;
}


char *bytetohex(unsigned char number) {
    char hexdecimal[16] = "0123456789ABCDEF";
    char *hex_string = malloc(3);
    for (int i = 1; i >= 0; i--) {
        hex_string[i] = hexdecimal[number % 16];
        number /= 16;
    }
    hex_string[2] = '\0';
    // printf("%s\n", hex_string);
    return hex_string;
}

unsigned long long hextolong(char *hex) {
    char hexdecimal[16] = "0123456789ABCDEF";
    unsigned long long byte = 0;
    for (int i = 2; i < strlen(hex); i++) {
        for (int j = 0; j < 16; j++) {
            if (hex[i] == hexdecimal[j]) {
                byte = byte * 16 + j;
                break;
            }
        }
    }
    return byte;
}

unsigned char hextobyte(char hex[3]) {
    char hexdecimal[16] = "0123456789ABCDEF";
    unsigned char byte = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 16; j++) {
            if (hex[i] == hexdecimal[j]) {
                byte = byte * 16 + j;
                break;
            }
        }
    }
    return byte;
}

unsigned long long mpztoull(mpz_t p) {
    // Convert mpz to unsigned long long properly
    assert(mpz_cmp_ui(p, 0) >= 0 && mpz_sizeinbase(p, 2) <= 64);
    unsigned long long val = 0;
    if (mpz_fits_ulong_p(p)) {
        val = mpz_get_ui(p);
    } else {
        // Handle large numbers by extracting parts
        mpz_t temp;
        mpz_init(temp);
        
        // Get lower 32 bits
        mpz_fdiv_r_2exp(temp, p, 32);
        val = mpz_get_ui(temp);
        
        // Get upper 32 bits
        mpz_fdiv_q_2exp(temp, p, 32);
        val |= ((unsigned long long)mpz_get_ui(temp) << 32);
        mpz_clear(temp);
    }
    return val;
}


void ulltompz(mpz_t result, unsigned long long val) {
    // GMP representation: count = 1 value, order = -1 (LSB first), size = 8 bytes
    mpz_import(result, 1, -1, sizeof(val), 0, 0, &val);
}