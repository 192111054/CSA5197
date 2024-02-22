#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

void generateCMACSubkeys(const unsigned char *key, unsigned char *k1, unsigned char *k2) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);

    unsigned char const_Rb = 0x87; // Rb constant for CMAC
    unsigned char L[16];
    memset(L, 0, sizeof(L));

    AES_encrypt(L, k1, &aesKey);

    if (k1[0] & 0x80) {
        for (int i = 0; i < AES_BLOCK_SIZE; i++) {
            k1[i] = (k1[i] << 1) | ((k1[i + 1] & 0x80) >> 7);
        }
    } else {
        for (int i = 0; i < AES_BLOCK_SIZE; i++) {
            k1[i] = (k1[i] << 1);
        }
    }

    if (L[0] & 0x80) {
        for (int i = 0; i < AES_BLOCK_SIZE; i++) {
            L[i] = (L[i] << 1) | ((L[i + 1] & 0x80) >> 7);
        }
    } else {
        for (int i = 0; i < AES_BLOCK_SIZE; i++) {
            L[i] = (L[i] << 1);
        }
    }

    if (k1[0] & 0x80) {
        k1[AES_BLOCK_SIZE - 1] ^= const_Rb;
    }

    memcpy(k2, k1, AES_BLOCK_SIZE);

    if (k2[0] & 0x80) {
        for (int i = 0; i < AES_BLOCK_SIZE; i++) {
            k2[i] = (k2[i] << 1) | ((k2[i + 1] & 0x80) >> 7);
        }
    } else {
        for (int i = 0; i < AES_BLOCK_SIZE; i++) {
            k2[i] = (k2[i] << 1);
        }
    }

    if (k1[0] & 0x80) {
        k2[AES_BLOCK_SIZE - 1] ^= const_Rb;
    }
}

int main() {
    const unsigned char key[16] = "0123456789abcdef";
    unsigned char k1[AES_BLOCK_SIZE];
    unsigned char k2[AES_BLOCK_SIZE];

    generateCMACSubkeys(key, k1, k2);

    printf("K1 (hex): ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02X", k1[i]);
    }
    printf("\n");

    printf("K2 (hex): ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02X", k2[i]);
    }
    printf("\n");

    return 0;
}
