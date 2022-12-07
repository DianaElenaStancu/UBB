USE [library_database_lab4]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[select_view]
	-- Add the parameters for the stored procedure here
	@view_name varchar(30)
AS
BEGIN
	-- SET NOCOUNT ON added to prevent extra result sets from
	-- interfering with SELECT statements.
	SET NOCOUNT ON;

    -- Insert statements for procedure here
	if @view_name = 'view_books'
	begin
		select * from view_books
	end

	if @view_name = 'view_group_by'
	begin
		select * from view_group_by
	end

	if @view_name = 'view_languages_books_records'
	begin
		select * from view_languages_books_records
	end
END
