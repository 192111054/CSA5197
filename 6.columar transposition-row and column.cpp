#include <stdio.h>
#include <string.h>
void columnar Transposition Encrypt (char message [], char key []) 
{
int message Len = strlen (message);
int key Len = strlen (key);
int rows = (message Len + keyLen - 1) / keyLen; 
char transposition Table[rows][keyLen];
int i, j, k = 0;
for (i = 0; i < rows; i++) 
{
 for (j = 0; j < key Len; j++)
{
 if (k < message Len)
 transposition Table[i][j] = message[k++];
 else
transposition Table[i][j] = ' ';
}
}
for (i = 0; i < key Len; i++) 
{
 int col = key[i] - '0' - 1;
 for (j = 0; j < rows; j++) 
{
 printf("%c", transpositionTable[j][col]);
 }
}
 printf("\n");
}
int main() {
 char message[100], key[100];
 printf("Enter the message to encrypt: ");
 fgets(message, sizeof(message), stdin);
 printf("Enter the key for columnar transposition: ");
 fgets(key, sizeof(key), stdin);
 message [strcspn(message, "\n")] = '\0';
 key [strcspn(key, "\n")] = '\0';
 printf("\nEncrypted message: ");
 columnar Transposition Encrypt (message, key);
 return 0;
}

