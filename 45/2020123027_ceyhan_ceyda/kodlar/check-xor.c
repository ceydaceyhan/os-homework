#include <stdio.h>

        int main(int argc, char* argv[]) {
        if (argc != 2) {
        fprintf(stderr, "Usage: %s input-file\n", argv[0]);
        return 1;
        }

        const char* input_file = argv[1];

        // Okumak için giriş dosyasını açın
        FILE* fp = fopen(input_file, "r");
        if (fp == NULL) {
        perror(input_file);
        return 1;
        }

        // XOR tabanlı sağlama toplamını hesaplayın
        unsigned char checksum = 0;
        int c;
        while ((c = fgetc(fp)) != EOF) {
        checksum ^= c;
        }

        // Sağlama toplamını yazdır
        printf("%hhu\n", checksum);

        // Girdi dosyasını kapatın ve sonucu döndürün
        fclose(fp);
        return 0;
}