USE [library_database_lab4]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[main]
	-- Add the parameters for the stored procedure here
	@nb_of_rows varchar(30)
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

	--SET @nb_of_rows = cast(@nb_of_rows as INT)

	declare @all_start datetime
	set @all_start = GETDATE();

	declare @records_delete_start datetime
	set @records_delete_start = GETDATE()
	execute delete_rows @nb_of_rows, 'Records'
	declare @records_delete_end datetime
	set @records_delete_end = GETDATE()

	declare @books_delete_start datetime
	set @books_delete_start = GETDATE()
	execute delete_rows @nb_of_rows, 'Books'
	declare @books_delete_end datetime
	set @books_delete_end = GETDATE()

	declare @languages_delete_start datetime
	set @languages_delete_start = GETDATE()
	execute delete_rows @nb_of_rows, 'Languages'
	declare @languages_delete_end datetime
	set @languages_delete_end = GETDATE()


	declare @languages_insert_start datetime
	set @languages_insert_start = GETDATE()
	execute insert_rows @nb_of_rows, 'Languages'
	declare @languages_insert_end datetime
	set @languages_insert_end = GETDATE()

	declare @books_insert_start datetime
	set @books_insert_start = GETDATE()
	execute insert_rows @nb_of_rows, 'Books'
	declare @books_insert_end datetime
	set @books_insert_end = GETDATE()

	declare @records_insert_start datetime
	set @records_insert_start = GETDATE()
	execute insert_rows @nb_of_rows, 'Records'
	declare @records_insert_end datetime
	set @records_insert_end = GETDATE()

	declare @view_1_table_start datetime
	set @view_1_table_start = GETDATE()
	execute select_view 'view_books'
	declare @view_1_table_end datetime
	set @view_1_table_end = GETDATE()

	declare @view_2_tables_start datetime
	set @view_2_tables_start = GETDATE()
	execute select_view 'view_languages_books_records'
	declare @view_2_tables_end datetime
	set @view_2_tables_end = GETDATE()

	declare @view_2_tables_group_by_start datetime
	set @view_2_tables_group_by_start = GETDATE()
	execute select_view 'view_group_by'
	declare @view_2_tables_group_by_end datetime
	set @view_2_tables_group_by_end = GETDATE()

	declare @all_stop datetime
	set @all_stop = getdate()

	declare @description varchar(100)
	set @description = 'TestRun' + convert(varchar(7), (select max(TestRunID) from TestRuns)) + 'delete, insert' + @nb_of_rows + 'rows, select all views'

	insert into TestRuns(Description, StartAt, EndAt)
	values(@description, @all_start, @all_stop);

	declare @lastTestRunID int;
	set @lastTestRunID = (select max(TestRunID) from TestRuns);

	insert into TestRunTables
	values(@lastTestRunID, 1, @languages_delete_start, @languages_insert_end)

    insert into TestRunTables
	values(@lastTestRunID, 2, @books_delete_start, @books_insert_end)

	insert into TestRunTables
	values(@lastTestRunID, 3, @records_delete_start, @records_insert_end)


	insert into TestRunViews
	values(@lastTestRunID, 1, @view_1_table_start, @view_1_table_end)

	insert into TestRunViews
	values(@lastTestRunID, 2, @view_2_tables_start, @view_2_tables_end)

	insert into TestRunViews
	values(@lastTestRunID,3, @view_2_tables_group_by_start, @view_2_tables_group_by_end)



END
