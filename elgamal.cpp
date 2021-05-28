#include <iostream>

/*
    For eficiency module and power (pow)
*/
int modpow(int base, int root, int mod) {
    int dummy = base;

    for (int i = 0; i < root-1; i++) {
        dummy = (dummy * base) % mod;
    }

    return dummy;
}

int isRelativePrime(int a, int b) {
    int dummy;

    while (b != 0) {
        dummy = a % b;
        a = b;
        b = dummy;
    }

    return a;    
}

int isPrimitiveRoot(int prime, int root) {
    int h[prime-2];
    int hprime = prime;

    for(int i=0; i<prime; i++) {
        h[i] = modpow(root, i+1, prime);
    }
    
    int kampret = 1;

    for(int i=0; i<sizeof(h)/sizeof(h[0]) - 1; i++) {
        for (int j=kampret; j<sizeof(h)/sizeof(h[0]); j++) {
            if (h[i] == h[j]) {
                std::cout << "Not primite root" << std::endl;
                return 0;
            }
        }
        
        if(isRelativePrime(prime, h[i]) != 1) {
            return 0;
        }

        kampret++;
    }

    return 1;
}

void keyBuilder(int p, int g, int x) {
    int y;
    if(isPrimitiveRoot(p, g) == 1) {
        y = modpow(g, x, p);
        std::cout << "Public key = (" << y << ", " << g << ", " << p << ")" << std::endl; 
        std::cout << "Private key = " << x << std::endl; 
    } else {
        std::cout << g << " is not primitive root from " << p << std::endl;
    }
}

void encryption() {
    int msg = 48, k, a, b, y, g, p, x;
    std::cout << "Input y, g, p = ";
    std::cin >> y >> g >> p;
    std::cout << "Input k (1 < k < p-1) = ";
    std::cin >> k;
    a = modpow(g, k, p);
    b = modpow(y, k, p) * msg % p;

    std::cout << "Ciphertext = (" << a << ", " << b << ")" << std::endl;
}

void decryption() {
    int a, b, x, p, m;
    std::cout << "Input a, b, x, p = ";
    std::cin >> a >> b >> x >> p;
    m = modpow(a, p-1-x, p) * b % p;
    std::cout << "Message = " << m << std::endl;
}

int main() {
    int p, g, x;
    std::cin >> p >> g >> x;
    keyBuilder(p, g, x);

    encryption();
    decryption();
}