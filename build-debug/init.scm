(eval-when (expand load eval)
	   (define working-dir (dirname (current-filename)))
	   (unless (member working-dir %load-path)
	     (add-to-load-path working-dir))
	   (use-modules (oop goops))
	   (use-modules (grafo graph))
	   (use-modules (grafo utils))
	   (use-modules (srfi srfi-1))
	   (use-modules (ice-9 q))
	   (use-modules (srfi srfi-43))

	   ;(use-modules (oop goops))
	   
	   ;(use-modules (grafo graph))

	   ;(use-modules (grafo utils))

	   ;(use-modules (grafo bipartiteness))

	   ;(use-modules (grafo spanning-trees))

	   ;(use-modules (grafo heap))

	   ;(use-modules (grafo dijkstra))

	   ;(use-modules (grafo floyd-warshall))

	   ;(use-modules (grafo ford-fulkerson))

	   ;(use-modules (grafo minimum-cost))

	   ;(use-modules (srfi srfi-1))
	   
	   (use-modules (system repl server))
	   (spawn-server))
