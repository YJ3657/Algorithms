package Java.Misc;
import java.lang.Math;

public class NumericalError {
  
  // Equal Check Using Relative and Absolute Error 
  // Code below is useful when dealing with floating-point values (ex. double, float) used in 
  // various algorithms (ex. binary search)
  public static boolean isEqual(double a, double b) {
    double diff = Math.abs(a - b);
    // If we have the difference within the range of acceptable absolute error, then 
    // we return true (absolute error works well with the values within small ranges)
    if (diff < 1e-10) return true;
    // if not, then we check for the relative error, which works well with the large values
    return diff <= (1e-8) * Math.max(Math.abs(a), Math.abs(b));
  }

  public static int binarySearch(int[] arr, int target) {
    int left = 0;
    int right = arr.length - 1;

    while (left <= right) {
      // This calculation prevents overflowing occuring from left + right operation
      int mid = left + (right - left) / 2;

      if (arr[mid] == target) {
        return mid;  // Found the target at index mid
      } else if (arr[mid] < target) {
        left = mid + 1;  // Target is in the right half
      } else {
        right = mid - 1;  // Target is in the left half
        }
    }
    return -1;  // Target not found in the array
  }

}