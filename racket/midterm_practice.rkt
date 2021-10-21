#lang plai
(define-type AE
  [num (n number?)]
  [add (lhs num?)
       (rhs num?)]
  [sub (lhs num?)
       (rhs num?)]);

(add (num 1) (num 2));