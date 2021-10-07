#lang plai
;[contract]: infix-parse: sexp -> AE
;            interp: AE -> number

;[purpose]: infix-parse: to convert sexp into AE
;           interp: consumes an AE and compute the corresponding number

;[tests]:

; infix-parse
;(test (infix-parse'{{3 + 4} + {5 - 1}}) (add (add (num 3) (num 4)) (sub (num 5) (num 1))))
;(test (infix-parse '{{9 - 4} + {5 - 2}}) (add (sub (num 9) (num 4)) (sub (num 5) (num 2))))
;(test (infix-parse '{{20 + 11} + {5 - 3}}) (add (add (num 20) (num 11)) (sub (num 5) (num 3))))
;(test (infix-parse '{{3 * 4} + {5 - 4}}) (add (mul (num 3) (num 4)) (sub (num 5) (num 4))))
;(test (infix-parse '{{8 / 4} + {5 - 5}}) (add (div (num 8) (num 4)) (sub (num 5) (num 5))))

; interp
;(test (interp (infix-parse '{{3 + 4} + {5 - 1}})) 11)
;(test (interp (infix-parse '{{9 - 4} + {5 - 2}})) 8)
;(test (interp (infix-parse '{{20 + 11} + {5 - 3}})) 33)
;(test (interp (infix-parse '{{3 * 4} + {5 - 4}})) 13)
;(test (interp (infix-parse '{{8 / 4} + {5 - 5}})) 2)

(define-type AE
  [num (n number?)]
  [add (lhs AE?) (rhs AE?)]
  [sub (lhs AE?) (rhs AE?)]
  [mul (lhs AE?) (rhs AE?)]
  [div (lhs AE?) (rhs AE?)]
  )

(define (interp an-ae)
  (type-case AE an-ae
    [num (n) n]
    [add (lhs rhs) (+ (interp lhs) (interp rhs))]
    [sub (lhs rhs) (- (interp lhs) (interp rhs))]
    [mul (lhs rhs) (* (interp lhs) (interp rhs))]
    [div (lhs rhs) (/ (interp lhs) (interp rhs))]))

(define (infix-parse sexp)
  (match sexp
    [(? number?) 			(num sexp)]
    [(list lhs '+ rhs)			(add (infix-parse lhs) (infix-parse rhs))]
    [(list lhs '- rhs)			(sub (infix-parse lhs) (infix-parse rhs))]
    [(list lhs '* rhs)			(mul (infix-parse lhs) (infix-parse rhs))]
    [(list lhs '/ rhs)			(div (infix-parse lhs) (infix-parse rhs))]
    [else (error 'parse "bad syntax:~a" sexp)]))

(test (infix-parse'{{3 + 4} + {5 - 1}}) (add (add (num 3) (num 4)) (sub (num 5) (num 1))))
(test (infix-parse '{{9 - 4} + {5 - 2}}) (add (sub (num 9) (num 4)) (sub (num 5) (num 2))))
(test (infix-parse '{{20 + 11} + {5 - 3}}) (add (add (num 20) (num 11)) (sub (num 5) (num 3))))
(test (infix-parse '{{3 * 4} + {5 - 4}}) (add (mul (num 3) (num 4)) (sub (num 5) (num 4))))
(test (infix-parse '{{8 / 4} + {5 - 5}}) (add (div (num 8) (num 4)) (sub (num 5) (num 5))))

(test (interp (infix-parse '{{3 + 4} + {5 - 1}})) 11)
(test (interp (infix-parse '{{9 - 4} + {5 - 2}})) 8)
(test (interp (infix-parse '{{20 + 11} + {5 - 3}})) 33)
(test (interp (infix-parse '{{3 * 4} + {5 - 4}})) 13)
(test (interp (infix-parse '{{8 / 4} + {5 - 5}})) 2)