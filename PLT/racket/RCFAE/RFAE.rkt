#lang plai

(define-type RFAE
    [num (n number?)]
    [add (l RFAE?) (r RFAE?)]
    [sub (l RFAE?) (r RFAE?)]
    [mul (l RFAE?) (r RFAE?)]
    [id (name symbol?)]
    [fun (param symbol?) (body RFAE?)]
    [app (fun-expr RFAE?) (arg-expr RFAE?)]
    [if0 (test-expr RFAE?) (then-expr RFAE?) (else-expr RFAE?)]
    [rec (name symbol?) (named-expr RFAE?) (fst-call RFAE?)])

(define-type RFAE-Value
    [numV (n number?)]
    [closureV (param symbol?) (body RFAE?) (ds DefrdSub?)])

; boxed-RFAE-Value? : any -> boolean
; returns true if given value is a boxed RFAE-Value

(define (boxed-RFAE-Value? value)
    (and    (box? value)
            (RFAE-Value? (unbox value))))

(define-type DefrdSub
    [mtSub]
    [aSub (key symbol?) (value RFAE-Value?) (ds DefrdSub?)]
    [aRecSub (key symbol?) (value-box boxed-RFAE-Value?) (ds DefrdSub?)])

; parse : sexp -> RFAE
(define (parse sexp)
    (match sexp
    [(? number? n)                                          (num n)]
    [(list '+ l r)                                          (add (parse l) (parse r))]
    [(list '- l r)                                          (sub (parse l) (parse r))]
    [(list '* l r)                                          (mul (parse l) (parse r))]
    [(? symbol? v)                                          (id v)]
    [(list 'fun (list (? symbol? param)) body)              (fun param (parse body))]
    [(list fun-expr arg-expr)                               (app (parse fun-expr) (parse arg-expr))]
    [(list 'if0 test-expr then-expr else-expr)                         (if0 (parse test-expr) (parse then-expr) (parse else-expr))]
    [(list 'with (list (? symbol? name) named-expr) body)   (app (fun name (parse body)) (parse named-expr))]
    [else                                                   (error 'parse "bad syntax: ~a" sexp)]))

(define (num-op op)
    (lambda (x y)
        (numV (op (numV-n x) (numV-n y)))))

; num+: FAE FAE -> FAE
(define num+ (num-op +))

; num-: FAE FAE -> FAE
(define num- (num-op -))

; num*: FAE FAE -> FAE
(define num* (num-op *))

; num-zero? : numV -> boolean
(define (num-zero? n)
    (zero? (numV-n n)))

; lookup : symbol DefrdSub -> RFAE-Value
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

; cyclically-bind-and-interp : symbol fun ds -> ds
(define (cyclically-bind-and-interp bound-id named-expr ds)
    (local [(define value-holder (box (numV 198)))
            (define new-ds (aRecSub bound-id value-holder ds))
            (define named-expr-val (interp named-expr new-ds))]
            (begin
                (set-box! value-holder named-expr-val)
                new-ds)))


(define (interp expr ds)
    (type-case RFAE expr
        [num(n)                 (numV n)]
        [add(l r)               (num+ (interp l ds) (interp r ds))]
        [sub(l r)               (num- (interp l ds) (interp r ds))]
        [mul(l r)               (num* (interp l ds) (interp r ds))]
        [id(v)                  (lookup v ds)]
        [fun(param body)        (closureV param body ds)]
        [app(fun-expr arg-expr)
                                (cond
                                [(eq? (local   [(define fun-val (interp fun-expr ds))
                                                (define arg-val (interp arg-expr ds))]
                                                (interp (closureV-body fun-val)
                                                        (aSub   (closureV-param fun-val)
                                                                arg-val
                                                                (closureV-ds fun-val)))) 'lookup)
                                                        (rec (fun-expr-param arg-expr fun-expr-body)
                                (interp bound-body
                                        (cyclically-bind-and-interp bound-id
                                                                    named-expr
                                                                    ds)))]
                                                                    [else (local [(define fun-val (interp fun-expr ds))
                                        (define arg-val (interp arg-expr ds))]
                                        (interp (closureV-body fun-val)
                                                (aSub   (closureV-param fun-val)
                                                        arg-val
                                                        (closureV-ds fun-val))))])]
        [if0(test-expr then-expr else-expr)
                                (local [(define test-expr-val (interp test-expr ds))]
                                        (if (num-zero? test-expr-val)
                                            (interp then-expr ds)
                                            (interp else-expr ds)))]
        [rec (bound-id named-expr bound-body)
                                (interp bound-body
                                        (cyclically-bind-and-interp bound-id
                                                                    named-expr
                                                                    ds))]))

; run
(define (run sexp)
    (interp (parse sexp) (mtSub)))

; (run '{with {fac {fun {x} {if0 x 1 {* x {fac {+ x -1}}}}}} {fac 10}} )
; (run '{with {count {fun {n} 0}} {with {count {fun {n} {if0 n 0 {+ 1 {count {- n 1}}}}}} {count 8}}})
; (run '{rec {count {fun {n} {if0 n 0 {+ 1 {count {- n 1}}}}}} {count 8}})
(parse '{with {count {fun {n} {if0 n 0 {+ 1 {count {- n 1}}}}}} {count 8}})
