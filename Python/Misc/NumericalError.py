from collections import *
from typing import *
from sys import *
from math import *
import heapq

# This file presents ways to prevent positive/negative overflow, etc in 
# calculation, and to write more numerically stable code
class NumericalError:

  """Equal Check Using Relative and Absolute Error 
  Code below is useful when dealing with floating-point values (ex. double, float) used in 
  various algorithms (ex. binary search)"""
  def isEqual(a: float, b: float) -> bool:
    diff = abs(a - b)
    # If we have the difference within the range of acceptable absolute error, then 
    # we return true (absolute error works well with the values within small ranges)
    if (diff < 1e-10): return True
    # if not, then we check for the relative error, which works well with the large values
    return diff <= (1e-8) * max(abs(a), abs(b))

  # Below are the example codes that prevent overflow from occuring 
  # Example 1. Binary Search
  def binary_search(arr: List[int], target: int) -> bool:
    left = 0
    right = len(arr) - 1

    while left <= right:
        # This calculation prevents overflowing occuring from left + right operation
        # Though this operation doesn't have any change in Python
        mid = left + (right - left) // 2

        if arr[mid] == target:
            return mid  # Found the target at index mid
        elif arr[mid] < target:
            left = mid + 1  # Target is in the right half
        else:
            right = mid - 1  # Target is in the left half

    return -1  # Target not found in the array

  # Example 2. Least Common Multiple
  def lcm(a: int, b: int) -> int:
    # Using arithmetic trick (this operation doesn't have any change in Python)
    result = a * (b / gcd(a, b))
    return result