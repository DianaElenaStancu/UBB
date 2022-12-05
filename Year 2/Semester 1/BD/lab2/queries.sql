USE library_database
/*
 5 - where                  1, 2, 3, 7, 8 ---
 3 - group by               4, 5, 6 ---
 2 distinct                 2, 3 ----
 2 having                   4, 5 ---
 7 joining 2+ tables        1, 2, 3, 4, 5, 7, 8 --
 2 2+ m-m tables            2, 3 ---
 */

/*
1. selecteaza cartile autorilor francezi si subdepartamentul din care fac parte
*/
SELECT B.title, BS.name, A.first_name
FROM Authors A
INNER JOIN Books B on A.id = B.author
INNER JOIN BookSubdepartments BS on B.subdepartment_id = BS.id
WHERE nationality = 'French';

/*
2. selecteaza toti bibliotecarii distincti care au dat la imprumut carti de la autorul cu id = 7 (christian dior) in perioada 2022-2023
*/
SELECT DISTINCT L.first_name, L.last_name
FROM Librarians L
INNER JOIN Records R2 ON L.id = R2.librarian_id
INNER JOIN Books B ON B.id = R2.book_id
WHERE B.author = 7 AND R2.loan_date BETWEEN datetimefromparts(2022,2,1,0,0,0,0) AND datetimefromparts(2023,3,1,0,0,0,0);


/*
3. selecteaza toti subscriberii distincti care au imprumutat carti in limba engleza si fac parte din grupul cu id = 2 (grupul de copii)
*/
SELECT DISTINCT S.last_name, S.first_name
FROM Subscribers S
INNER JOIN Records R2 ON S.id = R2.subscriber_id
INNER JOIN Books B ON B.id = R2.book_id
INNER JOIN Languages L on B.language_id = L.id
WHERE S.group_id = 2 AND L.id = 3;

/*
4. selecteaza limbile straine si numarul cartilor imprumutate din acea limba, daca exista cel putin 2 carti imprumutate in acea limba
*/
SELECT L.name, COUNT(L.id) as 'Numarul de carti'
FROM Books B
INNER JOIN Languages L on L.id = B.language_id
INNER JOIN Records R2 on B.id = R2.book_id
GROUP BY L.name
HAVING COUNT(R2.id) >= 2
ORDER BY COUNT(L.id) DESC;

/*
5. selecteaza toate editurile care au avut cel putin 3 carti imprumutate
*/
SELECT P.name, COUNT(P.id) as 'Numarul publicatii'
FROM Publishers P
INNER JOIN Books B on P.id = B.publisher
INNER JOIN Records R2 on B.id = R2.book_id
GROUP BY P.name
HAVING COUNT(P.id) >= 3
ORDER BY COUNT(P.id);

/*
  6. departamentele si numarul de subdepartamente
 */
 SELECT BD.name, COUNT(BD.id)
 FROM BookDepartments BD
 INNER JOIN BookSubdepartments BS on BD.id = BS.department_id
 GROUP BY BD.name;

/*
 7. Autorii, cartile si subdepartamentele care sunt din departamentul de Biographies
 */
 SELECT A.first_name, B.title, BS.name
 FROM Authors A
 INNER JOIN Books B on A.id = B.author
 INNER JOIN BookSubdepartments BS on BS.id = B.subdepartment_id
 INNER JOIN BookDepartments BD on BD.id = BS.department_id
WHERE BD.name = 'Biographies';

/*
 8. Numele studentilor, data cand trebuie restituita si cartea pe care trebuie sa o aduca
 */
SELECT S.first_name, S.last_name, R2.due_date, B.title
FROM Subscribers S
INNER JOIN Records R2 on S.id = R2.subscriber_id
INNER JOIN Books B on B.id = R2.book_id
INNER JOIN SubscriberGroups SG on SG.id = S.group_id
WHERE S.group_id = 1;

/*
 9. Administratorii si imprumuturile de care au fost responsabili pana in luna martie
 */
 SELECT L.first_name, L.last_name, R2.due_date
FROM Librarians L
INNER JOIN Records R2 on L.id = R2.librarian_id
WHERE R2.loan_date <= datetimefromparts(2022,3,1,0,0,0,0) AND R2.due_date <= datetimefromparts(2022,3,1,0,0,0,0);

/*
 10. Cartile scrise de Lois Burdett, ISBN si cand au fost acestea publicate
 */
 SELECT B.title,  B.ISBN, B.publication_date
FROM Authors A
INNER JOIN Books B on A.id = B.author
WHERE A.id = 10;
