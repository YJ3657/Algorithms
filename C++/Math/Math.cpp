#include<bits/stdc++.h>
#include<limits.h>
using namespace std;

#define ll long long
#define arr array
#define INF 987654321

class Math {

  Math() {}
  // Primality Test (Naive impl)
  bool check_prime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if ((n % 2) == 0) return false;

    for(int number = 3; number * number <= sqrt(n); number += 2) {
      if ((n % number) == 0) return false;
    }
    return true;
  }

  vector<int> prime_factor(int n) {
    vector<int> prifact;

    while((n % 2) == 0) {
        prifact.push_back(2);
        n /= 2;
      }    

    for(int number = 3; number * number <= n; number += 2) {
      while((n % number) == 0) {
        prifact.push_back(number);
        n /= number;
      }
    }

    if(n > 1) prifact.push_back(n);
    return prifact;
  }

  // Eratosthenes's sieve
  bool *eratosthenes_sieve(int n) {
    bool isPrime[n + 1];
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    
    for(int number1 = 2; number1 * number1 <= n; number1++) {
      if (isPrime[number1]) {
        for(int number2 = number1 * number1; number2 <= n; number2 += number1){
          isPrime[number2] = false;
        }
      }
    }
    return isPrime;
  }

  // Eratosthenes's sieve with bit masking (saves space - we use N / 8 byte to find the element)
  // Limitation - must know the size beforehand
  unsigned char *beratosthenes_sieve(int n) {
    unsigned char isPrime[(n + 7) / 8];
    memset(isPrime, 255, sizeof(isPrime));
    isPrime[0 >> 3] &= ~(1 << (0 & 7));
    isPrime[1 >> 3] &= ~(1 << (1 & 7));

    for(int number1 = 2; number1 <= int(sqrt(n)); number1++) {
      if(isPrime[number1 >> 3] & (1 << (k & 7))) {
        for(int number2 = number1 * number1; number2 <= n; number2 += number1){
          isPrime[number2 >> 3] &= ~(1 << (number2 & 7));
        }
      }
    }
  }

  // Euclidean Algorithm
  int gcd(int p, int q) {
    if(q == 0) return p;
    return gcd(q, p % q);
  }

  // Extended Euclidean Algorithm for finding x, y such that gcd(p,q) = px + qy
  pair<int, int>extended_euclid(int p, int q) {
    if (p == 0) return make_pair(0, 1);
    else if (q == 0) return make_pair(1, 0);
    int xp, yp;
    int remainder = p % q, quotient = p / q;
    pair<int, int> pa = extended_euclid(q, remainder);
    xp = pa.first, yp = pa.second;
    return make_pair(yp, xp - quotient * yp);
 }

  // Least Common Multiple
int lcm(int p, int q) {
  return (abs(p) * abs(q)) / gcd(p, q);
}

  // Linear Congruences for finding x for x ≡ x_0 (mod n / gcd(a, n)) and x = x_0 + (n / gcd(a, n)) * t 
  // where ax ≡ b (mod n)
  int lin_cong(int a, int b, int n, int t) {
    int d = gcd(a, n);
    if (d == 1) return -1; // This is he case when there is no solution

    pair<int, int> pa = extended_euclid(a, n);
    return pa.first + (n / d) * t;
  }
};