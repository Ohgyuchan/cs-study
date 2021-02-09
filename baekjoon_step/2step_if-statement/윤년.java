import java.util.Scanner;

class Main {
  public static void main(String[] args) {
    Scanner key = new Scanner(System.in);
    int year;
    year = key.nextInt();

    if (year <= 4000 && year >= 1) {
      if(year%4 == 0 && year%100 != 0 || year%400 == 0)
          System.out.print(1);

      else
        System.out.print(0);
    }
  }
}
