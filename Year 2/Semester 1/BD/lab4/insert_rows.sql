CREATE PROCEDURE [dbo].[insert_rows]
--ALTER PROCEDURE [dbo].[insert_rows]
-- Add the parameters for the stored procedure here
@nb_of_rows varchar(30),
@table_name varchar(30)
AS
BEGIN
-- SET NOCOUNT ON added to prevent extra result sets from
-- interfering with SELECT statements.
SET NOCOUNT ON;

declare @table varchar(100)
set @table = ('[' + @table_name + ']')


DBCC CHECKIDENT (@table, RESEED, 0); --checks the identity value for the specified table


-- Insert statements for procedure here
if ISNUMERIC(@nb_of_rows) != 1
BEGIN
print('Not a number')
return 1
END

SET @nb_of_rows = cast(@nb_of_rows as INT)

declare @contor int
set @contor = 1

--languages table
declare @language_name varchar(100)


--books table
declare @book_ISBN varchar(20)
declare @book_title varchar(100)
declare @book_author int
declare @book_language_id int
declare @book_subdepartment_id int
declare @book_publisher int
declare @book_active bit
declare @book_conditions varchar(20)
declare @book_publication_date date
declare @book_mentions varchar(200)
set @book_author = 1
set @book_subdepartment_id = 1
set @book_publisher = 1
set @book_active = 1
set @book_publication_date = GETDATE()

---records table
declare @record_subscriber_id int
declare @record_book_id int
declare @record_book_ISBN varchar(20)
declare @record_librarian_id int
declare @record_loan_date date
declare @record_due_date date
declare @record_restitution_date date
declare @record_mentions varchar(200)
set @record_subscriber_id = 1
set @record_librarian_id = 1

while @contor <= @nb_of_rows
begin
declare @contor_string varchar(7)
set @contor_string = convert(varchar(7), @contor)

if @table_name = 'Languages'
begin
set @language_name = 'Language' + @contor_string
insert into Languages (name) values (@language_name)
end

if @table_name = 'Books'
begin
set @book_title = 'title' + @contor_string
set @book_ISBN = '10XYZ' + @contor_string
set @book_conditions = 'conditions' + @contor_string
set @book_mentions = 'mentions' + @contor_string
set @book_language_id = (select max(id) from Languages) - @contor

INSERT INTO Books(ISBN, title, author, language_id, subdepartment_id, publisher, active, conditions, publication_date, mentions)
VALUES (@book_ISBN, @book_title, @book_author, @book_language_id, @book_subdepartment_id, @book_publisher, @book_active, @book_conditions, @book_publication_date, @book_mentions);
end
if @table_name = 'Records'
begin
set @record_book_id = (select max(id) from Books) - @contor
set @record_book_ISBN = '10XYZ' + convert(varchar(7), (select max(id) from Books) - @contor + 1)
set @record_loan_date = GETDATE()
set @record_due_date = GETDATE() + 10
set @record_restitution_date = GETDATE() + 10
set @record_mentions = 'mentions' + @contor_string

INSERT INTO Records(subscriber_id, book_id, book_ISBN, librarian_id, loan_date, due_date, restitution_date, mentions)
VALUES (@record_subscriber_id, @record_book_id, @record_book_ISBN, @record_librarian_id, @record_loan_date, @record_due_date, @record_restitution_date, @record_mentions);
end

set @contor = @contor + 1
end

END
go

