use library_database_lab4
go

INSERT INTO Authors(first_name, last_name, subjects, nationality, birth_date, death_date, mentions)
    VALUES ('Jack', 'Rosewood', 'Fiction', 'USA', datetimefromparts(1970,10,31,0,0,0,0) , '', '');

INSERT INTO BookDepartments(name)
    VALUES ('Arts & Music');

INSERT INTO BookSubdepartments(name, department_id)
    VALUES ('Art History', 1);

INSERT INTO Librarians(first_name, last_name, email, mentions)
    VALUES ('Evelina', 'Ilie', 'evelinai@gmail.com', 'studenta la limbi straine, lucreaza part-time');

INSERT INTO Publishers(name, address, phone_number, email, mentions)
    VALUES ('Taylor & Francis Ltd', 'Park Square Milton Park Abingdon OX14 4RN', '+442080520500', 'enquiries@taylorandfrancis.com', '');

INSERT INTO SubscriberGroups(name, mentions)
    VALUES ('student', 'prioritate la materialele educationale');

INSERT INTO Subscribers(first_name, last_name, address, phone_number, email, registration_date, group_id, mentions)
    VALUES ('Paul', 'Maresal', 'str. Aurel Vlaicu nr. 5, Cluj-Napoca', '0771657834', 'paul@gmail.com', datetimefromparts(1998,11,22,0,0,0,0), 1, 'student la drept');



delete Records;
delete Books;
delete Languages;
EXEC [dbo].insert_rows @nb_of_rows = 3, @table_name = 'Languages'
EXEC [dbo].insert_rows @nb_of_rows = 3, @table_name = 'Books'
EXEC [dbo].insert_rows @nb_of_rows = 3, @table_name = 'Records'

EXEC [dbo].delete_rows @nb_of_rows = 3, @table_name = 'Records'
EXEC [dbo].delete_rows @nb_of_rows = 3, @table_name = 'Books'
EXEC [dbo].delete_rows @nb_of_rows = 3, @table_name = 'Languages'

select * from view_books
select * from view_languages_books_records
select * from view_group_by

exec select_view @view_name = 'view_group_by'

insert into tables(name)
    values ('Languages'),
           ('Books'),
           ('Records');

insert into views(name)
    values ('view_books'),
           ('view_languages_books_records'),
           ('view_group_by');

insert into tests(name)
    values ('delete_rows'),
           ('insert_rows'),
           ('select_view');


insert TestViews(testid, viewid)
    values (3, 1),
           (3, 2),
           (3, 3);

insert TestTables(testid, tableid, noofrows, position)
    values (1, 1, 1000, 3),
           (1, 2, 1000, 2),
           (1, 3, 1000, 1),
           (2, 1, 1000, 1),
           (2, 2, 1000, 2),
           (2, 3, 1000, 3);


exec main @nb_of_rows = 1000

