#include<bits/stdc++.h>
#define INF 987654321
using namespace std;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int some_num = 32;
  int bit_on = __builtin_popcount(some_num); // must use __popcnt(some_num) for Visual C++
  int last_bit_on = __builtin_ctz(some_num); // must use _BitScanForward(&index, some_num) for Visual C++ and also 0 is not defined
  return 0;
}
