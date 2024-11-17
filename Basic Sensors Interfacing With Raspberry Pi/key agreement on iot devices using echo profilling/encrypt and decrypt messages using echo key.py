from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import binascii

# Convert the hexadecimal string to bytes
hex_key = '7b4cc45bd98e8913d50179fb63a13617ce486a74c947f4fcf915d0a69712b05c'
key_bytes = binascii.unhexlify(hex_key)

# Example data to encrypt
data = "Dumbo ee roju sayantram 5 ki vellipodam"

# AES encryption
def encrypt_message(key, message):
    cipher = AES.new(key, AES.MODE_EAX)  # Using EAX mode for example
    ciphertext, tag = cipher.encrypt_and_digest(pad(message.encode(), AES.block_size))
    return cipher.nonce + tag + ciphertext  # Combine nonce, tag, and ciphertext

# Encrypt the data
encrypted_data = encrypt_message(key_bytes, data)
print(f"Encrypted data: {binascii.hexlify(encrypted_data)}")

# AES decryption
def decrypt_message(key, encrypted_data):
    nonce = encrypted_data[:16]
    tag = encrypted_data[16:32]
    ciphertext = encrypted_data[32:]
    cipher = AES.new(key, AES.MODE_EAX, nonce=nonce)
    decrypted_data = unpad(cipher.decrypt_and_verify(ciphertext, tag), AES.block_size)
    return decrypted_data.decode()

# Decrypt the data
decrypted_data = decrypt_message(key_bytes, encrypted_data)
print(f"Decrypted data: {decrypted_data}")
