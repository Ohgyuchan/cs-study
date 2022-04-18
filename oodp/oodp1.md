## 1. Object Oriented Software Development
### 1.1. Software Industry  
> 소프트웨어 시장이 성장하면서 진보되고 끊임없이 혁신적인 제품을 생산할 수 있는 것과 동시에 소프트웨어의 개발하고, 유지하는 데 있어서 많은 비용이 필요하고 이로 인해 구매 비용이 증가하는 어려움을 직면하게 되었다.
> 
> 이러한 비용과 어려움들을 줄이기 위해서 나온 개념이 객체지향 소프트웨어 개발(Object Oriented Software Development)이다.

### 1.2. Software 개발에 있어서 직면하는 어려움의 실제 사례
* 높은 난이도, 많은 시간, 많은 인력과 비용을 필요로 한다.(Difficult, Time-consuming, costly endeavor)
  * MS의 Windows NT 초기 버전
       * 6,000,000(6 million) 줄의 코드
       * $150,000,000(150 million)의 개발 비용
       * 200여명의 개발자와 테스터들이 투입되어 5년만에 완성


* 버그가 많다.(Buggy)
  * 90년 2월 15일 미국의 AT&T 통신사의 장거리 통신 네트워크가 갑자기 다운 - C 언어로 된 코드에 `Break` 를 잘못 된 위치에 쓴 것이 원인
  * 96년 6월 4일, 프랑스가 개발한 로켓 `Ariane` 로켓이 발사 된지 37초 만에 폭발 - 64bit floating points를 16bit signed integer에 넣은 것이 원인

### 1.2.1 Difficulties in Software Development
* Buggy software is the norm. - 버그가 많은 것은 일반적이다.
  * Objectives: in delivering high-quality software <u>**on time and under budget**</u>. - 목표: 적정 시간과 예산 안에서 높은 퀄리티의 소프트웨어를 제공.
* Underlying causes of the difficulties of software development - 소프트웨어 개발이 어려운 근본적인 원인
  * Complexity(복잡성)
  * Longevity and evolution(장기적이고 변화(개선) - 오래 쓰이고 계속 바뀐다.)
  * High user expectations(사용자의 높은 기대치)

#### 1.2.2. 복잡성(Complexity)
* Software systems are very large and complex
* No individual can comprehend every details of the systems.
* Large systems must be developed by <u>**teams**</u> - 큰 시스템은 `개발자`가 아니라 `개발팀`이 개발한다.
  * Requirements(요구사항)이 너무 많다.
  * Communication skill 중요
  * Documentation skill(문서화 기술) 중요

#### 1.2.3. Longevity and Evolution
* Longevity: in service for very Long Lifetime
  * some `legacy system`: operating for more than 20 years. - (장수 시스템을 `legacy system`이라고 한다.) 20년 이상 운영되는 서비스들이 있다.
* Evolution
  * must constantly evolve to accommodate <u>**changes**</u> in users' needs and environments - 사용자의 니즈와 환경의 변화를 수용하기 위해 계속해서 개선(진화)해야 한다.
  * making changes to software is very difficult  - 소프트웨어를 변경하는 것은 매우 어렵다.
  * Ex. Y2K Problems(Year 2000 Problem)
    > it also known as Millennium bug, Y2K bug.
    1900년대에는 하드웨어의 한계로 인해 메모리 사용을 줄이기 위해서 1997년 등의 년도를 97로만 표기하는 등 코드 수를 줄이기 위해 노력했었는데 2000년이 되면 `00` 이라는 것이 2000년인지 1900년인지 알 수 없기 때문에 모든 전산 시스템이 마비된다는 말이 있었는데 이것이 밀레니엄 버그, Y2K Problem이다.

#### 1.2.4. High User Expectations
* 과거에는 컴퓨터는 전문적인 일이었지만, 지금은 지극히 평범한 일이 되었다. 따라서 일반적이 사람들은 프로그램이 버그가 없는 것(Bug Free)을 당연하게 여긴다.

### 1.3. Software Engineering
* Software Engineering
  * coined at a NATO workshop in 1668
  * to build the practice of software development on a solid scientific foundation
  * to attain the level of reliability and productivity associated with well-established engineering principles
  * 기존 Engineering Discipline으로 부터 Software Engineering의 특성을 살린 것.
  * defines the various <u>**activities**</u>
  * defines the <u>**software development processes**</u>
* Software means
* not only 소스코드 but also, **Documentation**
* **Documentation**
  * Requirements specification - 요구사항 설명서
  * Architecture and Design documents - 구조와 설계 문서
  * Configuration data - 구성 데이터
  * Installation and user manuals - 설치 및 사용자 매뉴얼

### 1.3.1. Software Development Activities
> Activity는 시간(순서) 개념이 포함이 안 된다고 생각.
> 
> 아래 내용들 모두 순서가 정해진 것이 아닌 그때그때 추가 될 수도 있기 때문.
* 요구사항 분석
  * 기능, 서비스, 제약을 정리
  * 사용자 타입
    * custom user: specific customer 특정 타겟 앱
    * commercial software (Shrink-wrapped): potential software 범용 앱
  * 요구사항 카테고리
    * 기능 요구
    * 비기능 요구
      * Ex. 제한 사항: 반응 속도, 메모리 소비, 사용자 친화 등등
* 설계-Design
  > 요소별로 나누고, 또, 요소들의 관계와 의존성을 정리함으로써 전반적인 구조 정립 
  * System design
  * Detail design
* Implementation and Unit Testing
  * 구현 및 구성 요소 별로 테스트
* Integration and System Testing
  * 전체적으로 통합 및 테스트
* Maintenance
  * 버그 수정
  * 퍼포먼스 향상
  * 기능 또는 서비스 강화
  * 새로운 환경에 적응

### 1.3.2. Software Development Processes
* **Waterfall Model**
  * 가장 잘 알려진 개발 과정
  * 산업적으로 표준화 된 모델
  * 한 번 정해진 걸 다시 변경하는 것을 최소화하는 모델.
    * 각각 잡업의 페이즈마다 철저하게 완료한다.
    * 한 번 승인된 거나 전달된 것은 바꾸지 않는다.
  * 현실적이지 않다.
  * 폭포처럼 한 단계씩 넘어가는 것.
  * Requirements -> Design -> Implementation and Unit Test -> Integration and System Testing -> Maintenance
  * 바로 이전 단계로는 돌아가되 그 이상으로는 돌아갈 수 없는 특징이 있다.

### 1.4. Desirable Software System
1. Usefulness
   * 고객의 니즈를 충족한 것
2. Timeliness
   * 고객에게 시의적절하게 완성되고, 전달되는 것
3. Reliability
   * 에러없이 정확하게 기능을 수행하는 것
4. Maintainability
   * 유지보수에 용이한 것
   * 달라진 상황과 환경에 따라 고칠 수 있게 범용성있는 것
   * 비용없이 확장 가능한 것
5. Reusability
   * 다른 컨텍스트에서도 사용 가능한 것
6. User Friendliness
   * 사용자가 접근하고 사용하기 쉬운 것
7. Efficiency
   * 시스템 리소스를 낭비하지 않고 효율적으로 사용하는 것
* Trade - Off
  * 위에 언급된 모든 내용을 같은 시간에 할 수 없기 때문에 각각을 조화롭게 하는 것.
  * Ex. 유지보수에 용이하게 만들다 보면 개발 일정이 미뤄졌다면 Maintainability 과 Timeliness 을 조율하는 것
* Maintainability의 중요성
  * 장기적으로 봤을 때는 유지보수 비용이 개발 비용 보다 더 많이 들기 때문
  * 어떤 소프트웨어던지 초기 버전에는 Reliability가 낮기 때문에
  * High Maintainability는 소프트웨어 시스템의 설계와 구현에 있어서 Flexibility 를 가져야 한다.

### 1.4.1. 유지보수에 유리한 소프트웨어의 요소
1. Flexibility
    * 쉽게 바꿀 수 있어야 한다.
    * 에러가 locally 해야 한다 - 한가지 에러를 고치기 위해 여러 곳을 고치도록 하지 않아야 한다.
    * 뭔가를 바꿨을 때 그 영향이 small regions로 제한
2. Simplicity
   * 간단해야 에러가 적다.
   * 코드가 부분적으로 나눠져 효율적인 사용으로 단순화 되어야 한다.(Divide and Conquer)
3. Readability
   * 이해하기 쉬워야 한다.
   * 코드, 구현, 문서화의 형태가 간단명료해야 한다.

### 1.5. Modeling
* Abstraction
  * 불필요한 부분을 생략하고 객체의 속성 중 필수적이고, 관련있는 특성을 잡는 것이다.
  * 자바에서 추상화의 기본적인 예를 들자면 부모클래스에 함수를 선언하고, 자식클래스이 공통적인 것은 놔두고 자신에게 필요한 것 만을 재정의하는 것으로 추상화를 구현할 수 있다.
  * 또는, 공통적인 것은 추상클래스 내에서 지정하고 나머지는 하위클래스에서 재정의하는 것.
* Interpretation
  * 추상화를 해석하는 것을 의미한다.

### 1.5.1. Evolution of Programming Models
* Computation-oriented models
  * 알고리즘에 집중
  * 문제해결, 효율적인 알고리즘 설계, 계산의 복잡성 제어가 주 된 문제
  * 복잡한 시스템의 Decomposition(분해)은 Control flow에 기초한다.
* Data-Oriented Model
  * 처리되는 데이터의 복잡성을 해결하고자 한다.
  * 데이터의 구조과 데이터의 플로우에 초점을 두었다.
  * 복잡한 시스템의 Decomposition(분해)은 data flow에 기초한다.
* Object-Oriented Model
  * data와 computation의 관점이 균형을 이룬다.
  * 객체들로 구성된다.
  * 복잡한 시스템의 Decomposition(분해)은 객체의 구조, 클래스의 관계에 기초한다.

### 1.6. Iterative Development
#### 1.6.1. Booch's iterative OOD processes
* Micro Processes
  1. 클래스 식별
  2. semantics 식별 (attributes and behaviors of 클래스)
  3. 클래스 간의 관계 식별
  4. 클래스 인터페이스 정의
  5. 클래스 구현
  6. 반복

* Macro Processes
  1. Micro process의 제어 프레임워크 역할을 한다.
  2. 분석, 모델링, 설계, 구형, 보수를 진행(시간순이 아닌 그때그때 필요하면 진행하는 Activities)
  3. RUP(Rational Unified Process) - complete  
  RUP 과정 후 완성
  4. XP(Extreme Programming) - lightweight  
  짜보고 생각

#### 1.6.2. OO Development Activities
1. Conceptualization
2. OO analysis and modeling
3. OO Design
4. Implementation
5. Maintanance

* Iterative Development Processes
  * 변경사항을 관리하고 용이하게 하기 위함
  * 각각의 iteration은 비교적 작고, 비교적 짧은 기간에 완성된 것이다.
  * 실행가능한 결과물이 나온 것.

* RUP
  * 하나가 아닌 다양한 개발 프로세스가 통합된 것

* RUP의 핵심 수행(Key Practices)
  * iteratively 하게 개발
  * 바뀌는 요구사항 반영
  * 구성요소 기반 구조를 사용
  * UML 활용
  * 소프트웨어의 퀄리티 향상
  * 소프트웨어의 체인지 제어

* XP의 핵심 수행
  * 배포를 자주
  * 디자인은 간단하게, 필요하다면 리팩토링
  * Test를 먼저한다.
  * Refactoring(시스템을 간단명료하게 하고, 중복 코드를 줄이기 위해)
  * Pair Programming
  * 누구나 코드를 변경할 수 있다.
  * iteration마다 계속해서 통합(integration)
  * 일주일에 40시간만 일한다.
  * 고객과 함께 일한다.

* RUP vs. XP
  * RUP: UML로 객체지향모델을 만드는 것을 강조
  * XP: 실행가능한 코드를 만드는 것을 강조
  * iterative 개념을 공유


### Conclusion
OODP를 알아야 한다.