# Swift 기본 문법

1. 콘솔로그, 문자열 보간법
```swift
print("Hello, World!")
dump("Hello, World!")
```

2. 상수와 변수
```swift
// let 상수명: 타입 = 값
// var 변수명: 타입 = 값
let name: String = "Gyuchan" // 상수는 값을 변경할 수 없음
var age: Int = 100 // 변수는 값을 변경할 수 있음

// 상수 선언 후에 나중에 값 할당하기
let name2: String
name2 = "Gyuchan"
```
3. 기본 데이터 타입
> 타입의 암묵적 형변형을 수용하지 않고, 명시적 형변환만 가능하다. 타입을 엄격하게 체크한다.
```swift
// Bool
var someBool: Bool = true
someBool = false

someBool = 0 // 컴파일 오류 발생, Int와 Bool을 구분함
someBool = 1 // 컴파일 오류 발생, Int와 Bool을 구분함

// Int 정수
var someInt: Int = -100
someInt = 100_000_000 // 100,000,000 자릿수 나눠서 시인성 향상 가능

// UInt unsigned int, 양의 정수
var someUInt: UInt = 100
someUInt = -100 // 컴파일 오류 발생, UInt는 음수를 표현할 수 없음

// Float 실수, 32비트 부동소수형
var someFloat: Float = 3.14
someFloat = 3 // 정수를 할당해도 오류가 발생하지 않음
someFloat = 3.14e2 // 314.0, 지수 표현도 가능
someFloat = 3.14e-2 // 0.0314, 지수 표현도 가능

// Double 실수, 64비트 부동소수형
var someDouble: Double = 3.14
someDouble = 3
someDouble = 3.14e2
someDouble = 3.14e-2
someFloat = someDouble // Float에 Double 할당 불가 - 컴파일 오류 발생

// Character 문자, 유니코드 사용
var someCharacter: Character = "🇰🇷"
someCharacter = "😄"
someCharacter = "가"
someCharacter = "A"
someCharacter = "ㄱ"

// String 문자열, 유니코드 사용
var someString: String = "하하하 😄"
someString = someString + "웃으면 복이와요" // 문자열 결합
someCharacter = someString // 컴파일 오류 발생
someString = someCharacter // 컴파일 오류 발생
someString = String(someCharacter) // 문자열로 타입 변환

var someAny: Any = 100
someAny = "어떤 타입도 수용 가능합니다"
someAny = 123.12
someDouble = someAny // 컴파일 오류 발생 
someAny = someDouble // 가능

class SomeClass {}
var someAnyObject: AnyObject = SomeClass() // AnyObject는 클래스의 인스턴스만 수용 가능
someAnyObject = 123.12 // 컴파일 오류 발생


```
