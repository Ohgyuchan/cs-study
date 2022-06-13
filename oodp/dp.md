# OODP

1. 생성(Creational) 패턴
    - 객체 생성에 관련된 패턴
    - 객체의 생성과 조합을 캡슐화해 특정 객체가 생성되거나 변경되어도 프로그램 구조에 영향을 크게 받지 않도록 유연성을 제공한다.
2. 구조(Structural) 패턴
    - 클래스나 객체를 조합해 더 큰 구조를 만드는 패턴
    - 예를 들어 서로 다른 인터페이스를 지닌 2개의 객체를 묶어 단일 인터페이스를 제공하거나 객체들을 서로 묶어 새로운 기능을 제공하는 패턴이다.
3. 행위(Behavioral)
    - 객체나 클래스 사이의 알고리즘이나 책임 분배에 관련된 패턴
    - 한 객체가 혼자 수행할 수 없는 작업을 여러 개의 객체로 어떻게 분배하는지, 또 그렇게 하면서도 객체 사이의 결합도를 최소화하는 것에 중점을 둔다.

## Singleton Pattern

- 정의
    - 클래스의 인스턴스가 프로그램 내에서 단 하나만 생성되게 하는 패턴
    - 인스턴스가 한 개밖에 존재하지 않는 것을 보장하는 패턴
    - 예) currentUser

```java
public class Singleton {
    private static Singleton singleton  = new Singleton();

    private Singleton() {
        System.out.println("created Singleton");
    }
    public static Singleton getInstance(){
        return singleton;
    }
}
```

- 장점
    - 외부에서 생성할 수 없다.
    - 고정된 영역에 미리 할당한다.('static area')
    - 고정된 영역에 할당하기에 메모리를 낭비하지 않는다.
    - JVM이 종료되기 전까지 계속 사용할 수 있다.
- 클래스 다이어그램
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/dda32c86-ef55-4a69-9958-12db610d5c3f/Untitled.png)
    

## Template Method Pattern

- 행위 패턴
- 정의
    - 작업에서 알고리즘의 골격을 정의하고 일부 단계를 하위 클래스로 연기합니다.
    - 템플릿 메서드를 사용해 하위 클래스에서 전체 구조를 변경하지 않고 알고리즘의 특정 단계를 재정의하는 패턴
    - 전체적인 구조를 변경하지 않기 때문에 코드의 수정/보수에 용이하다.
- 클래스 다이어그램
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/c40d1aaa-1c13-4c3a-b3ce-ee829d9bfff6/Untitled.png)
    

## Strategy Pattern

- 행위 패턴
- 정의
    - 객체가 할 수 있는 행위들을 각각 전략 클래스로 만든다.
    - 전략 클래스를 캡슐화하는 인터페이스를 정의
    - 객체의 행위를 바꾸고 싶을 때 전략을 바꿔주는 것으로 행위의 수정이 이루어지도록 하는 패턴
- 클래스 다이어그램

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/6f1852d2-f4ce-4cf7-9205-47bad8bc2eff/Untitled.png)

- 장점
    - 새로운 기능이 필요하면 interface를 상속해서 구현만 하면 되기 때문에 확장성이 좋다.

## Command Pattern

- 행위 패턴
- 정의
    - 명령 혹은 요청 자체를 캡슐화 하는 패턴
    - 요청 자체를 객체로 캡슐화하여 인자값으로 여러 명령을 수행시킬 수 있다.
- 클래스 다이어그램

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/0452ab8f-4bc1-415f-a843-f3033355fe9f/Untitled.png)

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/3bfa7b2d-fbd7-44ea-a2c9-ab34473b0988/Untitled.png)

- 장점
    - 전략패턴과 유사해서 확장성에 좋다.
    - 전략패턴과의 차이
        - 전략패턴은 알고리즘(하는 방법)에 초점, 공격을 할 때 어떤 무기로 공격을 할지
        - 커맨드는 행위(무엇을 하는지)에 초점, 버튼을 눌렀을 때 어떤 기능이 실행하는지

## Interpreter Pattern

- 행위 패턴
- 정의
    - 프로그램이 해결하고자 하는 문제를 간단한 `미니 언어` 로 표현하고, 구체적인 문제를 해당 `언어` 로 기술된 `미니 프로그램` 으로 표현하는 패턴
        - `미니 언어` 라는 문법을 클래스화 한 구조로써 미니 언어로 정의되어 있는 일련의 언어를 분석 및 파싱하는 패턴.
    - 미니 프로그램은 그 자체로는 동작하지 않고 Java언어로 통역(Interpreter)역할을 하는 프로그램을 만들어서 분석
    - 문법 규칙이 많아질수록 복잡해지고 무거워지기 때문에, 너무 많아진다 싶을 때는 컴파일러 생성기를 쓰거나 파서를 쓰는게 좋다.
- 클래스 다이어그램

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/02656b74-0391-4058-af2c-e850040f85cb/Untitled.png)

## Observer Pattern

- 정의
    - 관찰 대상의 상태가 변화하면 관찰자에게 알려주는 패턴
    - 어떤 객체의 상태가 변할 때, 연관된 객체들한테 알림을 보내는 디자인 패턴
- 클래스 다이어그램
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/bc19728f-8d09-4390-bd54-da2962321591/Untitled.png)
    

## Composite Pattern

- 구조 패턴
- 정의
    - 전체와 부분을 동일시해서 재귀적인 구조를 만들기 위한 패턴

## Decorator Pattern

- Serializing: 오브젝트를 쓰는 것(내보내거나)
- Deserializing: 오브젝트를 Restore하는 것(restore하거나)
- 정의
    - 원천 객체(Object)에 기능을 추가해나가는 디자인 패턴
    - add-on feature를 갖는 패턴
    - 연장, each add-on feature 마다 다른 클래스

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/fd2f2a56-2827-4eff-b77d-b4b24c37353f/Untitled.png)

- 사용 예제

```java

public class Client {
    public static void main(String args[]){

        // 핸들 있는 차
        Car carWithHandle = new HandleDecorator(new BasicCar());
        carWithHandle.make();

        // 핸들 + 휠 있는 차
        Car carWithHandleWheel = new HandleDecorator(new WheelDecorator(new BasicCar()));
        carWithHandleWheel.make();
    }
}
```

- 장점
    - 객체의 수정 없이 유동적으로 객체의 기능을 덧붙일 수 있다.

## Iterator Pattern

## Factory Design Pattern

- instance 생성

## Factory Method Pattern

- instance 생성
- 전체 구조 생성
- 템플릿 메서드 패턴을 이용한 형태

## Abstract Factory Pattern

- 각 Factory는 인스턴스를 만드는 일만 한다.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a05d12de-f3de-4e05-8d60-2bbbd3081531/Untitled.png)

## Prototype Pattern

- Creational Pattern
- 정의
    - 생성할 객체의 `원본을 저장`해두고 새로 해당 객체를 생성할 때는 원본 객체를 `복제`하여 사용하는 방법

## Builder Pattern

- Creational Pattern
- 인스턴스 생성을 Builder Class를 통해 하는 방법
- 생성자 vs 빌더
    - 생성자 호출: 설정하길 원하지 않는 매개변수의 값까지 지정해줘야하는 불편합이 있다.
    - 빌더: 필수 매개변수를 제외하고는 메서드를 통해 순서에 상관없이 입력 가능하다.

## Adapter Pattern

- Structural Pattern

```java
public interface Adapter {
    public Float twiceOf(Float f);
    public Float halfOf(Float f);
}
```

```java
public class AdapterImpl implements Adapter {

    @Override
    public Float twiceOf(Float f) {
        return (float) Math.twoTime(f.doubleValue());
    }

    @Override
    public Float halfOf(Float f) {
        return (float) Math.half(f.doubleValue());
    }
}
```

```java
public class main {
    public static void main(String[] args) {
        Adapter adapter = new AdapterImpl();
        System.out.println(adapter.twiceOf(100f)); //200.0
        System.out.println(adapter.halfOf(50f));   //25.0
    }
}
```

## Mediator Pattern

## Facade Pattern

## Proxy Pattern

## Flyweight Pattern

## Chain of Responsibility Pattern

## Visitor Design Pattern