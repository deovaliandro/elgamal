def is_relative_prime(prime, data):
    """
    Prime is relative prime with data in primitive root
    :param prime: int
    :param data: int
    :return: int
    """
    while data != 0:
        prime, data = data, prime % data
    return prime

def is_primitive_root(prime, root):
    """
    Root is primitive root from prime
    :param prime: int
    :param root: int
    :return: int
    """
    primitive_root = []
    for i in range(prime - 1):
        primitive_root.append(pow(root, i + 1) % prime)

    # Untuk memastikan tidak terjadi pembandingan primitive_root pada indeks j dan i yang sama
    kampret = 1
    
    # Membandingkan apakah tidak ada data yang sama
    for i in range(len(primitive_root)):
        for j in range(kampret, len(primitive_root) - 1):
            if primitive_root[i] == primitive_root[j + 1]:
                print("Not primitive root")
                return 0

        if is_relative_prime(prime, primitive_root[i]) != 1:
            print("Not relative prime")
            return 0
        kampret += 1
    return 1


def key_builder():
    """
    Count public and private key
    """
    print("Input prime number, root and secret key (x)")
    prime, root, secret_key = [int(x) for x in input().split(" ")]

    # root number must be primitive root from prime
    if is_primitive_root(prime, root) == 1:
        y = pow(root, secret_key) % prime
        print(f"Public Key (%d, %d, %d)" % (y, root, prime))
        print(f"Private key %d" % secret_key)


def encryption():
    """
    Encryption message with public key
    """

    # message is one character, string will be add later
    print("Input message")
    message = input()

    print("Input y, g and p (public key)")
    y, g, p = [int(x) for x in input().split(" ")]

    # k is random number from 1 <= k <= p-1
    print("Input k")
    k = int(input())

    # the ciphertext will be a pair of a and b
    a = pow(g, k) % p
    b = (pow(y, k) * ord(message)) % p

    print(f"Ciphertext (%d, %d)" % (a, b))


def decryption():
    """
    Decryption message
    """
    a, b, x, p = [int(x) for x in input().split(" ")]
    m = pow(a, (p-1-x)) * b % p
    print(f"Message %c" % m)


"""
Example:
Input prime number, root and secret key (x) = 2273, 3 and 243

Public Key 461 3 2273
Private key 243

Message = a
k = 1463

Ciphertext (1439, 2004)

with decryption(), message = a
"""
key_builder()
encryption()
decryption()