;Define program last, that gives you the last element of a list
(define last
  (lambda (ls)
    (if (null? (cdr ls))
        (car ls)
    (last (cdr ls)))))

;Define a function which calculates length of a list
(define len
  (lambda (ls)
    (if (null? ls)
        0
        (+ 1 (len (cdr ls))))))

;Define the predicate atom?, which returns true if its argument is not a pair and false if it is.
(define atom?
  (lambda (p)
    (if (pair? p)
        #false
        #true)))

;define the procedure shorter, which returns the shorter of two list arguments. Have it return the first list if they have the same length.
(define shorter
  (lambda (ls1 ls2)
    (if (< (length ls2) (length ls1))
        ls2
        ls1)))