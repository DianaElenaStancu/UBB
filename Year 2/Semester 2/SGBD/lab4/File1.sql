use library_database_sem4
go


-- dirty reads
-- t1: update + delay + rollback
-- t2: select + delay + select
-- real order: update - select - rollback - select
-- sol: committed
select * from Books

begin transaction
update books set title = 'Sonet 2' where id = 26 
waitfor delay '00:00:10' 
rollback transaction


-- nonrepeatable reads
-- t1: delay + update + commit
-- t2: select + delay + select
-- real order: select - update - select
-- sol: repeatable read

select * from Books

delete from Books where ISBN = 'HAGSKJJ48'
insert into Books(ISBN, title, author, language_id, subdepartment_id, publisher, active, conditions, publication_date, mentions)
	values ('HAGSKJJ48', 'Capra cu trei iezi', 2, 1, 1, 1, 1, 'bune', '2020-10-10', '');

begin tran
waitfor delay '00:00:10'
update Books set title = 'Frumoasa adormita' where ISBN = 'HAGSKJJ48'
commit tran

-- phantom reads
-- t1: delay + insert + commit
-- t2: select + delay + select
-- real order: select - insert - select
-- sol: serializable

select * from Books
delete from Books where ISBN = '12345678'

begin tran
waitfor delay '00:00:10'

insert into Books(ISBN, title, author, language_id, subdepartment_id, publisher, active, conditions, publication_date, mentions)
	values ('12345678', 'Alba ca zapada', 2, 1, 1, 1, 1, 'bune', '2020-10-10', '');
commit tran

-- deadlock
-- t1: update BookDepartments + delay + update BookSubdepartments
-- t2: update BookSubdepartments + delay + update BookDepartments
-- sol: set priority to define the "victim", execute in the same order
insert into BookDepartments values ('Istorie')
insert into BookSubdepartments values ('Istoria Romaniei', 2)
select * from BookDepartments
select * from BookSubdepartments

begin tran
update BookDepartments set name = 'Geografie' where id = 2
waitfor delay '00:00:10'
update BookSubdepartments set name = 'Geografia Romaniei' where id = 2
commit tran



begin tran
update BookDepartments set name = 'Geografie' where id = 2

update BookSubdepartments set name = 'Geografia Romaniei' where id = 2
commit tran