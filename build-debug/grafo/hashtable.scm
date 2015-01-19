;;; grafo/hashtable.scm
;;; Eduardo Acuña Yeomans
;;; 10/2014

(define-module (grafo hashtable)
  #:use-module (oop  goops)
  #:use-module (srfi srfi-1)
  #:export (key
	    value
	    hash-keys
	    hash-values
	    hash-tuples
	    hash-lookup
	    hash-insert!
	    hash-delete!
	    hash-vertex
	    assoc-vertex
	    hash-vertex-lookup
	    hash-vertex-insert!
	    hash-vertex-delete!
	    hash-edge
	    assoc-edge
	    hash-edge-lookup
	    hash-edge-insert!
	    hash-edge-delete!
	    hash-arrow
	    assoc-arrow
	    hash-arrow-lookup
	    hash-arrow-insert!
	    hash-arrow-delete!
	    hash-atribute
	    assoc-atribute
	    hash-atribute-lookup
	    hash-atribute-insert!
	    hash-atribute-delete!
	    set-equal?))

;;; Module for the hashtable related procedures
;;;
(define (key pair)
  (car pair))

(define (value pair)
  (cdr pair))

(define-method (hash-keys (h <hashtable>))
  (hash-map->list (λ (k v) k) h))

(define-method (hash-values (h <hashtable>))
  (hash-map->list (λ (k v) v) h))

(define-method (hash-tuples (h <hashtable>))
  (hash-map->list (λ (k v) (cons k v)) h))

(define-method (hash-lookup (h <hashtable>) k)
  (hash-get-handle h k))

(define-method (hash-insert! (h <hashtable>) k v)
  (hash-set! h k v))

(define-method (hash-delete! (h <hashtable>) k)
  (hash-remove! h k))

;;; Hash verties
;;;
(define (hash-vertex obj size)
  (hash obj size))

(define (assoc-vertex obj alist)
  (assoc obj alist))

(define-method (hash-vertex-lookup (h <hashtable>) k)
  (hash-lookup h k))

(define-method (hash-vertex-insert! (h <hashtable>) k v)
  (hash-insert! h k v))

(define-method (hash-vertex-delete! (h <hashtable>) k)
  (hash-delete! h k))

;;; Hash undirected edges
;;;
(define (set-equal? a b)
  (lset= equal? a b))

(define (hash-edge obj size)
  (remainder (+ (expt (hash-vertex (list-ref obj 0) size) 2)
		(expt (hash-vertex (list-ref obj 1) size) 2)) size))

(define (assoc-edge obj alist)
  (find (λ (pair) (set-equal? obj (car pair))) alist))

(define-method (hash-edge-lookup (h <hashtable>) k)
  (hashx-get-handle hash-edge
		    assoc-edge
		    h k))

(define-method (hash-edge-insert! (h <hashtable>) k v)
  (hashx-set! hash-edge
	      assoc-edge
	      h k v))

(define-method (hash-edge-delete! (h <hashtable>) k)
  (hashx-remove! hash-edge
		 assoc-edge
		 h k))

;;; Hash directed edges
;;;
(define (hash-arrow obj size)
  (hash obj size))

(define (assoc-arrow obj alist)
  (assoc obj alist))

(define-method (hash-arrow-lookup (h <hashtable>) k)
  (hash-lookup h k))

(define-method (hash-arrow-insert! (h <hashtable>) k v)
  (hash-insert! h k v))

(define-method (hash-arrow-delete! (h <hashtable>) k)
  (hash-delete! h k))

;;; Hash atributes
;;;
(define (hash-atribute obj size)
  (hash (keyword->symbol obj) size))

(define (assoc-atribute obj alist)
  (assoc obj alist))

(define-method (hash-atribute-lookup (h <hashtable>) k)
  (hash-lookup h k))

(define-method (hash-atribute-insert! (h <hashtable>) k v)
  (hash-insert! h k v))

(define-method (hash-atribute-delete! (h <hashtable>) k)
  (hash-delete! h k))
