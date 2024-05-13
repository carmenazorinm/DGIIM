#lang racket
; Exercise 1
(define duplicate
    (lambda (ls)
      (if (= (length ls) 1) (list  (car ls)  (car ls))
          (list (car ls) (car ls) (duplicate (cdr ls))))))

; Exercise 2
(define double-factorial
  (lambda (n)
    (if (< n 2)
        1
        (* n (double-factorial (- n 2))))))

; Exercise 3
(define state1 1)
(define state2 1)
(define state3 1)

(define exp
  (lambda (n m)
    (if (<= m 1)
        n
        (* n (exp n (- m 1))))))

(define random
  (lambda ()
    (let ((first-product (* 1176 state1)) (second-product (* 1476 state2)) (third-product (* 1776 state3)) (exponent (exp 2 32)))
      (set! state3 second-product)
      (set! state2 first-product)
      (set! state1 (modulo (+ (+ first-product second-product) third-product) (- exponent 5)))
      first-product)))

; Exercise 4
(define find-lower
  (lambda (ls minimo)
    (cond
      ((empty? ls) minimo)
      ((< (car ls) minimo) (find-lower (cdr ls) (car ls)))
      (else (find-lower (cdr ls) minimo)))))

(define minimal
  (lambda (ls)
    (find-lower ls (car ls))))

; Exercie 5
(define f
  (lambda (ls c)
    (if (= c 0) (* 1 (car ls))
        (+ (* (car ls) (exp 2 c)) (f (cdr ls) (- c 1))))))

(define bin2dec
  (lambda (ls)
   (f ls (- (length ls) 1))))

(define bin2dec2
  (lambda (ls)
    (let ((pos (- (length ls) 1)))
      (if (= pos 0) (* 1 (car ls))
          (+ (* (car ls) (exp 2 pos)) (bin2dec2 (cdr ls)))))))
