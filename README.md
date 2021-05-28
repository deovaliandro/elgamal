# ElGamal Cryptosystem

## Properties

1. n, a prime number (not secret)
2. g, primitive root of n (not secret)
3. x, a random number
5. y = g^x mod p
6. m, message
7. a and b, pair of ciphertext

Result:

- Alice's key: private key = x, publick key = (y, g, p). Ciphertext = (a, b).

usage:

```bash
g++ elgamal.cpp -o elgamal
./elgamal
```