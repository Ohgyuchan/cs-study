#lang plai

; RFAE definition
(define-type RCFAE
    [num (n number?)]
    [add (lhs RCFAE?) (rhs RCFAE?)]
    [sub (lhs RCFAE?) (rhs RCFAE?)]
    [mul (lhs RCFAE?) (rhs RCFAE?)]
    [id  (name symbol?)]
    [fun (param symbol?) (body RCFAE?)]
    [app (fun-expr RCFAE?) (arg-expr RCFAE?)]
    [if0 (test-expr RCFAE?) (then-expr RCFAE?) (else-expr RCFAE?)]
    [rec (name symbol?) (named-expr RCFAE?) (fst-call RCFAE?)])

; RFAE-Value
(define-type RCFAE-Value
    [numV (n number?)]
    [closureV (param symbol?)
              (body RCFAE?)
              (ds DefrdSub?)])

; DefrdSub
(define-type DefrdSub
    [mtSub]
    [aSub     (name symbol?)
              (value RCFAE-Value?)
              (ds DefrdSub?)]
    [aRecSub  (name symbol?)
              (value-box (box/c RCFAE-Value?))
              (ds DefrdSub?)])

; lookup : symbol DefrdSub -> RCFAE-Value
(define (lookup name ds)
    (type-case DefrdSub ds
        [mtSub  () (error 'lookup "free variable")]
        [aSub    (sub-name val rest-ds)
                            (if (symbol=? sub-name name)
                                val
                                (lookup name rest-ds))]
        [aRecSub (sub-name val-box rest-ds)
                          (if (symbol=? sub-name name)
                              (unbox val-box)
                              (lookup name rest-ds))]))


; parse: sexp -> RCFAEaSub.getStrName()
; purpose: to convert sexp to RCFAE
(define (parse sexp)
  (match sexp
    [(? number?)                    (num sexp)]
    [(list '+ l r)                  (add (parse l) (parse r))]
    [(list '- l r)                  (sub (parse l) (parse r))]
    [(list '* l r)                  (mul (parse l) (parse r))]
    [(list 'with (list i v) e)      (app (fun i (parse e)) (parse v))]
    [(? symbol?)                    (id sexp)]
    [(list 'fun (list p) b)         (fun p (parse b))]
    [(list f a)                     (app (parse f) (parse a))]
    [(list 'if0 test-expr then-expr else-expr) (if0 (parse test-expr) (parse then-expr) (parse else-expr))]
    [(list 'rec (list name named-expr) body)
                                    (rec name (parse named-expr) (parse body))]
    [else                           (error 'parse "bad syntax: ~a" sexp)]))

(define (num-op op)
  (lambda (x y)
    (num (op (numV-n x) (numV-n y)))))
; num+: FAE FAE -> FAE
(define num+ (num-op +))
; num-: FAE FAE -> FAE
(define num- (num-op -))
; num*: RCFAE RCFAE -> FAE
(define num* (num-op *))

; numzero? :  RCFAE-Value -> boolean
(define (numzero? n)
    (zero? (numV-n n)))

; interp : RCFAE DefrdSub -> RCFAE-Value
(define (interp rcfae ds)
    (type-case RCFAE rcfae
        [num (n) (numV n)]
        [add  (l r) (num+ (interp l ds) (interp r ds))]
        [sub  (l r) (num- (interp l ds) (interp r ds))]
        [mul  (l r) (num* (interp l ds) (interp r ds))]
        [id   (name) (lookup name ds)]
        [fun  (param body-expr) (closureV param body-expr ds)]
        [app  (f a) (local [(define ftn (interp f ds))]
                                    (interp (closureV-body ftn)
                                                  (aSub (closureV-param ftn)
                                                        (interp a ds)
                                                        (closureV-ds ftn))))]
        [if0   (test-expr then-expr else-expr) 
                (if (numzero? (interp test-expr ds))
                    (interp then-expr ds)
                    (interp else-expr ds))]
        [rec  (bound-id named-expr fst-call)
                (local ([define value-holder (box (numV 1729))]
                        [define new-ds (aRecSub bound-id value-holder ds)]
                        [define named-expr-val (interp named-expr new-ds)])
                        (begin 
                          (set-box! value-holder (interp named-expr new-ds))
                          (interp fst-call new-ds)))]))
                          



; run
(define (run sexp ds)
  (interp (parse sexp) ds))

; (parse '{rec {count {fun {n} {if0 n 0 {+ 1 {count {- n 1}}}}}} {count 8}})
; (interp '{rec {count {fun {n} {if0 n 0 {+ 1 {count {- n 1}}}}}} {count 8}} (mtSub))
; (run '{rec {count {fun {n} {if0 n 0 {+ 1 {count {- n 1}}}}}} {count 8}} (mtSub))
(test (interp (parse '{rec {fac {fun {x} {if0 x 1 {* x {fac {+ x -1}}}}}} {fac 10}}) (mtSub)) (numV 3628800))