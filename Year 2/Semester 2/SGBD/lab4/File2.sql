use library_database_sem4
go

-- dirty reads
-- t1: update + delay + rollback
-- t2: select + delay + select
-- real order: update - select - rollback - select
-- sol: committed

set transaction isolation level read uncommitted
-- set transaction isolation level read committed
begin tran
select * from Books
waitfor delay '00:00:15'
select * from Books
commit tran


-- nonrepeatable reads
-- t1: delay + update + commit
-- t2: select + delay + select
-- real order: select - update - select
-- sol: repeatable read

select * from Books

-- set transaction isolation level repeatable read
set transaction isolation level read committed
begin tran
select * from Books
waitfor delay '00:00:15'
select * from Books
commit tran


-- phantom reads
-- t1: delay + insert + commit
-- t2: select + delay + select
-- real order: select - insert - select
-- sol: serializable

-- set transaction isolation level repeatable read 
set transaction isolation level serializable
begin tran
select * from Books
waitfor delay '00:00:15'
select * from Books
commit tran

select * from Books

-- deadlock
-- t1: update BookDepartments + delay + update BookSubdepartments
-- t2: update BookSubdepartments + delay + update BookDepartments

set deadlock_priority high
begin tran
update BookSubdepartments set name = 'Geografia Romaniei' where id = 2
waitfor delay '00:00:10'
update BookDepartments set name = 'Geografie' where id = 2
commit tran

begin tran
update BookSubdepartments set name = 'Geografia Romaniei' where id = 2
update BookDepartments set name = 'Geografie' where id = 2
commit tran