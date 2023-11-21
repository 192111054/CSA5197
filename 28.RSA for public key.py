from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa

# Generate RSA key pair
def generate_rsa_key_pair():
    private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048,
        backend=default_backend()
    )

    public_key = private_key.public_key()

    return private_key, public_key

# Export public key to a PEM file
def export_public_key_to_pem(public_key, filename):
    pem = public_key.public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo
    )

    with open(filename, 'wb') as pem_file:
        pem_file.write(pem)

# Main program
def main():
    private_key, public_key = generate_rsa_key_pair()

    # Export public key to a PEM file
    export_public_key_to_pem(public_key, 'public_key.pem')

    print("RSA key generation and public key export successful.")

if __name__ == "__main__":
    main()
