import string
from collections import Counter

# Known letter frequency in the English language
ENGLISH_FREQUENCIES = ['E', 'T', 'A', 'O', 'I', 'N', 'S', 'H', 'R', 'D', 'L', 'C', 'U', 'M', 'W', 'F', 'G', 'Y', 'P', 'B', 'V', 'K', 'J', 'X', 'Q', 'Z']

def decrypt_caesar(ciphertext, shift):
    alphabet = string.ascii_uppercase
    decrypted = ""

    for char in ciphertext:
        if char in alphabet:
            decrypted += alphabet[(alphabet.index(char) - shift) % 26]
        else:
            decrypted += char

    return decrypted

def frequency_analysis(ciphertext, n=10):
    counter = Counter(ciphertext)
    most_common = [item[0] for item in counter.most_common(n)]
    possible_shifts = []

    for common in most_common:
        for freq in ENGLISH_FREQUENCIES:
            shift = (ord(common) - ord(freq)) % 26
            if shift not in possible_shifts:
                possible_shifts.append(shift)

    plaintexts = []
    for shift in possible_shifts:
        plaintexts.append(decrypt_caesar(ciphertext, shift))

    return plaintexts

def main():
    ciphertext = input("Enter the ciphertext: ").upper()
    n = int(input("How many possible plaintexts do you want? "))

    plaintexts = frequency_analysis(ciphertext, n)
    for i, text in enumerate(plaintexts, 1):
        print(f"{i}. {text}")

if __name__ == "__main__":
    main()
