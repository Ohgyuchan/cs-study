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
- 단점
    - 싱글톤 수정 시 싱글톤을 사용한 여러 곳에서 사이드 이펙트가 발생할 가능성이 있다.
    - 멀티스레드 환경에서는 동기화 문제가 발생할 수 있다.
- 클래스 다이어그램
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/dda32c86-ef55-4a69-9958-12db610d5c3f/Untitled.png)
    

## Template Method Pattern

- 행위 패턴
- 정의
    - 작업에서 알고리즘의 골격을 정의하고 일부 단계를 하위 클래스로 연기합니다.
    - 템플릿 메서드를 사용해 하위 클래스에서 전체 구조를 변경하지 않고 알고리즘의 특정 단계를 재정의하는 패턴
- 장점
    - 전체적인 구조를 변경하지 않기 때문에 코드의 수정/보수에 용이하다.
- 단점
    - 추상 메소드가 많아지면 클래스 관리가 복잡해진다.
    - 복잡해질수록 클래스 간의 관계와 코드가 꼬여버릴 가능성이 있다.
- 사용이유
    - 전체적인 구조 변경 없이 다른 알고리즘을 사용할 수 있게 해준다.
- 클래스 다이어그램
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/c40d1aaa-1c13-4c3a-b3ce-ee829d9bfff6/Untitled.png)
    

## Strategy Pattern

- 행위 패턴
- 정의
    - 객체가 할 수 있는 행위들을 각각 전략 클래스로 만든다.
    - 전략 클래스를 캡슐화하는 인터페이스를 정의
    - 객체의 행위를 바꾸고 싶을 때 전략을 바꿔주는 것으로 행위의 수정이 이루어지도록 하는 패턴
- 장점
    - 새로운 기능이 필요하면 interface를 상속해서 구현만 하면 되기 때문에 확장성이 좋다.
- 단점
    - 추상화를 사용하기 때문에 간단한 코드의 경우 전략패턴을 사용하지 않는 것이 더 유용할 수 있다.
- 클래스 다이어그램

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/6f1852d2-f4ce-4cf7-9205-47bad8bc2eff/Untitled.png)

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
        - 전략패턴은 알고리즘(하는 방법, 어떻게 하는지)에 초점, 공격을 할 때 어떤 무기로 공격을 할지
        - 커맨드는 행위(무엇을 하는지)에 초점, 버튼을 눌렀을 때 어떤 기능이 실행하는지
- 단점
    - 커맨드 패턴은 코드의 전체적인 구조에 대한 이해가 필요하고, 복잡한 설계 구조를 가진다.

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
- 장점
    - 실시간으로 한 객체의 변경사항을 다른 객체에 전파할 수 있다.
    - 느슨한 결합으로 시스템이 유연하고 객체간의 의존성을 최소화할 수 있다.
- 단점
    - 너무 많이 사용하게 되면, 상태 관리가 어렵다.
    - 데이터 배분에 문제가 생기면 큰 문제로 이어질 수 있다.
- 클래스 다이어그램
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/bc19728f-8d09-4390-bd54-da2962321591/Untitled.png)
    

## Composite Pattern

- 구조 패턴
- 정의
    - 전체와 부분을 동일시해서 재귀적인 구조를 만들기 위한 패턴
- 장점
    - 부분-전체의 관계를 갖는 객체들을 정의할 때 유용하다.
    - 부분객체를 추가하더라도 전체 코드는 건드리지 않는다.
    - 코드가 단순해진다.
- 설계가 지나치게 범용성을 가질 수 있다.
- 클래스 다이어그램

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/df168dd0-1d1d-4440-95c5-c574404f92b8/Untitled.png)

## Decorator Pattern

- Serializing: 오브젝트를 쓰는 것(내보내거나)
- Deserializing: 오브젝트를 Restore하는 것(restore하거나)
- 정의
    - 원천 객체(Object)에 기능을 추가해나가는 디자인 패턴
    - add-on feature를 갖는 패턴
    - 연장, each add-on feature 마다 다른 클래스
- 장점
    - 객체에 동적으로 기능 추가가 간단하게 가능하다
- 단점
    - 클래스가 너무 많아 질 수 있다.
    - 겹겹이 애워싸는 형태이기 때문에 객체의 정체를 알기 힘들고 가독성이 떨어질 수 있다.

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

## Iterator Pattern

- 정의
    - 자료구조에 상관없이 객체 접근 방식을 통일시키고자 할 때 사용
- 클래스 다이어그램

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/b7d29df8-1d56-4747-baab-94b447318104/Untitled.png)

## Factory Design Pattern

- instance 생성

## Factory Method Pattern

- instance 생성
- 전체 구조 생성
- 템플릿 메서드 패턴을 이용한 형태
- 클래스 다이어그램

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/08076ce1-65df-4e40-912d-c6401c62884d/Untitled.png)

## Abstract Factory Pattern

- 추상 팩토리 패턴은 많은 수의 연관된 서브 클래스를 특정 그룹으로 묶어 한번에 교체할 수 있도록 만든 디자인 패턴이다.
- 추상 팩토리 패턴은 팩토리 메소드 패턴과 유사하다. 하지만 한가지 다른 것은 팩토리를 만드는 상위 팩토리(super-factory) 클래스가 존재한다.

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a05d12de-f3de-4e05-8d60-2bbbd3081531/Untitled.png)

## Prototype Pattern

- Creational Pattern
- 정의
    - 생성할 객체의 `원본을 저장`해두고 새로 해당 객체를 생성할 때는 원본 객체를 `복제`하여 사용하는 방법
    - object.clone()

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/531bc87f-aaae-4d41-8713-028e8ce98b6d/Untitled.png)

## Builder Pattern

- Creational Pattern
- 인스턴스 생성을 Builder Class를 통해 하는 방법
- 생성자 vs 빌더
    - 생성자 호출: 설정하길 원하지 않는 매개변수의 값까지 지정해줘야하는 불편함이 있다.
    - 빌더: 필수 매개변수를 제외하고는 메서드를 통해 순서에 상관없이 입력 가능하다.
- ex) class.fromMap()

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/08aff4a7-3fa3-4ae6-93b7-116d20351e71/Untitled.png)

## Adapter Pattern

- Structural Pattern
- 정의
    - 한 클래스의 인터페이스를 클라이언트에서 사용하고자하는 다른 인터페이스로 변환하는 패턴
    - 어댑터를 이용하면 인터페이스 호환성 문제 때문에 같이 쓸 수 없던 클래스들을 연결해서 쓸 수 있다.
- 클래스 다이어그램

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/9888e980-c39e-4719-88e1-db1015f219d3/Untitled.png)

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

- 정의
    - 사공이 많으면 배가 산으로 간다.
    - 중개인이 있으면 사공은 모두 중개인에게 보고를 하고 중개인이 사원들에게 지시를 내릴 수 있게되면서 혼란이 사라진다.
    - 모든 클래스간의 복잡한 로직(상호작용)을 캡슐화하여 하나의 클래스에 위임하여 처리하는 패턴이다.
    - 즉, M:N의 관계에서 `M:1의 관계로 복잡도`를 떨어뜨려 `유지 보수 및 재사용의 확장성`에 유리한 패턴이다
- 장점
    - 효율적인 자원 관리를 가능하게 한다
    - 객체간의 통신을 위해 서로간에 직접 참조할 필요가 없게 한다
    - 객체들 간 수정을 하지 않고 관계를 수정할 수 있다
- 단점
    - 특정 application 로직에 맞춰져있기 때문에 다른 application에 재사용하기 힘들다
    - 중재자 패턴 사용 시 중재자 객체에 권한이 집중화되어 굉장히 크고 복잡해지므로, 설계와 수정 시 주의해야 한다.
- 클래스 다이어그램

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/cea5f3b2-45d8-4580-8e40-0855011b4974/Untitled.png)

## Facade Pattern

- 정의
    - 프로그램의 정면에서 요구를 받아서 전해주는 역할
    - 클래스 간의 관계를 정확히 파악 후 올바른 순서대로 메소드를 호출
    - 여러 메소드 호출을 대신 해주는 역할
- 장점
    - subsystem간의 결합도를 낮출 수 있다.
    - 클래스 간 의존성을 줄일 수 있다.
- 단점
    - 클라이언트에게 내부 subsystem까지 숨길 수 없다.
- 클래스 다이어그램

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/61ebac23-5c4a-4a02-9ffc-cff34a748559/Untitled.png)

## Proxy Pattern

- 정의
    - Proxy는 대리인이라는 뜻
    - 요청에 필요한 객체의 메서드를 대신 호출
    - 실제 객체를 사용하기 전에 전처리 작업이 가능
    - 실제 객체에 접근하기 전에 접근 권한을 판단하고 할 수 있는 일만 대신 수행
- 장점
    - 사이즈가 큰 객체가 로딩되기 전에도 프록시를 통해 참조할 수 있다
    - 객체의 접근에 대해서 사전처리를 할 수 있다
- 단점
    - 로직이 난해해져 가독성이 떨어질 수 있다
    - 객체를 생성할 때 한 단계를 거치게 되므로, 빈번한 객체 생성이 필요한 경우 성능이 저하될 수 있다

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/ee1f650b-cd00-4ef6-bfa5-802f93b0512f/Untitled.png)

## Flyweight Pattern

- 정의
    - 인스턴스를 공유시키면서 불필요한 인스턴스를 생성하지 않게 하는 패턴
    - 객체 생성 시 별도의 공간( FlyWeightFactory )에 미리 저장해두고,
    객체를 사용할 때 이미 생성된 객체라면 해당 객체를 꺼내서 전달하는 방식
    - 인스턴스를 공유하기 때문에 편리할 수도 버그가 많을 수도 있다.
- 장점
    - 많은 객체를 만들 때 성능이 향상된다
    - 여러 가상 객체의 상태를 한 곳에 집중시켜 놓을 수 있다
- 단점
    - 특정 인스턴스의 공유 컴포넌트를 다르게 행동하게 하는 것이 불가능하다
    - 객체의 값을 변경하면 공유받은 가상 객체를 사용하는 곳에 영향을 줄 수 있다
- 클래스 다이어그램

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/37959000-92f6-4a78-8578-527ede617e83/Untitled.png)

## Chain of Responsibility Pattern

- 정의
    - 여러 객체를 연결해서 연결된 객체를 순회하며 요청을 처리할 객체를 결정하는 방법
    - 요청이 들어 왔을 때, 요청을 처리할 수 있는 기회의 하나 이상의 객체에게 부여하는 방법이다.
    - 요청을 처리할 객체를 Chain 구조로 묶고 요청을 처리할 때까지 다음 객체로 요청을 전달한다
- 장점
    - 객체 간의 행동적 결합도가 낮아진다
        - 요청을 보내는 쪽이나 받는 쪽 모두 서로를 몰라도 되고, 연결 고리에 있는 객체들조차도 서로 어떻게 자신들이 연결되어 있는지 몰라도 된다. 자신과 연결된 그 다음 객체만 알면 된다.
- 단점
    - 비슷한 클래스가 너무 많이 생길 수 있다.
- 클래스 다이어그램

![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/7740e385-7863-41de-adcc-0e6c4705aa51/Untitled.png)

## Visitor Design Pattern

- 정의
    - 데이터 구조와 처리를 분리하는 패턴
    - 데이터 구조와 처리를 분리하여 데이터 구조 내부를 순회하는 Visitor에게 처리를 위임한다.
    - 새로운 처리를 추가할 때에는 새로운 Visitor를 생성하고 데이터 구조영역에서 해당 방문자의 접근을 허용한다.
- 사용이유
    - 데이터 구조 안에 많은 요소가 저장되어있고, 각 요서에 대해 무엇인가를 처리 해야할 때
    처리하는 코드를 데이터 구조를 표시하고 있는 클래스 안에 기술한다면 새로운 처리가 필요할 때마다 구조의 클래스의 수정이 필요하다.
- 장단점
    - 장점: ConcreteVisitor 추가는 간단, ConcreteElement의 수정이 필요 없기 때문
    - 단점: ConcreteElement의 추가는 복잡, 이에 따른 새로운 visitor가 필요하고 이로 인해 visitor 하위 클래스 전부에 새로운 메소드를 구현해야하기 때문
- 클래스 다이어그램