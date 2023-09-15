package Java.Bitmasking;

public class Bitmasking {
  public static void main(String[] args) {
    int some_num = 32;
    int bit_on = Integer.bitCount(some_num);
    int last_bit = Integer.numberOfLeadingZeros(some_num);
  }

}