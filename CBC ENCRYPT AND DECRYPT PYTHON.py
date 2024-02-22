# S-DES Substitution Boxes (S-Boxes)
S_BOXES = [
    [1, 0, 3, 2],
    [3, 2, 1, 0],
    [0, 2, 1, 3],
    [3, 1, 3, 2]
]

def apply_s_box(input_val, s_box):
    row = (input_val >> 1) & 0b10 | input_val & 0b01
    col = (input_val >> 2) & 0b10 | (input_val >> 3) & 0b01
    return s_box[row][col]

def left_shift(value, num_bits):
    return ((value << num_bits) & 0xFF) | (value >> (8 - num_bits))

def encrypt_block(block, key):
    def generate_subkeys():
        return [key >> 2, left_shift(key, 1) >> 2]

    subkeys = generate_subkeys()
    left, right = block >> 4, block & 0x0F
    for i in range(2):
        ep = (right << 2) | (right >> 2)
        xored = ep ^ subkeys[i]
        left, right = right ^ apply_s_box((xored >> 4) & 0x0F, S_BOXES), left ^ apply_s_box(xored & 0x0F, S_BOXES)
    return (right << 4) | left

def ctr_mode(plaintext, key):
    ciphertext = []
    counter = 0
    for byte in plaintext:
        ciphertext.append(encrypt_block(byte ^ counter, key))
        counter = (counter + 1) & 0xFF
    return bytes(ciphertext)

def main():
    plaintext = [0b00000001, 0b00000010, 0b00000100]
    key = 0b0111111101
    encrypted = ctr_mode(plaintext, key)
    print("Plaintext:", [bin(byte)[2:].zfill(8) for byte in plaintext])
    print("Encrypted:", [bin(byte)[2:].zfill(8) for byte in encrypted])

if __name__ == "__main__":
    main()
