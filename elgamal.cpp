/*
    CPP
*/

#include <iostream>

/*
    For eficiency module and power (pow)
*/
int powMod(int base, int root, int mod) {
    int dummy = base;

    for (int i = 0; i < root-1; i++) {
        dummy = (dummy * base) % mod;
    }

    return dummy;
}

int isRelativePrime(int a, int b) {
    int dummy = 0;

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
        h[i] = powMod(root, i+1, prime);
    }
    
    int kampret = 1;
    int arrsize = sizeof(h)/sizeof(h[0]);
    for(int i=0; i<arrsize-1; i++) {
        for (int j=kampret; j<arrsize; j++) {
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
        y = powMod(g, x, p);
        std::cout << "Public key = (" << y << ", " << g << ", " << p << ")" << std::endl; 
        std::cout << "Private key = " << x << std::endl; 
    } else {
        std::cout << g << " is not primitive root from " << p << std::endl;
    }
}

void encryption() {
    int msg = 48, y = 0, g = 0, p = 0, x = 0;
    std::cout << "Input y, g, p = ";
    std::cin >> y >> g >> p;
    
    std::cout << "Input k (1 < k < p-1) = ";
    int k = 0;
    std::cin >> k;
    
    int a = powMod(g, k, p);
    int b = powMod(y, k, p) * msg % p;

    std::cout << "Ciphertext = (" << a << ", " << b << ")" << std::endl;
}

void decryption() {
    int a, b, x, p, m;
    std::cout << "Input a, b, x, p = ";
    std::cin >> a >> b >> x >> p;
    m = powMod(a, p-1-x, p) * b % p;
    std::cout << "Message = " << m << std::endl;
}

int main() {
    int p = 0, g = 0, x = 0;
    std::cin >> p >> g >> x;
    keyBuilder(p, g, x);

    encryption();
    decryption();
}