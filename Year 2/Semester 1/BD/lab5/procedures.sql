CREATE PROCEDURE [dbo].[crudBookd]
	@method varchar(max),
	@id int,
	@ISBN varchar(10),
	@title varchar(100),
	@author int,
	@language_id int,
	@subdepartment_id int,
	@publisher int,
	@active bit,
	@conditions varchar(20),
	@publication_date date,
	@mentions varchar(200)
AS
BEGIN
	SET NOCOUNT ON; --prevent extra results

	--Verify data

	DECLARE @RES BIT = 1
	DECLARE @comm varchar(250)

	if dbo.checkISBN (@ISBN) = 0
	begin
		print 'Invalid ISBN'
		set @res = 0
	end

	if dbo.checkAlphaNumeric (@title) = 0
	begin
		print 'Title must be an alphanumeric string'
		set @res = 0
	end


	--check if the book with the given id exists
	declare @book_exists bit
	set @book_exists = 0
	if exists(select * from dbo.Books where id = @id)
	begin
	    set @book_exists = 1
	end

	--check if the book exists in Records
	declare @book_exists_in_records bit
	set @book_exists_in_records = 0
	if exists(select * from dbo.Records where book_id = @id)
	begin
	    set @book_exists_in_records = 1
	end

	--check if the author exists in the Authors table
	declare @author_exists bit
	set @author_exists = 0
	if exists(select * from dbo.Authors where id = @author)
	begin
        set @author_exists = 1
    end

	--check if the id of the language exists in the Languages table
	declare @language_exists bit
	set @language_exists = 0
	if exists(select * from dbo.Languages where id = @language_id)
	begin
        set @language_exists = 1
    end

	--check if the id of the subdepartment_id exists in the BookSubdepartments table
	declare @subdepartment_exists bit
	set @subdepartment_exists = 0
	if exists(select * from dbo.BookSubdepartments where id = @subdepartment_id)
	begin
        set @subdepartment_exists = 1
    end

	--check if the id of the publisher exists in the Publishers table
	declare @publisher_exists bit
	set @publisher_exists = 0
	if exists(select * from dbo.Publishers where id = @publisher)
	begin
        set @publisher_exists = 1
    end

	--execute command

	if @RES = 1
	begin
		if @method = 'delete'
		begin
			if @book_exists = 0
			begin
				print 'The action cannot be performed because the id does not exist'
				return
			end

			if @book_exists_in_records = 1
			begin
				print 'The action cannot be performed because the id exists in Records Table'
				return
			end

			delete from Books
			where id = @id
			print 'Delete completed'
		end
		else if @method = 'insert'
		begin
		    if @author_exists = 0
			begin
                print 'The author does not exist'
			    return
            end
			if @language_exists = 0
			begin
                print 'The language does not exist'
			    return
            end
			if @subdepartment_exists = 0
			begin
                print 'The subdepartment does not exist'
			    return
            end
			if @publisher_exists = 0
			begin
                print 'The publisher does not exist'
			    return
            end
			insert into Books(ISBN, title, author, language_id, subdepartment_id, publisher, active, conditions, publication_date, mentions) values (@ISBN, @title, @author, @language_id, @subdepartment_id, @publisher, @active, @conditions, @publication_date, @mentions)
			print 'Insert complet'
		end
		else if @method = 'update'
		begin
            if @book_exists = 0
            begin
                print 'The book does not exist'
			    return
            end
			if @author_exists = 0
			begin
                print 'The author does not exist'
			    return
            end
			if @language_exists = 0
			begin
                print 'The language does not exist'
			    return
            end
			if @subdepartment_exists = 0
			begin
                print 'The subdepartment does not exist'
			    return
            end
			if @publisher_exists = 0
			begin
                print 'The publisher does not exist'
			    return
            end

			update Books
			set ISBN = @ISBN, title = @title, author = @author, language_id = @language_id, subdepartment_id = @subdepartment_id, publisher = @publisher, active = @active, conditions = @conditions, publication_date = @publication_date, mentions = @mentions
			where id = @id

			print 'Update completed'
		end
		else if @method = 'select'
		begin
			select * from Books
			where title = @title

			print 'Select completed'
		end
		else
			print 'Please insert a correct command!'
	end
END
go

--------------------

CREATE PROCEDURE [dbo].[crudRecords]
	@method varchar(MAX),
	@id int,
	@subscriber_id int,
	@book_id int,
	@librarian_id int,
	@loan_date date,
    @due_date date,
    @restitution_date date,
    @mentions varchar(200)
AS
BEGIN
	SET NOCOUNT ON; --prevent extra results

	--Verify data
	if @loan_date > @due_date
	begin
        print 'loan_date > due_date is not a valid input'
	    return
    end

	if @loan_date > @restitution_date
	begin
        print 'resitution_date > due_date is not a valid input'
	    return
    end

	DECLARE @RES BIT = 1

	--check if the id of the record exists in the Records table
	declare @record_exists bit
	set @record_exists = 0
	if exists(select * from dbo.Records where id = @id)
	begin
        set @record_exists = 1
    end

	--check if the subscriber with the given id exists in Subscribers table
	declare @subscriber_exists bit
	set @subscriber_exists = 0
	if exists(select * from dbo.Subscribers where id = @subscriber_id)
	begin
	    set @subscriber_exists = 1
	end


	--check if the book_id exists in the Books table
	declare @book_exists bit
	set @book_exists = 0
	if exists(select * from dbo.Books where id = @book_id)
	begin
        set @book_exists = 1
    end

	--check if the librarian_id exists in the Librarians table
	declare @librarian_exists bit
	set @librarian_exists = 0
	if exists(select * from dbo.Librarians where id = @librarian_id)
	begin
        set @librarian_exists = 1
    end


	--execute command

	if @RES = 1
	begin
		if @method = 'delete'
		begin
			if @record_exists = 0
			begin
				print 'The action cannot be performed because the id does not exist'
				return
			end

			delete from Records
			where id = @id
			print 'Delete completed'
		end
		else if @method = 'insert'
		begin
		    if @subscriber_exists = 0
			begin
                print 'The provided subscriber_id does not exist'
			    return
            end
			if @book_exists = 0
			begin
                print 'The provided book_id does not exist'
			    return
            end
			if @librarian_exists = 0
			begin
                print 'The provided librarian_id does not exist'
			    return
            end
			insert into Records(subscriber_id, book_id, librarian_id, loan_date, due_date, restitution_date, mentions) values (@subscriber_id, @book_id, @librarian_id, @loan_date, @due_date, @restitution_date, @mentions)
			print 'Insert complet'
		end
		else if @method = 'update'
		begin
		    if @subscriber_exists = 0
			begin
                print 'The provided subscriber_id does not exist'
			    return
            end
			if @book_exists = 0
			begin
                print 'The provided book_id does not exist'
			    return
            end
			if @librarian_exists = 0
			begin
                print 'The provided librarian_id does not exist'
			    return
            end

			update Records
			set subscriber_id = @subscriber_id, book_id = @book_id, librarian_id = @librarian_id, loan_date = @loan_date, due_date = @due_date, restitution_date = @restitution_date, mentions = @mentions
			where id = @id

			print 'Update completed'
		end
		else if @method = 'select'
		begin
			select * from Records
			where id = @id

			print 'Select completed'
		end
		else
			print 'Please insert a correct command!'
	end
END
go

--------------

CREATE PROCEDURE [dbo].[crudSubscribers]
	@method varchar(MAX),
	@id int,
	@first_name varchar(50),
	@last_name varchar(50),
    @address varchar(200),
    @phone_number varchar(20),
    @email varchar(50),
    @registration_date date,
    @group_id int,
    @mentions varchar(200)
AS
BEGIN
	SET NOCOUNT ON; --prevent extra results

	--Verify data

	DECLARE @RES BIT = 1
	DECLARE @comm varchar(250)

	if dbo.checkAlphaNumeric (@first_name) = 0
	begin
		print 'First name must be an alphanumeric string'
		set @res = 0
	end

	if dbo.checkAlphaNumeric (@last_name) = 0
	begin
		print 'Last name must be an alphanumeric string'
		set @res = 0
	end

	if dbo.checkAlphaNumeric (@address) = 0
	begin
		print 'Address must be an alphanumeric string'
		set @res = 0
	end

	if dbo.checkPhone (@phone_number) = 0
	begin
		print 'Invalid phone number'
		set @res = 0
	end

	if dbo.checkAddress (@email) = 0
	begin
		print 'Invalid email'
		set @res = 0
	end

	--check if the subscriber with the given id exists
	declare @subscriber_exists bit
	set @subscriber_exists = 0
	if exists(select * from dbo.Subscribers where id = @id)
	begin
	    set @subscriber_exists = 1
	end


	--check if the group_id exists in the SubscriberGroups table
	declare @subscriber_group_exists bit
	set @subscriber_group_exists = 0
	if exists(select * from dbo.SubscriberGroups where id = @group_id)
	begin
        set @subscriber_group_exists = 1
    end

	--check if the id of the subscriber exists in the Records table
	declare @subscriber_exists_in_records bit
	set @subscriber_exists_in_records = 0
	if exists(select * from dbo.Records where subscriber_id = @id)
	begin
        set @subscriber_exists_in_records = 1
    end

	--execute command

	if @RES = 1
	begin
		if @method = 'delete'
		begin
			if @subscriber_exists_in_records = 1
			begin
				print 'The action cannot be performed because the id exists in Records'
				return
			end

			if not @subscriber_exists = 1
			begin
				print 'The action cannot be performed because the id does not exist'
				return
			end

			delete from Subscribers
			where id = @id
			print 'Delete completed'
		end
		else if @method = 'insert'
		begin
		    if @subscriber_group_exists = 0
			begin
                print 'The provided group_id does not exist in SubscriberGroups table'
			    return
            end
			insert into Subscribers(first_name, last_name, address, phone_number, email, registration_date, group_id, mentions) values(@first_name, @last_name, @address, @phone_number, @email, @registration_date, @group_id, @mentions)
			print 'Insert complet'
		end
		else if @method = 'update'
		begin

			if @subscriber_exists = 0
			begin
				print 'The action cannot be performed because the id does not exist'
				return
			end

			if @subscriber_group_exists = 0
			begin
                print 'The provided group_id does not exist in SubscriberGroups table'
			    return
            end

			update Subscribers
			set first_name = @first_name, last_name = @last_name, address = @address, phone_number = @phone_number, email = @email, registration_date = @registration_date, group_id = @group_id, mentions = @mentions
			where id = @id

			print 'Update completed'
		end
		else if @method = 'select'
		begin
			select * from Subscribers
			where first_name = @first_name

			print 'Select completed'
		end
		else
			print 'Please insert a correct command!'
	end
END
go


