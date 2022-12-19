#|

tipul (1):
(nod nr-subarbori lista-subarbore-1 lista-subarbore-2 ....)

tipul (2)
(nod (lista-subarbore-1) (lista-subarbore-2))

ex: 
(A 2 B 0 C 2 D 0 E 0)
	A
      /   \
     B     C
	  / \
         D   E


7. se da un arbore de tipul (1). Sa se precizeze nivelul pe care apare un nod x in arbore. Nivelul radacinii se considera a fi 0.
|#

#|

parcurgereSubarbori(l1l2...ln, nv, nm, laux) = 	laux, n = 0
						laux (+) (l1...ln), nv = nm + 1
						parcurgereSubarbori(l3...ln, nv + 1, nm + l2, laux (+) l1)

parcugereSubarbori(l nv nm laux)
l - lista care trebuie impartita in 2 liste reprezentand cei 2 subarbori
nv - numarul curent de varfuri parcurse
nm - numarul curent de muchii parcurse
laux - lista care contine segmentarea listei initiale in 2 liste, reprezentand cei 2 subarbori
|#

(defun parcurgereSubarbori(l nv nm laux)
	(cond
		((null l) (list laux))
		((= nv (+ nm 1)) (cons laux (list l)))
		(t (parcurgereSubarbori (cddr l) (+ nv 1) (+ nm (cadr l)) (append laux (list (car l) (cadr l)))))
	)
)

#|
subarboreStDr(l1...ln) = parcurgereSubarbori(l3 ... ln, 0, 0, ())

subarboreStDr(l)
l - lista ce reprezinta arborele de tip (1) care va fi transformat in tip (radacina (arbore st) (arbore dr))
|#

(defun subarboreStDr(l)
	(cons (car l) (parcurgereSubarbori (cddr l) 0 0 nil))
)

#|
gasesteNivel(l1...ln, e, nr) =	false, daca n = 0
				nr, daca e1 = e (n >=1)
				gasesteNivel(e2, e, nr + 1), daca gasesteNivel(e2, e, nr + 1) != false (n >= 2)
				gasesteNivel(e3, e, nr + 1), daca gasesteNivel(e3, e, nr + 1) != false (n<=3)
				false, altfel
el = subarboreStDr(l) = (e1..en) 
|#
(defun gasesteNivel(l e nr)
    (
	(lambda (el)
		(cond
			((null l) nil)
			((equal (car el) e) nr)
			((not (null (gasesteNivel (cadr el) e (+ nr 1)))) (gasesteNivel (cadr el) e (+ nr 1)))
			((not (null (gasesteNivel (caddr el) e (+ nr 1)))) (gasesteNivel (caddr el) e (+ nr 1)))
			(t nil)
		)
	)
	(subarboreStDr l)
   )
)


#|
main(l1...ln) = gasesteNivel(l, e, 0)

main(l e)
l - lista ce reprezinta arbore de tip (1)
e - elementul care trebuie cautat
|#
(defun main(l e)
	(gasesteNivel l e 0)
)


#|
(main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) 'a)
(main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) 'b)
(main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) 'd)
(main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) 'c)
(main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) 'f)
(main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) 'h)
(main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) 'e)
(main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) 'i)
(main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) 'g)
(main '(a 2 b 2 c 1 i 0 f 1 g 0 d 2 e 0 h 0) 'j)
(main '() 'a)
(main '(a 2 b 0 c 0) 'b)
(main '(a 2 b 1 c 0 d 0) 'd)
(main '(a 2 b 1 c 0 d 0) 'c)


|#









