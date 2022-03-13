import java.util.Scanner;

class Main {
  public static void main(String[] args) {
    Scanner key = new Scanner(System.in);
    int h, m;
    
    h = key.nextInt();
    m = key.nextInt();

    if(m >= 45) { m -= 45; }
    else if(m < 45) { 
      m = 60 + (m - 45); 
      if(h == 0)
        h = 23;
      else h--;
    }
    System.out.print(h + " " + m);
    key.close();
  }
}
