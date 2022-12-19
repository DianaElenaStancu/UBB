#| 
5 a) definiti o functie care interclaseaza cu pastrarea dublurilor doua liste liniare sortate

interclasare(l1l2...ln, p1p2...pm) =    l1l2...ln, m = 0
                                        p1p2...pm, n = 0
					l1 (+) interclasare(l2...ln, p1p2...pm), l1 < p1
					p1 (+) interclasare(l1l2...ln, p2...pm), p1 >= l1
l, p - liste liniare de numere intregi
|#
(defun interclasare(l p)
  (cond
    ((null p) l)
    ((null l) p)
    ((< (car l) (car p)) (cons (car l) (interclasare (cdr l) p))) 
    (t (cons (car p) (interclasare l (cdr p))))
  )
)

#|
5 b) definiti o functie care substituie un element E prin elementele unei liste L1 la toate nivelurile unei liste date L

substituie(p1p2...pn, e, l1) = 	nil, n = 0
				l1 (+) substituie(p2...pn, e, l1), p1 = e, n > 0
				substituie(p1, e, l1) (+) substituie(p2...pn, e, k), p1 - lista, p1 != e, n > 0
				p1 (+) substituie(p2...pn, e, l1), p1 - atom, p1 != e, n > 0 
p - lista in care se cauta elementul e pentru a fi substituit
e - elementul care trebuie cautat
l - lista care trebuie inlocuita cu elementul e
|#
(defun substituie(l e l1)
	(cond
		((null l) nil)
		((equal (car l) e) (append l1 (substituie (cdr l) e l1)))
		((listp (car l)) (cons (substituie (car l) e l1) (substituie (cdr l) e l1)))
		((atom (car l)) (cons (car l) (substituie (cdr l) e l1)))
	)
)


#|
5 c) definiti o functie care determina suma a doua numere in reprezentare de lista si calculeaza numarul zecimal corespunzator sumei

sum(l1l2...ln, k1k2...km, cf) = 	(l1 + k1 + cf)%10 (+) sum(l2...ln, k2...km, (l1 + k1 + cf)/10), n > 0, m > 0
					(l1 + cf)%10 (+) sum(l2...ln, k, (l1 + cf)/10), n > 0, m = 0
					(k1 + cf)%10 (+) sum(l, k2...km, (k1 + cf)/10), n = 0, m > 0
					(cf), n = 0, m = 0, cf = 1
					(), n = 0, m = 0, cf = 0
l, k - lista in care sunt numerele
cf - carry flag


invers(l1l2...ln, c) =			c, n = 0
					invers(l2...ln, l1 (+) c), altfel

l - lista care trebuie inversata
c - lista colectoare in care va fi lista inversata

sumP(l, k) = 		invers(sum(invers(l, ()), invers(k, ()), 0), ())
l, k - listele in care sunt reprezentate cele doua numere

transform(l1l2...ln, c) = 	c, n = 0
				transform(l2...ln, c*10 + l1), altfel
			 
|#
(defun transform(l c)
	(cond
		((null l) c)
		(t (transform (cdr l) (+ (* c 10) (car l))))
	)
)



(defun invers(l c)
	(cond
		((null l) c)
		(t (invers (cdr l) (cons (car l) c)))
	)
)

(defun sum(l k cf)
	(cond
		((and (not (null l)) (not (null k))) (cons (mod (+ (car l) (car k) cf) 10) (sum(cdr l) (cdr k) (floor (+ (car l) (car k) cf) 10))))
		((not (null l)) (cons (mod (+ (car l) cf) 10) (sum (cdr l) () (floor (+ (car l) cf) 10))))
		((not (null k)) (cons (mod (+ (car k) cf) 10) (sum () (cdr k) (floor (+ (car k) cf) 10))))
		((= cf 0) nil)
		((= cf 1) (list cf))
	)
)			

(defun sumP(l k)
	(transform (invers (sum (invers l ()) (invers k ()) 0) ()) 0)
)

#|
5 d) definiti o functie care intoarce cel mai mare divizor comun al numerelor dintr-o lista liniara

cmmdc(a, b) = 	a, b = 0
		cmmdc(b, a%b), atlfel
a, b - numere

cmmdcL(l1l2..ln) = 	nil, n = 0
			cmmdc(l1, cmmdcL(l2...ln)), l1 - atom numeric
			cmmdcL(l2...ln), altfel
l - lista liniara de numere
|#
(defun cmmdc(a b)
	(cond
		((= b 0) a)
		(t (cmmdc b (mod a b)))
	)
)

(defun cmmdcL(l)
	(cond
		((null l) 0)
		((numberp (car l)) (cmmdc (car l) (cmmdcL (cdr l))))
		(t (cmmdcL (cdr l)))
	)
)
