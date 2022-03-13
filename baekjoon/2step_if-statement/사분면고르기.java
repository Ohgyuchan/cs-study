import java.util.Scanner;

class Main {
  public static void main(String[] args) {
    Scanner key = new Scanner(System.in);
    int x, y;
    
    x = key.nextInt();
    y = key.nextInt();

    if(x > 0) {
      if(y > 0) System.out.print(1);
      if(y < 0) System.out.print(4);
    } else if(x < 0) {
      if(y > 0) System.out.print(2);
      if(y < 0) System.out.print(3);
    }
    key.close();
  }
}
