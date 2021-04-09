import java.util.Scanner;

class Main {
  public static void main(String[] args) {
    Scanner key = new Scanner(System.in);
    int a, b;
    a = key.nextInt();
    b = key.nextInt();
    
    if(a == b) System.out.print("==");
    else if (a > b) System.out.print(">");
    else if ( a < b) System.out.print("<");
  }
}
