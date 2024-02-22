import numpy as np
def matrix_mod_inverse(matrix, mod):
    det = np.linalg.det(matrix)
    det_inverse = pow(int(round(det)) % mod, -1, mod)
    adjugate = np.linalg.inv(matrix) * det
    return (adjugate % mod) * det_inverse % mod
def decrypt(encrypted, key_matrix):
    return np.dot(matrix_mod_inverse(key_matrix, 26), encrypted) % 26
def main():
    key_matrix = np.array([[9, 4], [5, 7]])
    plaintext = np.array([0, 3])
    ciphertext = np.dot(key_matrix, plaintext) % 26
    print("Known Plaintext:", plaintext)
    print("Ciphertext:", ciphertext)
    recovered_plaintext = decrypt(ciphertext, key_matrix)
    print("Recovered Plaintext:", recovered_plaintext)
if __name__ == "__main__":
    main()
