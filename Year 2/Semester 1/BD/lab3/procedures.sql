USE library_database

CREATE PROCEDURE UpdateVersiune1
AS
    BEGIN
	    SET NOCOUNT ON; /*the number of rows that are affected is not returned*/

	    ALTER TABLE Books
        ALTER COLUMN ISBN char(10)

        UPDATE Versiune
        SET Versiune = 1;

	    PRINT 'UPGRADE V1: Tabel Books, Coloana ISBN, TIP char(10).'
    END;
GO

CREATE PROCEDURE DownVersiune1
AS
    BEGIN
	    SET NOCOUNT ON;

	    ALTER TABLE Books
        ALTER COLUMN ISBN varchar(20)

        UPDATE Versiune
        SET Versiune = 0;

	    PRINT 'DOWNGRADE V0: Tabel Books, Coloana ISBN, TIP varchar(20).'
    END;
GO

CREATE PROCEDURE UpdateVersiune2
AS
   IF EXISTS(SELECT * FROM sys.default_constraints WHERE NAME = 'DF_Active')
       BEGIN
           PRINT 'Exista deja constrangere pentru valoare implicita la Active'
       END
   ELSE
		BEGIN
		    SET NOCOUNT ON;

	        ALTER TABLE Books
            ADD CONSTRAINT DF_Active DEFAULT 1 FOR active;

            UPDATE Versiune
            SET Versiune = 2;

		    PRINT 'UPGRADE V2: Tabel Books, Coloana active, DEFAULT VALUE 1'
		END;
GO

CREATE PROCEDURE DownVersiune2
AS
	IF NOT EXISTS(SELECT * FROM sys.default_constraints WHERE NAME = 'DF_Active')
	    BEGIN
	        PRINT 'NU exista constrangere pentru valoare implicita Active'
	    END
    ELSE
	    BEGIN
		    SET NOCOUNT ON;

	        ALTER TABLE Books
            DROP CONSTRAINT DF_Active;

            UPDATE Versiune
            SET Versiune = 1;

		    PRINT 'DOWNGRADE V1: Tabel Books, Coloana active, NO DEFAULT VALUE'
	    END;
GO

CREATE PROCEDURE UpdateVersiune3
AS
	IF EXISTS(SELECT * FROM sys.tables WHERE NAME = 'Reviews')
	    BEGIN
		    PRINT 'Exista deja tabela Reviews in baza de date.'
	    END
	ELSE
	    BEGIN
		    SET NOCOUNT ON;

		    CREATE TABLE Reviews (
				id INT PRIMARY KEY IDENTITY(1, 1),
				Nota INT NOT NULL,
				book_id INT FOREIGN KEY REFERENCES Books(id),
				subscriber_id INT FOREIGN KEY REFERENCES Subscribers(id),
			    librarian_id INT NOT NULL
			);

		    UPDATE Versiune
		    SET Versiune = 3;

		    PRINT 'UPGRADE V3: create table Reviews'
	    END;
GO

CREATE PROCEDURE DownVersiune3
AS
	IF NOT EXISTS(SELECT * FROM sys.tables WHERE NAME = 'Reviews')
	    BEGIN
		    PRINT 'Nu exista o tabela Reviews in baza de date.'
	    END
	ELSE
	    BEGIN
		    SET NOCOUNT ON;

		    DROP TABLE Reviews;

		    UPDATE Versiune
		    SET Versiune = 2;

		    PRINT 'DOWNGRADE V2: drop table Reviews'
	    END;
GO

CREATE PROCEDURE UpdateVersiune4
AS
	IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Reviews')
	    BEGIN
		    PRINT 'Nu exista tabela Reviews.'
	    END
	ELSE IF EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'Reviews' AND COLUMN_NAME = 'mentiuni')
	    BEGIN
		    PRINT 'Exista deja campul Mentiuni in tabela Reviews'
	    END
	ELSE
	    BEGIN
		    SET NOCOUNT ON;

		    ALTER TABLE Reviews
			ADD mentiuni VARCHAR(200);

		    UPDATE Versiune
		    SET Versiune = 4;

		    PRINT 'UPGRADE V4: tabel Reviews, new column mentiuni'
	    END;
GO

CREATE PROCEDURE DownVersiune4
AS
	IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Reviews')
	    BEGIN
		    PRINT 'Nu exista tabela Reviews.'
	    END
	ELSE IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'Reviews' AND COLUMN_NAME = 'mentiuni')
	    BEGIN
		    PRINT 'NU exista campul Mentiuni in tabela Reviews'
	    END
	ELSE
		BEGIN
			SET NOCOUNT ON;

			ALTER TABLE Reviews
			DROP COLUMN mentiuni;

			UPDATE Versiune
			SET Versiune = 3;

		    PRINT 'DOWNGRADE V3: tabel Reviews, drop column mentiuni'
		END;
GO

CREATE PROCEDURE UpdateVersiune5
AS
    IF NOT EXISTS(SELECT * FROM sys.tables WHERE NAME = 'Reviews')
        BEGIN
		    PRINT 'Nu exista o tabela Reviews in baza de date.'
        END
	ELSE IF EXISTS(SELECT * FROM sys.foreign_keys WHERE NAME = 'FK_Reviews_Librarians')
	    BEGIN
		    PRINT 'Exista constrangerea de cheie straina pe tabela reviews'
		END
	ELSE
		BEGIN
			SET NOCOUNT ON;

            ALTER TABLE Reviews
			ADD CONSTRAINT FK_Reviews_Librarians FOREIGN KEY (librarian_id) REFERENCES Librarians(id);

			UPDATE Versiune
			SET Versiune = 5;

			PRINT 'UPGRADE V5: tabel Reviews, add constraint foreign key column librarian_id'
		END
GO

CREATE PROCEDURE DownVersiune5
AS
	IF NOT EXISTS(SELECT * FROM sys.foreign_keys WHERE NAME = 'FK_Reviews_Librarians')
	    BEGIN
		    PRINT 'Nu exista constrangerea de cheie straina pe tabela reviews'
	    END
	ELSE
		BEGIN
			SET NOCOUNT ON;

			ALTER TABLE Reviews
			DROP CONSTRAINT FK_Reviews_Librarians;

			UPDATE Versiune
			SET Versiune = 4;

			PRINT 'DOWNGRADE V4: tabel Reviews, drop constraint foreign key column librarian_id'
		END
GO


CREATE PROCEDURE TransformaVersiune
@VersiuneDorita INT
AS
BEGIN
	DECLARE @VersiuneCurenta INT;
	SELECT @VersiuneCurenta = V.Versiune
	FROM Versiune V;

	IF @VersiuneDorita < 0 OR @VersiuneDorita > 5
	BEGIN
		PRINT 'Argument invalid'
	END
	ELSE
	BEGIN
		SET NOCOUNT ON;

		DECLARE @Procedura VARCHAR(25)

		PRINT 'Versiunea curenta ' + CONVERT(VARCHAR(2), @VersiuneCurenta) + ' -----> ' + CONVERT(VARCHAR(2), @VersiuneDorita)

		IF @VersiuneCurenta < @VersiuneDorita
		BEGIN
			SET @VersiuneCurenta = @VersiuneCurenta + 1
			WHILE @VersiuneCurenta <= @VersiuneDorita
			BEGIN
				SET @Procedura = 'UpdateVersiune' + CONVERT(VARCHAR(2), @VersiuneCurenta);
				EXEC @Procedura
				SET @VersiuneCurenta = @VersiuneCurenta + 1
			END
		END
		ELSE
		BEGIN
			WHILE @VersiuneCurenta > @VersiuneDorita
			BEGIN
				SET @Procedura = 'DownVersiune' + CONVERT(VARCHAR(2), @VersiuneCurenta);
				EXEC @Procedura
				SET @VersiuneCurenta = @VersiuneCurenta - 1
			END
		END
	END
END
GO

EXEC TransformaVersiune @VersiuneDorita = 1;
