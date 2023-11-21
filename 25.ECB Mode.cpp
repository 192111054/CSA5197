#include <stdio.h>
#include <string.h>
void encryptBlock(char* block) {
    printf("Encrypting block: %s\n", block);
}
void ecbEncrypt(char* message, int block_size) {
    int message_length = strlen(message);
    int padding = block_size - (message_length % block_size);
    if (padding != block_size) {
        for (int i = 0; i < padding; ++i) {
            message[message_length + i] = ' ';
        }
        message[message_length + padding] = '\0';
    }
    for (int i = 0; i < message_length; i += block_size) {
        encryptBlock(message + i);
    }
}

int main() {
    char message[] = "Hello, ECB Mode!";
    int block_size = 8; 
    ecbEncrypt(message, block_size);

    return 0;
}

