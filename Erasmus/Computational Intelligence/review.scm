#lang racket
(define quadratic_formula
  (lambda (a b c)
    (let ((root1 0) (root2 0) (minusb 0) (radical 0) (divisor 0))
    (set! minusb (- 0 b))
    (set! radical (- (* b b) (* 4 (* a c))))
    (set! divisor (* 2 a))
    (set! root1 (/ (+ minusb (sqrt radical)) (* 2 a)))
    (set! root2 (/ (- minusb (sqrt radical)) (* 2 a)))
    (cons root1 root2)
    )))

(define quadratic_formula2
  (lambda (a b c)
    (let (
          (minusb (- 0 b))
          (radical (- (* b b) (* 4 (* a c))))
          (denominator (* 2 a))
          )
      (let (
            (root1 (/ (+ minusb (sqrt radical)) (* 2 a)))
            (root2 (/ (- minusb (sqrt radical)) (* 2 a)))
            )
        (cons root1 root2)
        )
     )))

(define cons_count 0)

;(define cons
;  (let ((old_cons cons))
;    (lambda (x y)
;     (set! cons_count (+ cons_count 1))
;     (old_cons x y)
;     )))

(define next 0)

(define next_number
  (lambda ()
    (set! next (+ next 1))
    next
    ))

(define count 0)

(define next_count
  (lambda ()
    (let ((v count))
      (set! count (+ 1 count))
      v)))

(define next_count2
  (let ((nextc 0))
    (lambda ()
      (let ((v nextc))
        (set! nextc (+ 1 nextc))
        v))))

; method that sums the numbers of a list
(define sum
  (lambda (lst)
    (let ((a (car lst)) (b (cdr lst)))
      (if (null? b)
          a
          (+ a (sum b))))))

; define method factorial
(define factorial
  (lambda (n)
    (if (= n 1)
        1
        (* n (factorial (- n 1))))))

; insert element in a given position of a list
(define append
  (lambda (lst a)
    (list lst a)))

(define insert
  (let ((curr_lst '()) (i 0))
    (lambda (lst pos a)
      (let ((end_lst lst))
        (set! curr_lst (list curr_lst (car end_lst)))
        (set! end_lst (cdr end_lst))
        (set! i (+ 1 i))
       (if (= i pos)
          (list curr_lst a end_lst)
           (insert lst pos a))))))

(define product
  (lambda (ls)
    (call/cc
     (lambda (break)
       (let f ((ls ls))
         (cond
           ((null? ls) 1)
           ((= (car ls) 0) (break 0))
           (else (* (car ls)) (f (cdr ls)))))))))

(define factorial2
  (lambda (n)
    (let fact ((i n))
      (if (= i 0)
          1
          (* i (fact (- i 1)))))))

(letrec ((sum (lambda (ls)
                (if (null? ls) 0 (+ (car ls) (sum (cdr ls)))))))
  (sum '(1 2 3)))

(letrec ((even?
          (lambda (x)
            (or (= x 0)
                (odd? (- x 1)))))
         (odd?
          (lambda (x)
            (and (not (= x 0))
                 (even? (- x 1))))))
  (list (even? 20) (odd? 20)))