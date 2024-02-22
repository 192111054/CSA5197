#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

void encryptAES_ECB(const unsigned char *input, const unsigned char *key, unsigned char *output, size_t length) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);

    for (size_t i = 0; i < length; i += AES_BLOCK_SIZE) {
        AES_encrypt(input + i, output + i, &aesKey);
    }
}

void encryptAES_CBC(const unsigned char *input, const unsigned char *key, const unsigned char *iv, unsigned char *output, size_t length) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);

    unsigned char xorBlock[AES_BLOCK_SIZE];
    memcpy(xorBlock, iv, AES_BLOCK_SIZE);

    for (size_t i = 0; i < length; i += AES_BLOCK_SIZE) {
        for (int j = 0; j < AES_BLOCK_SIZE; j++) {
            input[i + j] ^= xorBlock[j];
        }
        AES_encrypt(input + i, output + i, &aesKey);
        memcpy(xorBlock, output + i, AES_BLOCK_SIZE);
    }
}

void encryptAES_CFB(const unsigned char *input, const unsigned char *key, const unsigned char *iv, unsigned char *output, size_t length) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);

    unsigned char xorBlock[AES_BLOCK_SIZE];
    memcpy(xorBlock, iv, AES_BLOCK_SIZE);

    for (size_t i = 0; i < length; i += AES_BLOCK_SIZE) {
        AES_encrypt(xorBlock, xorBlock, &aesKey);
        for (int j = 0; j < AES_BLOCK_SIZE; j++) {
            output[i + j] = input[i + j] ^ xorBlock[j];
        }
        memcpy(xorBlock, output + i, AES_BLOCK_SIZE);
    }
}

int main() {
    // Your plaintext, key, and IV
    const char *plaintext = "This is a simple example of ECB, CBC, and CFB modes.";
    const unsigned char key[16] = "0123456789abcdef";
    const unsigned char iv[16] = "0123456789abcdef";

    size_t plaintextLen = strlen(plaintext);
    unsigned char ciphertext[plaintextLen];

    // Ensure the plaintext length is a multiple of AES_BLOCK_SIZE
    size_t paddedLen = ((plaintextLen + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    // Pad the plaintext if necessary
    unsigned char paddedPlaintext[paddedLen];
    memcpy(paddedPlaintext, plaintext, plaintextLen);
    memset(paddedPlaintext + plaintextLen, 0, paddedLen - plaintextLen);

    // Encrypt in ECB mode
    encryptAES_ECB(paddedPlaintext, key, ciphertext, paddedLen);
    printf("ECB Ciphertext (hex): ");
    for (size_t i = 0; i < paddedLen; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    // Encrypt in CBC mode
    encryptAES_CBC(paddedPlaintext, key, iv, ciphertext, paddedLen);
    printf("CBC Ciphertext (hex): ");
    for (size_t i = 0; i < paddedLen; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    // Encrypt in CFB mode
    encryptAES_CFB(paddedPlaintext, key, iv, ciphertext, paddedLen);
    printf("CFB Ciphertext (hex): ");
    for (size_t i = 0; i < paddedLen; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
