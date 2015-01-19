;;; grafo/graph.scm
;;; Eduardo Acuña Yeomans
;;; 10/2014

(define-module (grafo graph)
  #:use-module (oop   goops)
  #:use-module (srfi  srfi-1)
  #:use-module (grafo hashtable)
  #:export (<graph>
	    <undirected-graph>
	    <directed-graph>
	    make-graph
	    make-tree
	    make-K-n-n
	    make-K-n
	    make-cicle
	    from
	    to
	    vertices
	    incident
	    adjacent
	    adjacent?
	    degree
	    edges
	    vertex?
	    edge?
	    atributes
	    atribute
	    atribute?
	    add-vertex!
	    add-vertices!
	    remove-vertex!
	    remove-vertices!
	    add-edge!
	    add-edges!
	    remove-edge!
	    remove-edges!
	    add-atribute!
	    remove-atribute!
	    populate!
	    remove-vertices-atribute!
	    remove-edges-atribute!
	    remove-arrows-atribute!
	    outcident
	    in-adjacent
	    out-adjacent
	    in-adjacent?
	    out-adjacent?
	    in-degree
	    out-degree
	    arrows
	    arrow?
	    add-arrow!
	    add-arrows!
	    remove-arrow!
	    remove-arrows!)
  #:re-export (key
	       value))

;;; Module for the graph class
;;;
;;; A graph G is a pair (V,E) where V and E are collections of objects called
;;; vertices and edges respectively; the edges establish a relationship between
;;; vertices.
;;;
;;; There are several types of graphs and each type has different rules
;;; for manipulating V and E.
;;;
;;; All graph types share the same data representation for V and E:
;;;
;;; The core data is represented as a hashtable where the key is a vertex and
;;; the value is a list of the associated edges.
;;;
;;; However this implementation of graphs contemplates the idea of associating
;;; atributes to vertices and edges.
;;;
;;; This feature is implemented as two separate hashtables that relates vertices
;;; to a hashtable of atributes and edges to a hashtable of atributes.
;;;


;;; 
;;; Class definitions
;;; 
(define-class <graph> (<object>)
  (vertex:edges     #:init-thunk make-hash-table #:getter v:es)
  (vertex:atributes #:init-thunk make-hash-table #:getter v:as)
  (edge:atributes   #:init-thunk make-hash-table #:getter e:as))

(define-class <undirected-graph> (<graph>))
(define-class <directed-graph> (<graph>))


;;;
;;; Auxiliary procedures
;;;
(define-method (from (edge <list>))
  (list-ref edge 0))

(define-method (to (edge <list>))
  (list-ref edge 1))

;;; get some value in the graph hashtable
(define-method (get-v:es (g <graph>) vertex)
  (define handle (hash-vertex-lookup (v:es g) vertex))
  (if handle (value handle) #f))

(define-method (get-v:edge (g <undirected-graph>) vertex (edge <list>))
  (define es (get-v:es g vertex))
  (cond (es   (find (λ (x) (set-equal? x edge)) es))
	(else #false)))

(define-method (get-v:arrow (g <directed-graph>) vertex (arrow <list>))
  (define as (get-v:es g vertex))
  (cond (as   (find (λ (x) (equal? x arrow)) as))
	(else #false)))

(define-method (get-v:arrow (g <graph>) v (arrow <list>))
  (define as (get-v:es g v))
  (cond (as   (find (λ (x) (equal? x arrow)) as))
	(else #false)))

(define-method (get-v:as (g <graph>) vertex)
  (define handle (hash-vertex-lookup (v:as g) vertex))
  (if handle (value handle) #f))

(define-method (get-v:atribute (g <graph>) vertex (key <keyword>))
  (define as (get-v:as g vertex))
  (cond (as  (let ((a (hash-atribute-lookup as key)))
	       (if a a #f)))
	(else #f)))

(define-method (get-e:as (g <undirected-graph>) (edge <list>))
  (define handle (hash-edge-lookup (e:as g) edge))
  (if handle (value handle) #f))

(define-method (get-e:as (g <directed-graph>) (arrow <list>))
  (define handle (hash-arrow-lookup (e:as g) arrow))
  (if handle (value handle) #f))


(define-method (get-e:atribute (g <graph>) (edge <list>) (key <keyword>))
  (define as (get-e:as g edge))
  (cond (as   (let ((a (hash-atribute-lookup as key)))
		(if a a #f)))
	(else #f)))


;;; insert into the graph hashtable
(define-method (set-v:es! (g <graph>) vertex (lst <list>))
  (hash-vertex-insert! (v:es g) vertex lst))

(define-method (set-v:edge! (g <undirected-graph>) vertex (edge <list>))
  (define es (get-v:es g vertex))
  (set-v:es! g vertex (lset-union set-equal? es (list edge))))

(define-method (set-v:arrow! (g <directed-graph>) vertex (arrow <list>))
  (define es (get-v:es g vertex))
  (set-v:es! g vertex (lset-union equal? es (list arrow))))

(define-method (set-v:as! (g <graph>) vertex table)
  (hash-vertex-insert! (v:as g) vertex table))

(define-method (set-v:atribute! (g <graph>) vertex (key <keyword>) val)
  (define as (get-v:as g vertex))
  (when as (hash-atribute-insert! as key val)))

(define-method (set-e:as! (g <undirected-graph>) (edge <list>) table)
  (hash-edge-insert! (e:as g) edge table))

(define-method (set-e:as! (g <directed-graph>) (arrow <list>) table)
  (hash-arrow-insert! (e:as g) arrow table))

(define-method (set-e:atribute! (g <undirected-graph>) (edge <list>) (key <keyword>) val)
  (define as (get-e:as g edge))
  (when as (hash-atribute-insert! as key val)))

(define-method (set-e:atribute! (g <directed-graph>) (arrow <list>) (key <keyword>) val)
  (define as (get-e:as g arrow))
  (when as (hash-atribute-insert! as key val)))

;;; remove from the graph hashtable
(define-method (del-v:es! (g <graph>) vertex)
  (hash-vertex-delete! (v:es g) vertex))

(define-method (del-v:edge! (g <undirected-graph>) vertex (edge <list>))
  (define es (get-v:es g vertex))
  (set-v:es! g vertex (lset-difference set-equal? es (list edge))))

(define-method (del-v:arrow! (g <directed-graph>) vertex (arrow <list>))
  (define es (get-v:es g vertex))
  (set-v:es! g vertex (lset-difference equal? es (list arrow))))

(define-method (del-v:as! (g <graph>) vertex)
  (hash-vertex-delete! (v:as g) vertex))

(define-method (del-v:atribute! (g <graph>) vertex (key <keyword>))
  (define as (get-v:as g vertex))
  (when as (hash-atribute-delete! as key)))

(define-method (del-e:as! (g <undirected-graph>) (edge <list>))
  (hash-edge-delete! (e:as g) edge))

(define-method (del-e:as! (g <directed-graph>) (arrow <list>))
  (hash-arrow-delete! (e:as g) arrow))

(define-method (del-e:atribute! (g <undirected-graph>) (edge <list>) (key <keyword>))
  (define as (get-e:as g edge))
  (when as (hash-atribute-delete! as key)))

(define-method (del-e:atribute! (g <directed-graph>) (arrow <list>) (key <keyword>))
  (define as (get-e:as g arrow))
  (when as (hash-atribute-delete! as key)))

;;; 
;;; Method definitions
;;; 
(define-method (vertices (g <graph>))
  (hash-keys (v:es g)))

(define-method (incident (g <undirected-graph>) v)
  (define edges (get-v:es g v))
  (cond (edges edges)
	(else (error "not a vertex" v))))

(define-method (incident (g <directed-graph>) v)
  (filter (λ (a) (equal? (to a) v)) (arrows g)))

(define-method (outcident (g <directed-graph>) v)
  (define arrows (get-v:es g v))
  (cond (arrows arrows)
	(else (error "not a vertex" v))))

(define-method (adjacent (g <undirected-graph>) v)
  (apply append (map (λ (e) (remove (λ (x) (equal? x v)) e)) (incident g v))))

(define-method (adjacent (g <directed-graph>) v)
  (append (in-adjacent g v) (out-adjacent g v)))

(define-method (in-adjacent (g <directed-graph>) v)
  (apply append (map (λ (a) (remove (λ (x) (equal? x v)) a)) (incident g v))))

(define-method (out-adjacent (g <directed-graph>) v)
  (apply append (map (λ (a) (remove (λ (x) (equal? x v)) a)) (outcident g v))))

(define-method (adjacent? (g <undirected-graph>) u v)
  (cond ((member v (adjacent g u)) #true)
	(else                      #false)))

(define-method (adjacent? (g <directed-graph>) u v)
  (cond ((member v (adjacent g u)) #true)
	(else                      #false)))

(define-method (in-adjacent? (g <directed-graph>) u v)
  (cond ((member v (in-adjacent g u)) #true)
	(else                         #false)))

(define-method (out-adjacent? (g <directed-graph>) u v)
  (cond ((member v (out-adjacent g u)) #true)
	(else                          #false)))

(define-method (degree (g <undirected-graph>) v)
  (length (adjacent g v)))

(define-method (degree (g <directed-graph>) v)
  (+ (in-degree g v) (out-degree g v)))

(define-method (in-degree (g <directed-graph>) v)
  (length (in-adjacent g v)))

(define-method (out-degree (g <directed-graph>) v)
  (length (out-adjacent g v)))

(define-method (edges (g <undirected-graph>))
  (hash-keys (e:as g)))

(define-method (arrows (g <directed-graph>))
  (hash-keys (e:as g)))

(define-method (vertex? (g <graph>) v)
  (cond ((get-v:as g v) #true)
	(else           #false)))

(define-method (edge? (g <undirected-graph>) (edge <list>))
  (cond ((get-e:as g edge) #true)
	(else              #false)))

(define-method (arrow? (g <directed-graph>) (arrow <list>))
  (cond ((get-e:as g arrow) #true)
	(else               #false)))

(define-method (atributes (g <graph>) v)
  (define as (get-v:as g v))
  (cond (as   (hash-tuples as))
	(else (error "not a vertex" v))))

(define-method (atributes (g <undirected-graph>) (edge <list>))
  (define as (get-e:as g edge))
  (cond (as   (hash-tuples as))
	(else (error "not an edge" edge))))

(define-method (atributes (g <directed-graph>) (arrow <list>))
  (define as (get-e:as g arrow))
  (cond (as   (hash-tuples as))
	(else (error "not an arrow" arrow))))

(define-method (atribute (g <graph>) v (k <keyword>))
  (get-v:atribute g v k))

(define-method (atribute (g <undirected-graph>) (edge <list>) (k <keyword>))
  (get-e:atribute g edge k))

(define-method (atribute (g <directed-graph>) (arrow <list>) (k <keyword>))
  (get-e:atribute g arrow k))

(define-method (atribute? (g <graph>) v (k <keyword>))
  (if (atribute g v k) #true #false))

(define-method (atribute? (g <undirected-graph>) (lst <list>) (k <keyword>))
  (if (atribute g lst k) #true #false))

(define-method (atribute? (g <directed-graph>) (lst <list>) (k <keyword>))
  (if (atribute g lst k) #true #false))

(define-method (add-vertex! (g <graph>) v . rest)
  (cond ((vertex? g v)
	 #false)
	(else
	 (set-v:es! g v '())
	 (set-v:as! g v (make-hash-table))
	 #true)))

(define-method (add-vertices! (g <graph>) (lst <list>))
  (for-each (λ (v) (add-vertex! g v)) lst))

(define-method (remove-vertex! (g <undirected-graph>) v)
  (cond ((vertex? g v)
	 (for-each (λ (e) (remove-edge! g e))
		   (incident g v))
	 (del-v:es! g v)
	 (del-v:as! g v)
	 #true)
	(else
	 #false)))

(define-method (remove-vertex! (g <directed-graph>) v)
  (cond ((vertex? g v)
	 (for-each (λ (out) (remove-arrow! g out))
		   (outcident g v))
	 (for-each (λ (in) (remove-arrow! g in))
		   (incident g v))
	 (del-v:es! g v)
	 (del-v:as! g v)
	 #true)
	(else
	 #false)))

(define-method (remove-vertices! (g <undirected-graph>) (lst <list>))
  (for-each (λ (v) (remove-vertex! g v)) lst))

(define-method (remove-vertices! (g <directed-graph>) (lst <list>))
  (for-each (λ (v) (remove-vertex! g v)) lst))

(define-method (add-edge! (g <undirected-graph>) (edge <list>))
  (define u (from edge))
  (define v (to edge))
  (add-vertex! g u)
  (add-vertex! g v)
  (cond ((or (edge? g edge) (equal? (from edge) (to edge)))
	 #false)
	(else
	 (set-e:as! g edge (make-hash-table))
	 (set-v:edge! g u edge)
	 (set-v:edge! g v edge)
	 #true)))

(define-method (add-arrow! (g <directed-graph>) (arrow <list>))
  (define u (from arrow))
  (define v (to arrow))
  (add-vertex! g u)
  (add-vertex! g v)
  (cond ((arrow? g arrow)
	 #false)
	(else
	 (set-e:as! g arrow (make-hash-table))
	 (set-v:arrow! g u arrow)
	 #true)))

(define-method (add-edges! (g <undirected-graph>) (lst <list>))
  (for-each (λ (e) (add-edge! g e)) lst))

(define-method (add-arrows! (g <directed-graph>) (lst <list>))
  (for-each (λ (a) (add-arrow! g a)) lst))

(define-method (remove-edge! (g <undirected-graph>) (edge <list>))
  (define u (from edge))
  (define v (to edge))
  (cond ((edge? g edge)
	 (del-e:as! g edge)
	 (del-v:edge! g u edge)
	 (del-v:edge! g v edge)
	 #true)
	(else
	 #false)))

(define-method (remove-arrow! (g <directed-graph>) (arrow <list>))
  (define u (from arrow))
  (define v (to arrow))
  (cond ((arrow? g arrow)
	 (del-e:as! g arrow)
	 (del-v:arrow! g u arrow)
	 #true)
	(else
	 #false)))

(define-method (remove-edges! (g <undirected-graph>) (lst <list>))
  (for-each (λ (e) (remove-edge! g e)) lst))

(define-method (remove-arrows! (g <directed-graph>) (lst <list>))
  (for-each (λ (a) (remove-arrow! g a)) lst))

(define-method (add-atribute! (g <graph>) v (k <keyword>) val)
  (set-v:atribute! g v k val))

(define-method (add-atribute! (g <undirected-graph>) (edge <list>) (k <keyword>) val)
  (set-e:atribute! g edge k val))

(define-method (add-atribute! (g <directed-graph>) (arrow <list>) (k <keyword>) val)
  (set-e:atribute! g arrow k val))

(define-method (remove-atribute! (g <graph>) v (k <keyword>))
  (del-v:atribute! g v k))

(define-method (remove-atribute! (g <undirected-graph>) (edge <list>) (k <keyword>))
  (del-e:atribute! g edge k))

(define-method (remove-atribute! (g <directed-graph>) (arrow <list>) (k <keyword>))
  (del-e:atribute! g arrow k))

(define-method (remove-vertices-atribute! (g <graph>) (k <keyword>))
  (for-each (λ (v) (remove-atribute! g v k)) (vertices g)))

(define-method (remove-edges-atribute! (g <undirected-graph>) (k <keyword>))
  (for-each (λ (e) (remove-atribute! g e k)) (edges g)))

(define-method (remove-arrows-atribute! (g <directed-graph>) (k <keyword>))
  (for-each (λ (a) (remove-atribute! g a k)) (arrows g)))

;;;
;;; Constructors
;;;
(define-method (populate! (g <undirected-graph>) (p <list>))
  (define (construct-atributes lst)
    (zip (filter-map (λ (l i) (and (even? i) l)) lst (iota (length lst)))
	 (filter-map (λ (l i) (and (odd? i) l)) lst (iota (length lst)))))
  (define (add-vertex-compound-edge! vertex edge)
    (define v (car edge))
    (define as (cdr edge))
    (add-edge! g (list vertex v))
    (for-each (λ (a) (add-atribute! g (list vertex v) (car a) (cadr a)))
	      (construct-atributes as)))
  (define (add-vertex-edges! vertex edges)
    (for-each (λ (e)
		 (if (list? e)
		     (add-vertex-compound-edge! vertex e)
		     (add-edge! g (list vertex e))))
	      edges))
  (define (add-compound-vertex! vertex)
    (define v (car vertex))
    (define as (cdr vertex))
    (add-vertex! g v)
    (for-each (λ (a) (add-atribute! g v (car a) (cadr a)))
	      (construct-atributes as)))
  (define (add-compound-context! ctx)
    (define v (first ctx))
    (define es (if (null? (cdr ctx)) '() (second ctx)))
    (cond ((list? v)
	   (add-compound-vertex! v)
	   (add-vertex-edges! (first v) es))
	  (else
	   (add-vertex! g v)
	   (add-vertex-edges! v es))))
  (define (add-context! ctx)
    (cond ((list? ctx)			; the context is complex
	   (add-compound-context! ctx))
	  (else				; the context is a vertex
	   (add-vertex! g ctx))))
  (for-each add-context! p))

;;;
;;; I/O Procedures
;;;
(define-method (write (g <undirected-graph>) port)
  (format port "\n<undirected-graph>\n")
  (format port "  <vertices>\n")
  (unless (null? (vertices g))
    (format port "    ~a\n" (vertices g)))
  (format port "  <edges>\n")
  (for-each (λ (e)
	       (format port "    ~a\n" e))
	    (edges g)))

(define-method (write (g <directed-graph>) port)
  (format port "\n<directed-graph>\n")
  (format port "  <vertices>\n")
  (unless (null? (vertices g))
    (format port "    ~a\n" (vertices g)))
  (format port "  <arrows>\n")
  (for-each (λ (a)
	       (format port "    ~a\n" a))
	    (arrows g)))

(define-method (display (g <undirected-graph>) port)
  (format port "\n<undirected-graph>\n")
  (format port "  <vertices>\n")
  (unless (null? (vertices g))
    (format port "    ~a\n" (vertices g)))
  (format port "  <edges>\n")
  (for-each (λ (e)
	       (format port "    ~a\n" e))
	    (edges g))
  (format port "  <vertices-details>\n")
  (for-each (λ (v)
	       (format port "    ~a : ~a\n" v (atributes g v)))
	    (remove (λ (v) (null? (atributes g v))) (vertices g)))
  (format port "  <edges-details>\n")
  (for-each (λ (e)
	       (format port "    ~a : ~a\n" e (atributes g e)))
	    (remove (λ (e) (null? (atributes g e))) (edges g)))
  (newline))

(define-method (display (g <directed-graph>) port)
  (format port "\n<directed-graph>\n")
  (format port "  <vertices>\n")
  (unless (null? (vertices g))
    (format port "    ~a\n" (vertices g)))
  (format port "  <arrows>\n")
  (for-each (λ (a)
	       (format port "    ~a\n" a))
	    (arrows g))
  (format port "  <vertices-details>\n")
  (for-each (λ (v)
	       (format port "    ~a : ~a\n" v (atributes g v)))
	    (remove (λ (v) (null? (atributes g v))) (vertices g)))
  (format port "  <arrows-details>\n")
  (for-each (λ (a)
	       (format port "    ~a : ~a\n" a (atributes g a)))
	    (remove (λ (a) (null? (atributes g a))) (arrows g)))
  (newline))

;;;
;;; Specialized constructors
;;;

;;; Graph   = (Context ...)
;;; Context = Vertex
;;;         | (Vertex ...)
(define-method (make-graph (graph <list>))
  (define (insert-context! g c)
    (cond ((list? c)
	   (let ((v (car c)) (destinations (cdr c)))
	     (add-vertex! g v)
	     (for-each (λ (u)
			  (add-edge! g (list v u)))
		       destinations)))
	  (else
	   (add-vertex! g c))))
  (define (insert-into-graph! g contexts)
    (for-each (λ (ctx)
		 (insert-context! g ctx))
	      contexts))
  (define g (make <undirected-graph>))
  (insert-into-graph! g graph)
  g)

;;; Tree = Vertex
;;;      | (Vertex Tree ...)
(define-method (make-tree tree)
  (define (insert-into-tree! g t p)
    (cond ((list? t)
	   (let ((v (car t)) (children (cdr t)))
	     (add-vertex! g v)
	     (unless (null? p)
	       (add-edge! g (list p v)))
	     (for-each (λ (subtree)
			  (insert-into-tree! g subtree v))
		       children)))
	  (else
	   (add-vertex! g t)
	   (unless (null? p)
	     (add-edge! g (list p t))))))
  (define g (make <undirected-graph>))
  (insert-into-tree! g tree '())
  g)


;;; Bipartite = (V-Set ...)
;;; V-Set     = (Vertex ...)
(define-method (make-K-n-n (graph <list>))
  (define (flatten lst)
    (apply append lst))
  (define (remove-from x lst)
    (remove (λ (y) (equal? x y)) lst))
  (define (insert-set-into-graph! g vset lst)
    (for-each (λ (u)
		 (for-each (λ (v)
			      (add-edge! g (list u v)))
			   lst))
	      vset))
  (define g (make <undirected-graph>))
  (for-each (λ (vset)
	       (insert-set-into-graph!
		g vset (flatten (remove-from vset graph))))
	    graph)
  g)

;;; Complete = (Vertex ...)
(define-method (make-K-n (vertices <list>))
  (define (remove-from x lst)
    (remove (λ (y) (equal? x y)) lst))
  (define g (make <undirected-graph>))
  (for-each (λ (u)
	       (for-each (λ (v)
			    (add-edge! g (list u v)))
			 (remove-from u vertices)))
	    vertices)
  g)

;;; Cicle = (Vertex ...)
(define-method (make-cicle (path <list>))
  (define (rotate-left lst)
    (take (cdr (apply circular-list lst)) (length lst)))
  (define g (make <undirected-graph>))
  (for-each (λ (e)
	       (add-edge! g e))
	    (zip path (rotate-left path)))
  g)
