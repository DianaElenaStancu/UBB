USE [library_database_lab4]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[delete_rows]
-- Add the parameters for the stored procedure here
@nb_of_rows varchar(30),
@table_name varchar(30)
AS
BEGIN
-- SET NOCOUNT ON added to prevent extra result sets from
-- interfering with SELECT statements.
SET NOCOUNT ON;

-- Insert statements for procedure here
if ISNUMERIC(@nb_of_rows) != 1
BEGIN
print('Not a number')
return 1
END

SET @nb_of_rows = cast(@nb_of_rows as INT)

declare @last_row int
if @table_name = 'Languages'
begin
set @last_row = (select MAX(id) from Languages) - @nb_of_rows

delete from Languages
where id > @last_row
end

if @table_name = 'Books'
begin
set @last_row =(select MAX(id) from Books) - @nb_of_rows
delete from Books
where id > @last_row
end

if @table_name = 'Records'
begin
delete from Records
end
END
