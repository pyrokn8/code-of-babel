void help() {
    printf("Usage: cob [options] -swt <byte> | -swk <key> | -r\n");
    printf("\nMain commands:\n");
    printf("  -swt <byte>  Search with text (up to 8 bytes in hex format)\n");
    printf("  -swk <key>   Search with key (decimal or hex with 0x prefix)\n");
    printf("  -r           Random search\n");
    printf("\nAdditional options:\n");
    printf("  -asm         Show disassembled code\n");
    printf("  -save        Store machine code to code.bin\n");
    printf("\nExamples:\n");
    printf("  cob -swt E1 A0 00 00 -asm  # Search for a NOP instruction\n");//https://en.wikipedia.org/wiki/NOP_(code)
    printf("  cob -swk 0xff              # Search by specific key\n");
    printf("  cob -asm -save -r          # Random search with assembly and binary output\n");
}