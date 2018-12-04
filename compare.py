from Crypto.Cipher import AES
import binascii
import os

key =  binascii.unhexlify('2b7e151628aed2a6abf7158809cf4f3c')
text = binascii.unhexlify('3243f6a8885a308d313198a2e0370734')
IV =   binascii.unhexlify('00000000000000000000000000000000')

# IV = os.urandom(16)
# print(binascii.hexlify(IV).upper())
encryptor = AES.new(key, AES.MODE_CBC, IV=IV)

ciphertext = encryptor.encrypt(text)
print(binascii.hexlify(ciphertext))

# OUTPUT: b'3925841d02dc09fbdc118597196a0b32'
# This is the same as
# 39 02 dc 19 
# 25 dc 11 6a 
# 84 09 85 0b 
# 1d fb 97 32 

