#include <stdio.h>
        #include <stdlib.h>

        #define BLOCK_SIZE 4096

        int main(int argc, char* argv[]) {
        // Bağımsız değişken sayısının doğru olup olmadığını kontrol edin
        if (argc != 3) {
        printf("Usage: create-csum <input_file> <output_file>\n");
        return 1;
        }

        // Girdi dosyasını salt okunur modda açın
        FILE* input_file = fopen(argv[1], "r");
        if (input_file == NULL) {
        printf("Error: could not open input file\n");
        return 1;
        }

        // Çıktı dosyasını salt yazılır modunda açın
        FILE* output_file = fopen(argv[2], "w");
        if (output_file == NULL) {
        printf("Error: could not open output file\n");
        return 1;
        }

        // Arabellek için bellek ayırma
        char* buffer = (char*) malloc(BLOCK_SIZE);

        // Girdi dosyasını BLOCK_SIZE baytlık bloklar halinde oku
        // ve her blok için sağlama toplamını hesaplayın
        int num_read;
        while ((num_read = fread(buffer, 1, BLOCK_SIZE, input_file)) > 0) {
        // Sağlama toplamını hesapla
        unsigned char checksum = 0;
        for (int i = 0; i < num_read; i++) {
        checksum += buffer[i];
        }

        // Çıktı dosyasına sağlama toplamını yazın
        fwrite(&checksum, 1, 1, output_file);
        }

        // Kapat
        free(buffer);
        fclose(input_file);
        fclose(output_file);

        return 0;
        }