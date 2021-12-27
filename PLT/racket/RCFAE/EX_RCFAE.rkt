#lang plai

(define-type RFAE
  [num (n number?)]
  [add (l RFAE?) (r RFAE?)]
  [mul (l RFAE?) (r RFAE?)]
  [id (name symbol?)]
  [fun (param symbol?) (body RFAE?)]
  [app (fun-expr RFAE?) (arg-expr RFAE?)]
  [if0 (pred RFAE?) (truth RFAE?) (falsity RFAE?)]
  [rec (name symbol?) (named-expr RFAE?) (body RFAE?)])

(define-type RFAE-Value
    [nV]
    [numV (n number?)]
    [closureV (param symbol?) (body RFAE?) (ds DefrdSub?)])

;; boxed-RFAE-Value? : any -> boolean
;; returns true if given value is a boxed RFAE-Value

(define (boxed-RFAE-Value? value)
  (and (box? value)
      (RFAE-Value? (unbox value))))

(define-type DefrdSub
  [mtSub]
  [aSub (key symbol?) (value RFAE-Value?) (ds DefrdSub?)]
  [aRecSub (key symbol?) (value boxed-RFAE-Value?) (ds DefrdSub?)])

;; parse : sexp -> RFAE
;; converts given S-expression to RFAE expression

(define (parse sexp)
  (match sexp
    [(? number? n) (num n)]
    [(list '+ l r) (add (parse l) (parse r))]
    [(list '* l r) (mul (parse l) (parse r))]
    [(? symbol? v) (id v)]
    [(list 'fun (list (? symbol? param)) body)
     (fun param (parse body))]
    [(list fun-expr arg-expr) (app (parse fun-expr) (parse arg-expr))]
    [(list 'if0 pred truth falsity)
     (if0 (parse pred) (parse truth) (parse falsity))]
    [(list 'with (list (? symbol? name) named-expr) body)
     (app (fun name (parse body)) (parse named-expr))]
    [(list 'rec (list (? symbol? name) named-expr) body)
     (rec name (parse named-expr) (parse body))]))

;; num-op : op numV numV -> numV
;; applies given operation on given two numbers

(define (num-op op n1 n2)
  (numV (op (numV-n n1) (numV-n n2))))

;; num-zero? : numV -> boolean
;; returns true if given numV value is zero

(define (num-zero? n)
  (zero? (numV-n n)))

;; lookup : symbol DefrdSub -> RFAE-Value
;; looks up given name in given environment

(define (lookup name ds)
  (local [(define (lookup-helper name ds)
            (type-case DefrdSub ds
              [mtSub () (error 'lookup "free identifier")]
              [aSub (key value ds)
                    (if (symbol=? name key)
                        value
                        (lookup-helper name ds))]
              [aRecSub (key boxed-value ds)
                       (if (symbol=? name key)
                           (unbox boxed-value)
                           (lookup-helper name ds))]))
          (define val (lookup-helper name ds))]
    (if (nV? val)
        (error "no value assigned")
        val)))

;; cyclically-bind-and-interp : symbol fun ds -> ds
(define (cyclically-bind-and-interp bound-id named-expr ds)
  (local [(define value-holder (box (nV)))
          (define new-ds (aRecSub bound-id value-holder ds))
          (define named-expr-val (interp named-expr new-ds))]
    (begin
      (set-box! value-holder named-expr-val)
      new-ds)))


(define (interp expr ds)
  (type-case RFAE expr
    [num (n) (numV n)]
    [add (l r) (num-op + (interp l ds) (interp r ds))]
    [mul (l r) (num-op * (interp l ds) (interp r ds))]
    [id (v) (lookup v ds)]
    [fun (param body) (closureV param body ds)]
    [app (fun-expr arg-expr)
         (local [(define fun-val (interp fun-expr ds))
                 (define arg-val (interp arg-expr ds))]
           (interp (closureV-body fun-val)
                   (aSub (closureV-param fun-val)
                         arg-val
                         (closureV-ds fun-val))))]
    [if0 (pred truth falsity)
         (local [(define pred-val (interp pred ds))]
           (if (num-zero? pred-val)
               (interp truth ds)
               (interp falsity ds)))]
    [rec (bound-id named-expr bound-body)
         (interp bound-body
                 (cyclically-bind-and-interp bound-id
                                             named-expr
                                             ds))]))

; run
(define (run sexp)
    (interp (parse sexp) (mtSub)))

; (run '{rec {fac {fun {x} {if0 x 1 {* x {fac {+ x -1}}}}}} {fac 10}} )
; (run '{with {count {fun {n} 0}} {with {count {fun {n} {if0 n 0 {+ 1 {count {- n 1}}}}}} {count 8}}})
(run '{rec {count {fun {n} {if0 n 0 {+ 1 {count {- n 1}}}}}} {count 8}})
