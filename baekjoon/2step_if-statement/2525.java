import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int hour, minuet, time;
        hour = input.nextInt();
        minuet = input.nextInt();
        time = input.nextInt();
        
        if(time >= 60) {
            hour += time / 60;
            minuet += time % 60;
        } else {
            minuet += time;
        }

        if(minuet >= 60) {
            hour += minuet / 60;
            minuet %= 60;
        }

        System.out.print(hour + ' ' + minuet);
        
        input.close();
    }
}