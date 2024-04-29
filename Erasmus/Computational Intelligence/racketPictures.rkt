#lang slideshow
;Define the procedure chessboard given its dimension
(define black_square (colorize (filled-rectangle 10 10) "black"))
(define white_square (colorize (rectangle 10 10) "black"))

(define (draw_black_line n)
  (if (= n 1)
      black_square
      (if (even? n)
          (hc-append white_square (draw_black_line (- n 1)))
          (hc-append black_square (draw_black_line (- n 1))))))

(define (draw_white_line n)
  (if (= n 1)
      white_square
      (if (even? n)
          (hc-append black_square (draw_white_line (- n 1)))
          (hc-append white_square (draw_white_line (- n 1))))))

(define (board f c)
  (if (= f 1)
      (draw_black_line c)
      (if (even? f)
          (vc-append (draw_white_line c) (board (- f 1) c))
          (vc-append (draw_black_line c) (board (- f 1) c)))))

(define (chessboard n) (board n n))


