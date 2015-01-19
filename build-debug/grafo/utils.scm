(define-module (grafo utils)
  #:use-module (oop   goops)
  #:use-module (srfi  srfi-1)
  #:use-module (ice-9 q)
  #:export (null
	    obj->string
	    choose))

(define (obj->string x)
  (call-with-output-string
   (lambda (out)
     (display x out))))

(define null '())

(define (choose lst)
  (list-ref lst (random (length lst))))
