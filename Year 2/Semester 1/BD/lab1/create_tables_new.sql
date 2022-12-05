CREATE DATABASE library_database
GO
USE library_database
GO

CREATE TABLE Librarians(
id INT PRIMARY KEY IDENTITY(1,1),
first_name varchar(50) NOT NULL,
last_name varchar(50) NOT NULL,
email varchar(50) UNIQUE,
mentions varchar(200)
)

CREATE TABLE SubscriberGroups(
id INT PRIMARY KEY IDENTITY(1,1),
name varchar(50) NOT NULL UNIQUE,
mentions varchar(200)
)

CREATE TABLE Subscribers(
id INT PRIMARY KEY IDENTITY(1,1),
first_name varchar(50) NOT NULL,
last_name varchar(50) NOT NULL,
address varchar(200) NOT NULL,
phone_number varchar(20) NOT NULL,
email varchar(50) NOT NULL,
registration_date date NOT NULL,
group_id INT FOREIGN KEY REFERENCES SubscriberGroups(id),
mentions varchar(200)
)

CREATE TABLE Languages(
id INT PRIMARY KEY IDENTITY(1,1),
name varchar(100) NOT NULL,
)

CREATE TABLE BookDepartments(
id INT PRIMARY KEY IDENTITY(1,1),
name varchar(100) NOT NULL,
)

CREATE TABLE BookSubdepartments(
id INT PRIMARY KEY IDENTITY(1,1),
name varchar(100) NOT NULL,
department_id INT FOREIGN KEY REFERENCES BookDepartments(id)
)

CREATE TABLE Authors(
id INT PRIMARY KEY IDENTITY(1,1),
first_name varchar(50) NOT NULL,
last_name varchar(50) NOT NULL,
subjects varchar(200) NOT NULL,
nationality varchar(50) NOT NULL,
birth_date date NOT NULL,
death_date date,
mentions varchar(200)
)

CREATE TABLE Publishers(
id INT PRIMARY KEY IDENTITY(1,1),
name varchar(100) NOT NULL,
address varchar(200) NOT NULL,
phone_number varchar(20) NOT NULL,
email varchar(50) NOT NULL,
mentions varchar(200)
)

CREATE TABLE Books(
id INT PRIMARY KEY IDENTITY(1,1),
ISBN varchar(20) default '-',
title varchar(100) NOT NULL,
author INT FOREIGN KEY REFERENCES Authors(id),
language_id INT FOREIGN KEY REFERENCES Languages(id),
subdepartment_id INT FOREIGN KEY REFERENCES BookSubdepartments(id),
publisher INT FOREIGN KEY REFERENCES Publishers(id),
active bit default 0,
conditions varchar(20) NOT NULL,
publication_date date NOT NULL,
mentions varchar(200)
)

CREATE TABLE Records(
id INT PRIMARY KEY IDENTITY(1,1),
subscriber_id INT FOREIGN KEY REFERENCES Subscribers(id),
book_id INT FOREIGN KEY REFERENCES Books(id),
librarian_id INT FOREIGN KEY REFERENCES Librarians(id),
loan_date date NOT NULL,
due_date date NOT NULL,
restitution_date date,
mentions varchar(200)
)

