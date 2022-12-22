#|
9. definiti o functie care sa substituie un element E prin elemenetele unei liste L1 la toate nivelurile unei liste date L


substituie(x, e, l1) =	l1, daca x = e
			U substituie(xi e l1), i = 1...n, daca x = lista de forma x1x2...xn
			(x), altfel

main(x, e, l1) = p1, unde (p1) = substituie(x, e, l1)

|#

(defun substituie(x e l1)
	(cond
		((equal x e) l1)
		((listp x) 
			(list (apply #'append
				(mapcar 	
					#'(lambda(l)
					(substituie l e l1)
				     	)
				     	x
			   	)
			      )
			)
			
		)
		(t (list x))
	)
)	

(defun main(x e l1)
	(car (substituie x e l1))
)
