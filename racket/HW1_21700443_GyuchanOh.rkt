#lang plai

;Problem 1:
;Solved by myself: Y
;Time taken: about 2 mins
;[contract] dollar->won: number-> number
;[purpose]: To convert dollar to won
;[tests]: (test (dollar->won 1) 1162)
;         (test (dollar->won 5) 5810)
(define (dollar->won d)
  (* d 1162))

(test (dollar->won 1) 1162)
(test (dollar->won 5) 5810)

;Problem 2:
;Solved by myself: Y
;Time taken: about 2 mins
;[contract] digit_sum: number number number -> number
;[purpose]: To sum three integer numbers
;[tests]: (test (digit_sum 1 2 3) 6)
;         (test (digit_sum 10 2 3) 15)

(define (digit_sum a b c)
  (+ a b c))

(test (digit_sum 1 2 3) 6)
(test (digit_sum 10 2 3) 15)

;Problem 3:
;Solved by myself: Y
;Time taken: about 2 mins
;[contract] inchworm-travel: number number -> number
;[purpose]: To get the distance an Inchworm can travel in that time in centimeters
;[tests]: (test (inchworm-travel 1 2) 5.08)
;         (test (inchworm-travel 5 2) 25.4)
(define (inchworm-travel n hours)
  (* n hours 2.54))

(test (inchworm-travel 1 2) 5.08)
(test (inchworm-travel 5 2) 25.4)


;Problem 4:
;Solved by myself: Y
;Time taken: about 2 mins
;[contract] inchworm-travel: number -> boolean
;[purpose]: To know if the given number is an odd number
;[tests]: (test (is-odd 3) #t)
;         (test (is-odd 4) #f)
(define (is-odd? n)
  (= (modulo n 2) 1))

(test (is-odd? 3) #t)
(test (is-odd? 4) #f)

;Problem 5
;Solved by myself: Y
;Time taken: about 20 mins
;[contract] combination: number number -> number
;           factorial: number -> number
;[purpose]: To get the number of combinations
;[tests]: (test (factorial 3) 6)
;         (test (factorial 5) 120) 
;         (test (combination 3 2) 3)
;         (test (combination 10 2) 45)
(define (factorial n)
  (cond
    [(= n 1) 1]
    [else (* n (factorial (- n 1)))]
  )
)

(define (combination n k)  
    (/ (factorial n) (* (factorial (- n k)) (factorial k))))


(test (factorial 3) 6)
(test (factorial 5) 120)

(test (combination 3 2) 3)
(test (combination 10 2) 45)

;Problem 6
;Solved by myself: Y
;Time taken: about 30 mins
;[contract] have-courses: PERSON -> number
;           ready-to-graduate: PERSON -> boolean
;[purpose]: PERSON: To define type has three variants(Professor, UndergraduateStudent, GraduateStudent)
;           have-courses: To get the number of courses taken or taught for the given person
;           ready-to-graduate: To check that the person given is a graduate student and check that GraduateStudent is ready to graduate
;[tests]: (test (have-courses p) 2)
;         (test (have-courses us) 3)
;         (test (have-courses gs1) 4)
;         (test (have-courses gs2) 5)
;         (test (ready-to-graduate p) #f)
;         (test (ready-to-graduate us) #f)
;         (test (ready-to-graduate gs1) #t)
;         (test (ready-to-graduate gs2) #f)
(define-type PERSON
  [Professor (courses number?)
             (projects number?)]
  [UndergraduateStudent (courses number?)]
  [GraduateStudent (courses number?)
                   (papers number?)]
)

(define (have-courses person)
  (type-case PERSON person
    [Professor (courses projects) courses]
    [UndergraduateStudent (courses) courses]
    [GraduateStudent (courses papers) courses]
  )
)
    

(define (ready-to-graduate person)
  (cond
    [(GraduateStudent? person)
     (cond
       [(>= (GraduateStudent-papers person) 3) #t]
       [else #f]
     )
    ]
    [else #f]
  )
)

(define p(Professor 2 5))
(define us(UndergraduateStudent 3))
(define gs1(GraduateStudent 4 4))
(define gs2(GraduateStudent 5 2))

(test (have-courses p) 2)
(test (have-courses us) 3)
(test (have-courses gs1) 4)
(test (have-courses gs2) 5)

(test (ready-to-graduate p) #f)
(test (ready-to-graduate us) #f)
(test (ready-to-graduate gs1) #t)
(test (ready-to-graduate gs2) #f)

;Problem 7
;Solved by myself: N(I didn't get help from anyone else, but I saw the example code about for-statement from https://docs.racket-lang.org/guide/for.html)
;Time taken: about 30 mins
;[contract] name-alphabet: list -> list
;[purpose]: name-alphabet: To get a corresponding list of an alphabetical character  with names starting with the alphabet character
;[tests]: (test (name-alphabet '(a b c)) '(alice unnamed cherry))
;         (test (name-alphabet '(a c j k)) '(alice cherry jc kate))
(define (name-alphabet alphabets)
  (for/list ([i alphabets])
    (cond
      [(equal? i 'a) 'alice]
      [(equal? i 'c) 'cherry]
      [(equal? i 'j) 'jc]
      [(equal? i 'k) 'kate]
      [else 'unnamed]
    )
  )
)


(test (name-alphabet '(a b c)) '(alice unnamed cherry))
(test (name-alphabet '(a c j k)) '(alice cherry jc kate))

;Problem 8
;Solved by myself: Y
;Time taken: about 10 mins
;[contract] update-name symbol symbol list -> list
;[purpose]: update-name To get a corresponding list of an alphabetical character  with names starting with the alphabet character
;[tests]:
(define (update-name old new slst)
  (for/list ([i slst])
    (cond
      [(equal? i old) new]
      [else i]
    )
  )
)

(test (update-name 'cherry 'claire (cons 'jc (cons 'cherry (cons 'kate empty)))) '(jc claire kate))
(test (update-name 'jc 'JC (cons 'jc (cons 'jc (cons 'kate (cons 'cherry (cons 'jc empty)))))) '(JC JC kate cherry JC))