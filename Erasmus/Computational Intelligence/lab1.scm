;Exercise2.2.1
(- (* 1.2 (- 2 (/ 1 3))) 8.7)
(/ (+ (/ 2 3) (/ 4 9)) (- (/ 5 11) (/ 4 3)))
(+ 1 (/ 1 (+ 2 (/ 1 (+ 1 (/ 1 2))))))
(* 1 (* -2 (* 3 (* -4 (* 5 (* -6 7))))))

;Exercise2.2.3
(cons 'car 'cdr)
(list 'this '(is silly?))
(cons 'is '(this silly?))
(quote (+ 2 3))
(cons '+ '(2 3))
(car '(+ 2 3))
(cdr '(+ 2 3))
cons
(quote cons)
(quote (quote cons))
(car (quote (quote cons)))
(+ 2 3)
(+ '2 '3)
(+ (car '(2 3)) (car (cdr '(2 3))))
((car (list + - * /)) 2 3)

;Exercise2.2.4
(car (car '((a b) (c d))))
(car (cdr (car '((a b) (c d)))))
(car (car (cdr '((a b) (c d)))))
(car (cdr (car (cdr '((a b) (c d))))))

;Exercise2.2.7
(car '((a b) (c d)))
(cdr '((a b) (c d)))

(car (car '((a b) (c d))))
(car (cdr '((a b) (c d))))
(car (car (cdr '((a b) (c d)))))

(cdr (car '((a b) (c d))))
(car (cdr (car '((a b) (c d)))))
(cdr (cdr (car '((a b) (c d)))))
(cdr (cdr '((a b) (c d))))

(cdr (car (cdr '((a b) (c d)))))
(car (cdr (car (cdr '((a b) (c d))))))
(cdr (cdr (car (cdr '((a b) (c d))))))

;Exercise2.4.1
(let ((a 1) (b 2))
 (let ((x (* 3 a)))
    (+ (- x b) (+ x b))))

(let ((a 2) (b 3) (c 5))
 (let ((x (list a b c)))
  (cons (car x) (cdr x))))

;Exercise2.4.2; solution is 54
(let ((x 9))
 (* x
    (let ((x (/ x 3)))
          (+ x x))))
; first we do solution=x*something where x=9. then something=x+x where x=x/3=9/3=3 -> something=3+3=6 -> solution=9*6=54