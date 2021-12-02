## 1. R기초
### 1.1. 주석과 도움말
주석 표기 `#`  
함수, 패키지 등에 대한 설명을 얻고 싶을 때는 ?, hlep를 이용할 수 있다.
```R
# This is comments
?print
help(print)
```

### 1.2. 패키지 설치
```R
install.packages("randomForest")
library("randomForest")
update.packages("rpart")
```

### 1.3. 기본 연산자
```R
2+2
2-2
2*2
2/2
2%%2 # 나머지
3%/%2 # 몫
```