#include<bits/stdc++.h>
#include<limits.h>
using namespace std;

// This file presents ways to prevent positive/negative overflow, etc in 
// calculation, and to write more numerically stable code
class NumericalError {
  // Equal Check Using Relative and Absolute Error 
  // Code below is useful when dealing with floating-point values (ex. double, float) used in 
  // various algorithms (ex. binary search)
  bool isEqual(double a, double b) {
    double diff = fabs(a - b);
    // If we have the difference within the range of acceptable absolute error, then 
    // we return true (absolute error works well with the values within small ranges)
    if (diff < 1e-10) return true;
    // if not, then we check for the relative error, which works well with the large values
    return diff <= (1e-8) * max(fabs(a), fabs(b));
  }

  // Below are the example codes that prevent overflow from occuring 
  // Example 1. Binary Search
  int binarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
      // This calculation prevents overflowing occuring from left + right operation
      int mid = left + (right - left) / 2;

      if (arr[mid] == target) {
          return mid;  // Found the target at index mid
      }
      else if (arr[mid] < target) {
          left = mid + 1;  // Target is in the right half
      }
      else {
          right = mid - 1;  // Target is in the left half
      }
    }
    return -1;  // Target not found in the array
  }

  // Example 2. Least Common Multiple
  int lcm(int a, int b) {
    // First way (Using promotion)
    long long result1 = (a * (long long)b) / gcd(a, b);
    // Second way (using arithmetic trick)
    int result2 = a * (b / gcd(a, b));
    return result2;
  }
}