def xor_bytes(a, b):
    return bytes(x ^ y for x, y in zip(a, b))

def encrypt_cbc_mac(key, message):
    iv = b'\x00' * len(key)  # Initialization vector
    ciphertext = iv

    for i in range(0, len(message), len(key)):
        block = message[i:i + len(key)]
        ciphertext = xor_bytes(ciphertext, block)
        ciphertext = xor_bytes(ciphertext, key)

    return ciphertext

def main():
    key = b'Sixteen byte key'
    message = b'Hello, world!'

    mac_x = encrypt_cbc_mac(key, message)
    mac_x_xor = encrypt_cbc_mac(key, message + xor_bytes(message, mac_x))

    print("Original Message:", message)
    print("MAC(X):", mac_x.hex())
    print("MAC(X || (X ⊕ T)):", mac_x_xor.hex())

if __name__ == "__main__":
    main()
