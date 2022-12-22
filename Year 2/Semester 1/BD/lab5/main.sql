use [library_database]
--records
declare @loan_date date
    set @loan_date = datetimefromparts(2022, 2, 3, 0, 0,0,0)
declare @due_date date
    set @due_date = datetimefromparts(2022, 5, 3, 0, 0,0,0)
declare @restitution_date date
    set @restitution_date = datetimefromparts(2022, 7, 3, 0, 0,0,0)
--exec crudRecords 'insert', 1, 1029, 1, 2,  @loan_date,@due_date, @restitution_date, 'no mentions'
--exec crudRecords 'insert', 2, 1031, 20, 1,  @loan_date,@due_date, @restitution_date, 'no mentions'
--exec crudRecords 'select', 1003, null, null, null,  null,null, null, null
--exec crudRecords 'delete', 1003, null, null, null,  null,null, null, null
exec crudRecords 'update', 1002, 1030, 1, 2,  @loan_date,@due_date, @restitution_date, 'no mentions'

--subscribers
declare @registration_date date
    set @registration_date = datetimefromparts(2022, 2, 2, 0, 0,0,0)
--exec crudSubscribers 'insert', 1060, 'Bogdan', 'Presura', 'str scaune 2', '0771683998', 'ana@gmail.com', @registration_date, 1, 'nicio mentiune'
exec crudSubscribers 'update', 1060, 'Bolintineanu', 'Presurianu', 'str scaune 2', '0771683998', 'ana@gmail.com', @registration_date, 1, 'nicio mentiune'
exec crudSubscribers 'delete', 1060, null, null, null, '0771582001', 'ana@gmail.com', null, null, null
exec crudSubscribers 'select', null, 'Ana', null, null, '0771582001', 'ana@gmail.com', null, null, null

--books
declare @publication_date date
    set @publication_date = datetimefromparts(1999, 2, 2, 0, 0,0,0)
--exec crudBookd 'insert' , null, '1234567890', 'Biology book', 3, 2, 2, 10, 1, 'ok', @publication_date, 'noua'
--exec crudBookd 'update' , 1029, '1234567890', 'Biology book 2', 3, 2, 2, 10, 1, 'ok', @publication_date, 'noua'
exec crudBookd 'delete' , 1029, '1234567890', 'Biology book 2', 3, 2, 2, 10, 1, 'ok', @publication_date, 'noua'
--exec crudBookd 'select' , 1029, '1234567890', 'Biology book 2', 3, 2, 2, 10, 1, 'ok', @publication_date, 'noua'




drop index IX_Subscribers_last_name_asc on Subscribers;
drop index IX_Subscribers_last_name_asc_first_name_asc on Subscribers;

create index IX_Subscribers_last_name_asc_first_name_asc on Subscribers(last_name asc, first_name asc)

create index IX_Subscribers_last_name_asc on Subscribers(last_name asc)
--view 1
select last_name, first_name from Subscribers where last_name IN ('Hanganu', 'Cojoc')

drop index IX_Books_title_asc on Books
create index IX_Books_title_asc on Books(title asc)
--view 2
select id, title from Books where title like '%MATHS%'
