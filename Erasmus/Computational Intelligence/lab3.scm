; Create function member, that says if a element is in a list
#lang racket
(define member?
  (lambda (a lst)
    (cond
      [(null? lst) #f]
      [(eqv? a (car lst)) #t]
      [else (member? a (cdr lst))])))

; Create procedure remove, that removes all the ucurrences of an element in a list

(define remove
  (lambda (e lst)
    (cond
      [(null? lst) '()]
      [(eqv? e (car lst)) (remove e (cdr lst))]
      [else (cons (car lst) (remove e (cdr lst)))]
      )))

; Insert element at the beggining of the list

(define insertBeginning
  (lambda (a lst)
    (cons a lst)))

; Insert element at the end of the list

(define append
  (lambda (a lst)
    (cons lst a)))

; Insert element at a given position in the list

; Join two lists
; Define square, that calculates the square of an element
(define square
  (lambda (x)
    (* x x)))

; Create procedure that calculates the derivative of a function in a given point with given dx
(define derivate
  (lambda (f x dx)
    (/ (- (f (+ x dx)) (f x)) dx)))

; Define procedure random using: x_n+1 = (11*x_n + 13)
(define state 1)

(define random
  (lambda ()
    (set! state (modulo (+ 13 (* 11 state)) 100)) state ))

; Define procedure random with a given range
(define random_
  (lambda (n)
    (set! state (modulo (+ 13 (* 11 state)) n)) state))

; Create procedure fibonacci

(define fibonacci
  (lambda (n)
    (if (= n 0)
        0
        (let fib ((i n) (a1 1) (a2 0))
          (if (= 1 i)
              a1
              (fib (- i 1) (+ a1 a2) a1))))))

(define fibonacci2
  (lambda (n)
    (let fib ((i n))
    (cond
      [(= i 0) 0]
      [(= i 1) 1]
      [else (+ (fib (- i 1)) (fib (- i 2)))]))))
