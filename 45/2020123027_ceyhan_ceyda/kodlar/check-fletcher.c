#include <stdio.h>
        #include <stdlib.h>

        int main(int argc, char* argv[]) {
        if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
        }

        // Okumak için giriş dosyasını açın.
        const char* input_file = argv[1];
        FILE* fp = fopen(input_file, "r");
        if (!fp) {
        perror(input_file);
        return 1;
        }

        // Fletcher sağlama toplamını hesaplayın.
        unsigned char sum1 = 0;
        unsigned char sum2 = 0;
        int c;
        while ((c = fgetc(fp)) != EOF) {
        sum1 = (sum1 + (unsigned char)c) % 255;
        sum2 = (sum2 + sum1) % 255;
        }

        // Sağlama toplamını stdout'a yazdırın.
        printf("%02X%02X\n", sum2, sum1);

        // Giriş dosyasını kapatın ve başarıyla geri dönün.
        fclose(fp);
        return 0;
}