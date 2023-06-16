package Java.Misc;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;
// Specifically for the Scanner Class
import java.util.Scanner;

// There could be more files added in future
public class FastIO {
  // First Way (Using Scanner Class):
  public static void firstMethod(String[] args) {
    try (Scanner s = new Scanner(System.in)) {
      int n = s.nextInt();
      int k = s.nextInt();
      int count = 0;
      while (n-- > 0) {
          int x = s.nextInt();
          if (x % k == 0)
              count++;
      }
      System.out.println(count);
    }
  }

  // Second Way (Using BufferedReader Class):
  public static void secondMethod(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(
        new InputStreamReader(System.in));

    StringTokenizer st
        = new StringTokenizer(br.readLine());
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    int count = 0;
    while (n-- > 0) {
        int x = Integer.parseInt(br.readLine());
        if (x % k == 0)
            count++;
    }
    System.out.println(count);
  }

  // Third Way (User-defined Class) (The fastest)
  static class FastReader {
    BufferedReader br;
    StringTokenizer st;

    public FastReader() {
      br = new BufferedReader(
            new InputStreamReader(System.in));
    }

    String next() {
      while (st == null || !st.hasMoreElements()) {
        try {
          st = new StringTokenizer(br.readLine());
        }
        catch (IOException e) {
          e.printStackTrace();
        }
      }
      return st.nextToken();
    }

    int nextInt() { return Integer.parseInt(next()); }

    long nextLong() { return Long.parseLong(next()); }

    double nextDouble() {
      return Double.parseDouble(next());
    }

    String nextLine() {
      String str = "";
      try {
          if(st.hasMoreTokens()){
            str = st.nextToken("\n");
          }
          else {
            str = br.readLine();
            }
        }
      catch (IOException e) {
        e.printStackTrace();
      }
    return str;
    }
  }

  public static void thirdMethod(String[] args) {
    FastReader s = new FastReader();
    int n = s.nextInt();
    int k = s.nextInt();
    int count = 0;
    while (n-- > 0) {
      int x = s.nextInt();
      if (x % k == 0)
        count++;
    }
    System.out.println(count);
    }
}