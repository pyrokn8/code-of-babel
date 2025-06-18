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