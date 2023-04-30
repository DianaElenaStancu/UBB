use library_database_sem4
go

/*
create table Logs
(
  id int identity,
  operationType varchar(20),
  tableName varchar(20),
  executionTime datetime,
  constraint pk_Logs primary key(id)
)
*/

select * from Books;
select * from Records;
select * from Librarians;
go
CREATE OR ALTER FUNCTION validate_name (@name VARCHAR(51))
RETURNS BIT
AS
BEGIN
  DECLARE @isValid BIT = 0
  
  IF @name IS NOT NULL AND @name <> '' -- Name is not null or empty
    AND LEN(@name) <= 50 -- Name has a maximum of 50 characters
    SET @isValid = 1

  RETURN @isValid
END

go
SELECT  dbo.validate_name('John Doe') -- Returns 1
SELECT  dbo.validate_name('aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa') -- Returns 0
SELECT  dbo.validate_name(NULL) -- Returns 0
go
CREATE OR ALTER FUNCTION validate_email (@email VARCHAR(51))
RETURNS BIT
AS
BEGIN
  DECLARE @isValid BIT = 1
  IF @email IS NULL OR @email = '' -- Email is not null or empty
    OR @email NOT LIKE '%_@__%.__%'
    OR LEN(@email) > 50 -- Email has a maximum of 50 characters
    SET @isValid = 0
  RETURN @isValid
END
go

-- Test valid email addresses
SELECT dbo.validate_email('test@example.com') -- Returns 1
SELECT dbo.validate_email('test.email+label@example.co.uk') -- Returns 1
SELECT dbo.validate_email('test@sub.domain.example.net') -- Returns 1

-- Test invalid email addresses
SELECT dbo.validate_email(NULL) -- Returns 0
SELECT dbo.validate_email('') -- Returns 0
SELECT dbo.validate_email('test') -- Returns 0
SELECT dbo.validate_email('test@') -- Returns 0
SELECT dbo.validate_email('@example.com') -- Returns 0
go
CREATE OR ALTER FUNCTION validate_mentions(@mentions VARCHAR(201))
RETURNS BIT
AS
BEGIN
  DECLARE @isValid BIT = 0
  
  IF @mentions IS NOT NULL AND @mentions <> '' -- Name is not null or empty
    AND LEN(@mentions) <= 200 -- Name has a maximum of 50 characters
    SET @isValid = 1

  RETURN @isValid
END
go
CREATE OR ALTER FUNCTION validate_conditions(@conditions VARCHAR(21))
RETURNS BIT
AS
BEGIN
  DECLARE @isValid BIT = 0
  
  IF @conditions IS NOT NULL AND @conditions <> '' -- Name is not null or empty
    AND LEN(@conditions) <= 20 -- Name has a maximum of 50 characters
    SET @isValid = 1

  RETURN @isValid
END
go
CREATE FUNCTION validate_ISBN
(
	@ISBN varchar(20)
)
RETURNS BIT
AS
BEGIN

	if  @ISBN like '%[^a-zA-Z0-9]%' or (len(@ISBN) != 10 and len(@ISBN) != 13)
		return 0

	return 1
END
go



go
create or alter function validate_parameters_librarian(
@first_name varchar(51),
@last_name varchar(51),
@email varchar(51),
@mentions_librarian varchar(51)
) 
returns varchar(200)
as
begin
	declare @error_message varchar(200)
	set @error_message = ''

	if (dbo.validate_name(@first_name) = 0)
		set @error_message = @error_message + 'prenumele nu trebuie sa fie null, gol sau sa aiba mai mult de 50 de caractere.'
	if (dbo.validate_name(@last_name) = 0)
		set @error_message = @error_message + 'numele nu trebuie sa fie null, gol sau sa aiba mai mult de 50 de caractere.'

	if (dbo.validate_email(@email) = 0)
		set @error_message = @error_message + 'email invalid.'

	if (dbo.validate_mentions(@mentions_librarian) = 0)
		set @error_message = @error_message + 'mentions null, gol sau prea lung (>200).'
	return @error_message
end
go

select dbo.validate_parameters_librarian(null, '', 'asd', '')
go

create or alter function validate_parameters_record(
@subscriber_id int,
@book_id int, 
@librarian_id int, 
@loan_date date, 
@due_date date, 
@restitution_date date, 
@mentions_record varchar(201)
)
returns varchar(200)
as
begin
	declare @error_message varchar(200)
	set @error_message = ''
	if (not (exists(select id from dbo.Subscribers where id = @subscriber_id)))
		set @error_message = @error_message + 'subscriberul cu id-ul dat nu exista.'
	if (not (exists(select id from dbo.Books where id = @book_id)))
		set @error_message = @error_message +'cartea cu id-ul dat nu exista.'
	if (not (exists(select id from dbo.Librarians where id = @librarian_id)))
		set @error_message = @error_message +'bibliotecarul cu id-ul dat nu exista.'
	if (@loan_date is null or @due_date is null or @restitution_date is null)
		set @error_message = @error_message + 'cel putin una dintre date (tip date) sunt nulle.'
	if (@loan_date > @due_date)
		set @error_message = @error_message +'datele de luare si predare carte sunt invalide.'
	if (@loan_date > @restitution_date)
		set @error_message = @error_message +'data de restituire a cartii este inainte de cea de inchiriere'
	if (dbo.validate_mentions(@mentions_record) = 0)
		set @error_message = @error_message + 'mentions null, gol sau prea lung (>200).'
	return @error_message
end
go

select dbo.validate_parameters_record(null,null,null,'dasdsada','dsadasdsa','dsadsadas',null)


select dbo.validate_parameters_record(10,11,23,null,null,null,null)

go
create or alter function validate_parameters_book(
@ISBN varchar(20),
@title varchar(100),
@author int, 
@language_id int,
@subdepartment_id int, 
@publisher int, 
@active bit, 
@conditions varchar(20),
@publication_date date, 
@mentions_book varchar(200)
)
returns varchar(200)
as
begin
	declare @error_message varchar(200)
	set @error_message = ''
	if (not (exists(select id from dbo.Authors where id = @author)))
		set @error_message = @error_message + 'autorul cu id-ul dat nu exista.'
	if (not (exists(select id from dbo.Languages where id = @language_id)))
		set @error_message = @error_message + 'limba cu id-ul dat nu exista.'
	if (not (exists(select id from BookSubdepartments where id = @subdepartment_id)))
		set @error_message = @error_message +'subdepartamentul cu id-ul dat nu exista.'
	if (dbo.validate_ISBN(@ISBN) = 0)
		set @error_message = @error_message +'ISBN invalid.'
	if (dbo.validate_name(@title) = 0)
		set @error_message = @error_message +'titlul nu trebuie sa fie null, gol sau sa aiba mai mult de 50 de caractere.'
	if (dbo.validate_conditions(@conditions) = 0)
		set @error_message = @error_message + 'conditions null, gol sau prea lung (>20).'
	if (dbo.validate_mentions(@mentions_book) = 0)
		set @error_message = @error_message + 'mentions null, gol sau prea lung (>200).'
	return @error_message
end
go

select dbo.validate_parameters_book(10,11,23,null, null,null,null,null, null, null)


go
create or alter procedure insert_librarian_book_record_v1(
@first_name varchar(50),
@last_name varchar(50),
@email varchar(50),
@mentions_librarian varchar(50),
@subscriber_id int,
@loan_date date, 
@due_date date, 
@restitution_date date, 
@mentions_record varchar(200),
@ISBN varchar(20),
@title varchar(100),
@author int, 
@language_id int,
@subdepartment_id int, 
@publisher int, 
@active bit, 
@conditions varchar(20),
@publication_date date, 
@mentions_book varchar(200)
)
as
begin
	begin tran
	begin try
		declare @error_message varchar(200)
		set @error_message = dbo.validate_parameters_librarian(@first_name,@last_name,@email,@mentions_librarian)
		if (@error_message != '')
		begin
			print @error_message
			raiserror(@error_message, 14, 1)
		end
		insert into Librarians(first_name, last_name, email, mentions) values (@first_name, @last_name, @email, @mentions_librarian)
		insert into Logs(operationType, tableName, executionTime) values ('insert', 'librarians', CURRENT_TIMESTAMP)
		set @error_message = dbo.validate_parameters_book(@ISBN,@title,@author, @language_id, @subdepartment_id, @publisher, @active, @conditions,@publication_date, @mentions_book)
		if (@error_message != '')
		begin
			print @error_message
			raiserror(@error_message, 14, 1)
		end
		insert into Books(ISBN,title,author, language_id, subdepartment_id, publisher, active, conditions,publication_date, mentions) values (@ISBN,@title,@author,@language_id, @subdepartment_id, @publisher, @active, @conditions,@publication_date, @mentions_book)
		insert into Logs(operationType, tableName, executionTime) values ('insert', 'books', CURRENT_TIMESTAMP)
		declare @librarian_id int, @book_id int
		set @librarian_id = (select max(id) from Librarians)
		insert into Logs(operationType, tableName, executionTime) values ('select', 'librarian id', CURRENT_TIMESTAMP)
		set @book_id = (select max(id) from Books)
		insert into Logs(operationType, tableName, executionTime) values ('select', 'book id', CURRENT_TIMESTAMP)

		set @error_message = dbo.validate_parameters_record(@subscriber_id, @book_id, @librarian_id,@loan_date, @due_date, @restitution_date, @mentions_record)
		if (@error_message != '')
		begin
			print @error_message
			raiserror(@error_message, 14, 1)
		end

		insert into Records(subscriber_id, book_id, librarian_id,loan_date, due_date, restitution_date, mentions) values (@subscriber_id, @book_id, @librarian_id,@loan_date, @due_date, @restitution_date, @mentions_record);
		insert into Logs(operationType, tableName, executionTime) values ('insert', 'records', CURRENT_TIMESTAMP)

		commit tran

		select 'Transaction commited'
	end try
	begin catch
		rollback tran
		select 'Transaction rollbacked'
	end catch
end
go

-- tests
select * from Librarians
select * from Records
select * from Books
select * from Logs

--commit
execute dbo.insert_librarian_book_record_v1
'iosif',
'marian',
'iosif@biblio.com',
'specializat pe romane',
'1',
'2021-10-10', 
'2021-11-11', 
'2021-12-12', 
'intarziere de o luna',
'ABSOJ76S98',
'Sonet 10',
2, 
1,
1, 
1, 
1, 
'foarte buna',
'2000-10-10', 
'foarte ceruta de catre studenti'

select * from Librarians
select * from Records
select * from Books
select * from Logs

--rollback
execute dbo.insert_librarian_book_record_v1
'cristi',
'popescu',
'cristi@biblio.com',
'specializat pe schite',
'1',
'2021-10-10', 
'2019-11-11', 
'', 
'intarziere de o luna',
'ABSS98',
'Sonet 10',
0, 
1,
199, 
1, 
1, 
'foarte buna',
'2000-10-10', 
'foarte ceruta de catre studenti'

select * from Librarians
select * from Records
select * from Books
select * from Logs

go
create or alter procedure insert_librarian_book_record_v2(
@first_name varchar(50),
@last_name varchar(50),
@email varchar(50),
@mentions_librarian varchar(50),
@subscriber_id int,
@loan_date date, 
@due_date date, 
@restitution_date date, 
@mentions_record varchar(200),
@ISBN varchar(20),
@title varchar(100),
@author int, 
@language_id int,
@subdepartment_id int, 
@publisher int, 
@active bit, 
@conditions varchar(20),
@publication_date date, 
@mentions_book varchar(200)
)
as
begin
	declare @error bit
	set @error = 1

	begin tran
	begin try
		declare @error_message varchar(200)
		set @error_message = dbo.validate_parameters_librarian(@first_name,@last_name,@email,@mentions_librarian)
		if (@error_message != '')
		begin
			print @error_message
			raiserror(@error_message, 14, 1)
		end
		insert into Librarians(first_name, last_name, email, mentions) values (@first_name, @last_name, @email, @mentions_librarian)
		insert into Logs(operationType, tableName, executionTime) values ('insert', 'librarians', CURRENT_TIMESTAMP)
		
		commit tran
		select 'Transaction comitted Librarians'
	end try
	begin catch
		rollback tran
		select 'Transaction rollbacked for Librarians'
		insert into Logs(operationType, tableName, executionTime) values ('rollback', 'librarians', CURRENT_TIMESTAMP)
		set @error = 0
	end catch
	
	begin tran
	begin try
		set @error_message = dbo.validate_parameters_book(@ISBN,@title,@author, @language_id, @subdepartment_id, @publisher, @active, @conditions,@publication_date, @mentions_book)
		if (@error_message != '')
		begin
			print @error_message
			raiserror(@error_message, 14, 1)
		end
		insert into Books(ISBN,title,author, language_id, subdepartment_id, publisher, active, conditions,publication_date, mentions) values (@ISBN,@title,@author,@language_id, @subdepartment_id, @publisher, @active, @conditions,@publication_date, @mentions_book)
		insert into Logs(operationType, tableName, executionTime) values ('insert', 'books', CURRENT_TIMESTAMP)

		commit tran
		select 'Transaction comitted Books'
	end try
	begin catch
		rollback tran
		select 'Transaction rollbacked for Books'
		insert into Logs(operationType, tableName, executionTime) values ('rollback', 'books', CURRENT_TIMESTAMP)
		set @error = 0
	end catch

	if (@error = 0)
		return;

	begin tran
	begin try
		declare @librarian_id int, @book_id int
		set @librarian_id = (select max(id) from Librarians)
		insert into Logs(operationType, tableName, executionTime) values ('select', 'librarian id', CURRENT_TIMESTAMP)
		set @book_id = (select max(id) from Books)
		insert into Logs(operationType, tableName, executionTime) values ('select', 'book id', CURRENT_TIMESTAMP)

		set @error_message = dbo.validate_parameters_record(@subscriber_id, @book_id, @librarian_id,@loan_date, @due_date, @restitution_date, @mentions_record)
		if (@error_message != '')
		begin
			print @error_message
			raiserror(@error_message, 14, 1)
		end

		insert into Records(subscriber_id, book_id, librarian_id,loan_date, due_date, restitution_date, mentions) values (@subscriber_id, @book_id, @librarian_id,@loan_date, @due_date, @restitution_date, @mentions_record);
		insert into Logs(operationType, tableName, executionTime) values ('insert', 'records', CURRENT_TIMESTAMP)

		commit tran

		select 'Transaction commited Records'
	end try
	begin catch
		rollback tran
		insert into Logs(operationType, tableName, executionTime) values ('rollback', 'records', CURRENT_TIMESTAMP)
		select 'Transaction rollbacked Records'
	end catch
end
go


-- tests
select * from Librarians
select * from Records
select * from Books
select * from Logs

--commit
execute dbo.insert_librarian_book_record_v2
'cristian',
'kim',
'kim@biblio.com',
'arta contemporana',
'1',
'2021-10-10', 
'2021-11-11', 
'2021-12-12', 
'intarziere de o luna',
'ABSOJ76S18',
'Arta contemporana',
2, 
1,
1, 
1, 
1, 
'foarte buna',
'2000-10-10', 
'foarte ceruta de catre studenti'

select * from Librarians
select * from Records
select * from Books
select * from Logs

--rollback
execute dbo.insert_librarian_book_record_v2
'marius',
'budiu',
'budiuu@biblio.com',
'sanatate',
'1',
'2021-10-10', 
'2019-11-11', 
'', 
'intarziere de o luna',
'ABSS79GHPA',
'Secrete',
2, 
1,
1, 
1, 
1, 
'foarte buna',
'2000-10-10', 
'foarte ceruta de catre studenti'

select * from Librarians
select * from Records
select * from Books
select * from Logs