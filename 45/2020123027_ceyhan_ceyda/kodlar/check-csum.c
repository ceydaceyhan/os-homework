#include <stdio.h>
        #include <stdlib.h>

        #define BLOCK_SIZE 4096 // Bayt cinsinden her bloğun boyutu

        int main(int argc, char* argv[]) {
        if (argc != 3) {
        fprintf(stderr, "Usage: %s input-file checksum-file\n", argv[0]);
        return 1;
        }

        const char* input_file = argv[1];
        const char* checksum_file = argv[2];

        // Okumak için giriş dosyasını açın
        FILE* fp_in = fopen(input_file, "r");
        if (fp_in == NULL) {
        perror(input_file);
        return 1;
        }

        // Okumak için sağlama toplamı dosyasını açın
        FILE* fp_chk = fopen(checksum_file, "r");
        if (fp_chk == NULL) {
        perror(checksum_file);
        fclose(fp_in);
        return 1;
        }

        // Girdi dosyasından okuma blokları için bir arabellek tahsis edin
        unsigned char* block = malloc(BLOCK_SIZE);
        if (block == NULL) {
        perror("malloc");
        fclose(fp_in);
        fclose(fp_chk);
        return 1;
        }

        // Girdi dosyasından blokları okuyun, sağlama toplamlarını hesaplayın ve karşılaştırın
        // sağlama toplamı dosyasından saklanan sağlama toplamlarının sonuçları
        int c;
        while ((c = fread(block, 1, BLOCK_SIZE, fp_in)) > 0) {
        // Geçerli blok için sağlama toplamını hesapla
        unsigned char checksum = 0;
        for (int i = 0; i < c; i++) {
        checksum ^= block[i];
        }

        // Sağlama toplamı dosyasından saklanan sağlama toplamını okuyun
        int stored_checksum = fgetc(fp_chk);
        if (stored_checksum == EOF) {
        fprintf(stderr, "Error: checksum file is too short\n");
        break;
        }

        // Hesaplanan sağlama toplamını saklanan sağlama toplamıyla karşılaştırın
        if (checksum != stored_checksum) {
        fprintf(stderr, "Error: checksum mismatch at offset %ld\n",
        ftell(fp_in) - BLOCK_SIZE);
        break;
        }
        }

        // Sağlama toplamı dosyasında kalan sağlama toplamı olup olmadığını kontrol edin
        if (fgetc(fp_chk) != EOF) {
        fprintf(stderr, "Error: checksum file is too long\n");
        }

        // Kapat ve sonucu döndür
        free(block);
        fclose(fp_in);
        fclose(fp_chk);
        return 0;
}