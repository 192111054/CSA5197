from cryptography.hazmat.primitives import padding
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
import os

def add_padding(data, block_size):
    padder = padding.PKCS7(block_size * 8).padder()
    return padder.update(data) + padder.finalize()

def remove_padding(padded_data):
    unpadder = padding.PKCS7(128).unpadder()
    return unpadder.update(padded_data) + unpadder.finalize()

def encrypt_decrypt_aes_cbc(mode, key, iv, data):
    cipher = Cipher(algorithms.AES(key), mode(iv), backend=default_backend())
    encryptor = cipher.encryptor()
    padded_data = add_padding(data, 16)
    ciphertext = encryptor.update(padded_data) + encryptor.finalize()
    decryptor = cipher.decryptor()
    decrypted = remove_padding(decryptor.update(ciphertext) + decryptor.finalize())
    return ciphertext, decrypted

def main():
    key = os.urandom(16)  # 128-bit AES key
    iv = os.urandom(16)   # 128-bit initialization vector
    plaintext = b"This is a plaintext message for testing."

    print("Original Data:", plaintext)

    cbc_cipher, cbc_decrypted = encrypt_decrypt_aes_cbc(modes.CBC, key, iv, plaintext)
    print("CBC Ciphertext:", cbc_cipher)
    print("CBC Decrypted:", cbc_decrypted)

if _name_ == "_main_":
    main()
