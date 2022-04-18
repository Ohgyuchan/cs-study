* Dynamic binding of method
  * 메소드가 런타임에 바인딩 되는 것.

* type of variables and objects
  * 정해지는 시간
  * variable type -> compile time
  * class of object -> run time

* subtype
  * 클래스 간의 subtype 관계
    * 상속관계
    * 인터페이스 - 임플리먼테이션 관계
    * primitive type - Int is subtype of Long
  * Substitutability
    * superType의 value에 subtype의 value가 올 수 있다.
    * subclass의 인스턴스는 항상 상위 클래스의 인스턴스를 대체할 수 있다.
  * widening - supertype 자리에 subtype 위치
    * **Widening** 은 항상 허용.
  * narrowing - subtype 자리에 supertype을 위치
    * narrowing 할 때는 explicit cast(명시적 형변환)를 해줘야 한다.
    * 안 하면 runtime exception이 나올 수 있다.

  *  Primitive type 과 reference type의 conversion 차이
     *  Primitive type은 변수의 타입마다 표현 방식이 달라서 이것에 표현 방식을 따로 지정해줘야 된다.
     *  reference type는 표현 방식은 같고, 가르키는 오브젝트만 다르다는 점에서 차이가 있다.

* Polymorphic Assignment
  * 정적 프로그래밍 언어(C같은) 에서는 compatible type만 할당해야하는데
  * 객체지향언어에서는 Polymorphic 할당이다.

* 할당 규칙
  * rhs가 lhs의 subtype이어야 할당 가능
    * lhs의 변수가 서로 다른 클래스의 객체를 hold할 수 있다.
    * E extends B, E can acts as an instance B

* Downcasting
  * 컴파일은 되지만 런타임에서 에러가 날 수 있음
  * B b = (B) c, when c is instance of A or C.
  * 처리 방법
    * pessimistic
      * if-else 되는지 확인, 되면 하고, 아니면 딴 거
    * optimistic
      * try-catch 일단 실행 오류나면 딴 거
