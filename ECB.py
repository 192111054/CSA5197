from cryptography.hazmat.primitives import padding
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

def add_padding(data, block_size):
    padder = padding.PKCS7(block_size * 8).padder()
    return padder.update(data) + padder.finalize()

def remove_padding(padded_data):
    unpadder = padding.PKCS7(128).unpadder()
    return unpadder.update(padded_data) + unpadder.finalize()

def encrypt_decrypt(mode, key, iv, data):
    cipher = Cipher(algorithms.AES(key), mode, backend=default_backend())
    encryptor = cipher.encryptor()
    padded_data = add_padding(data, 16)
    ciphertext = encryptor.update(padded_data) + encryptor.finalize()
    decryptor = cipher.decryptor()
    decrypted = remove_padding(decryptor.update(ciphertext) + decryptor.finalize())
    return ciphertext, decrypted

def main():
    key = b"this_is_a_16_key"
    iv = b"this_is_a_16_iv_"
    plaintext = b"This is a plaintext message for testing."

    print("Original Data:", plaintext)

    ecb_cipher, ecb_decrypted = encrypt_decrypt(modes.ECB(), key, iv, plaintext)
    print("ECB Ciphertext:", ecb_cipher)
    print("ECB Decrypted:", ecb_decrypted)

    cbc_cipher, cbc_decrypted = encrypt_decrypt(modes.CBC(iv), key, iv, plaintext)
    print("CBC Ciphertext:", cbc_cipher)
    print("CBC Decrypted:", cbc_decrypted)

if _name_ == "_main_":
    main()
