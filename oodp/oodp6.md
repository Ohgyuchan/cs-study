* 디자인패턴
  * 설계에 있어서 공통적인 부분
  * 반복적인 문제에 대해 재사용 가능한 솔루션을 나타낸다.
* 주 목적 - 소프트웨어 디자인패턴
  * 경험들을 뽑아내는 것
  * 설계의 재사용과 확신을 높이는 것에 도움이 된다.
  * 공통적인 단어를 통해 설계에 있어서 소통을 원활하게 해쥼
* 감마 디자인 패턴
  * 23개의 디자인 패턴
* 디자인 패턴의 카테고리
  * creational pattern - 객체 생성
  * structural pattern - 정적 요소와 구조
  * behavior patter - 클래스 간의 동적 상호작용
* 싱글톤 패턴
  * Category: Creational dp
  * Intent: 전역으로 접근 가능한 인스턴스를 하나만 가지는 클래스를 만들게 하기 위해
  * Applicability: 클라이언트로 하여금 잘 알려진 엑세스 포인트에 엑세스 가능하게 한다.
  * Multithread Problem
    * singleton 클래스 내에서 instant 선언 시 초기화 방법
    * synchronized - getter & print에 각각 synchronized

* 템플릿 메소드 패턴
  * Category: Behavioral dp
  * Intent: 특정 작업을 처리하는 일부분을 서브 클래스로 캡슐화하여 전체적인 구조는 바꾸지 않으면서 특정 단계에서 수행하는 내용을 바꾸는 패턴
  * Applicability: 
    * non-abstract: 공통 behavior
    * abstract: context-specific behavior
    * context마다 특정 behavior가 placeholder의 역할을 하고, 이것을 hook-method라고 한다.

* strategy 패턴
  * Category: Behavioral dp
  * Intent: 메소드를 캡슐화를 통해 오브젝트화 시켜 코드의 중복을 없앤다.
  * Applicability:
    * abstract method: 각가의 전략 클래스에 선언되어있다.
    * context class에서 abstract method를 오버라이드한다.
    * 메소드들을 캡슐화를 통해 오브젝트처럼 사용하여 코드를 변경할 때 이것들만 변경하여서 확장에 용이하게 한다.
  * 객체들이 할 수 있는 행위 각각에 대해 전략 클래스를 생성하고, 유사한 행위들을 캡슐화 하는 인터페이스를 정의하여,
  * 객체의 행위를 동적으로 바꾸고 싶은 경우 직접 행위를 수정하지 않고 전략을 바꿔주기만 함으로써 행위를 유연하게 확장하는 방법

* Generic components == reusable components
  * 기본 테크닉
    * 리팩토링(refactoring)
    * 제너럴라이징(generalizing)
  * 제너릭 컴포넌트를 만드는데 사용되는 메카니즘
    * 상속(inheritance)
    * 위임(delegation)
* refactoring
  * 제너릭한 소프트웨어를 만들어가는 과정
  * 반복되는 코드를 찾아서 리팩토링 시작
  * 이걸 기반으로 제너링 컴포넌트 로직을 만들고
  * 또 이걸 기반으로 프로그래밍 재구조화
  * 장점
    * 반복적인 코드를 하나로 정리하고,
    * 필요한 데에 가져다 쓰기
  * 방법
    * 메소드 인보케이션
      * 가장 간단한 방법
      * 메소드를 인보케이션하여 구현
      * 하나의 메소드에서 반복적이거나
      * 하나의 클래서에서 반복적인 경우에 효율적
    * 상속
      * 여러 클래스에서 반복적인 부분이 있을 때
      * 클래스 하나에 정리해서 상속 시키기
      * delegation 보다 더 쉬움
      * 싱글 인헤리턴스로는 불가능한 경우가 존재
      * 즉, 이미 상속 받은 클래스 경우에는 불가능
    * 위임
      * 여러 클래스에서 반복적인 부분이 있을 때, 패런트 클래스(상속)를 사용하지 못할 때
      * 헬퍼 클래스를 만들어서 정리 후 헬프 객체 생성 후 호출
      * 인헤리턴스 보다 플렉서블 하다
      * 위임으로는 항상 리팩토링 구현 가능
