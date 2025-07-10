static const char hexdecimal[16] = "0123456789ABCDEF";

char *longtohex(unsigned long long number) {
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
    char *hex_string = malloc(3);
    for (int i = 1; i >= 0; i--) {
        hex_string[i] = hexdecimal[number % 16];
        number /= 16;
    }
    hex_string[2] = '\0';
    return hex_string;
}

unsigned long long hextolong(char *hex) {
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

char *disasseble(unsigned long long k) {
    // Disassemble a 4-byte ARM instruction from an unsigned long long value
    csh handle;
    cs_insn *insn;
    size_t count;
    
    if (cs_open(CS_ARCH_ARM, CS_MODE_ARM, &handle) != CS_ERR_OK) {
        return "Error opening Capstone\n";
    }
    
    unsigned char *code = (unsigned char *)&k;

    count = cs_disasm(handle, code, sizeof(code), 0x0, 0, &insn);
    if (count > 0) {
        char *result = malloc(212);
        for (short i = 0; i < 212; i++) {result[i] = '\0';}
        
        FILE *asmfile = fopen("code.asm", "a");
		for (short j = 0; j < count; j++) {
            char *temp = malloc(212);
            snprintf(temp, 212, "\t%d: %s %s\n", j+1, insn[j].mnemonic, insn[j].op_str);
            strcat(result, temp);
            free(temp);
            if (asmfile != NULL) {
                fprintf(asmfile, "\t%s %s\n", insn[j].mnemonic, insn[j].op_str);
            } 
		}
        fclose(asmfile);
        cs_free(insn, count);
        cs_close(&handle);
        return result;
    } else {
        cs_close(&handle);
        return "Failed to disassemble given code!\n"; // Failed to disassemble
    }
}