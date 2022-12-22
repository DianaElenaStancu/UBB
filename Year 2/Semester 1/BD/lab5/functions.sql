CREATE FUNCTION [dbo].[checkAddress]
(
	-- the parameters of the function here
	@address varchar(MAX)
)
RETURNS BIT
AS
BEGIN

	if not @address like '%_@__%.__%' or @address is null
		return 0

	return 1
END
go

-----------

CREATE FUNCTION [dbo].[checkAlphaNumeric]
(
	-- the parameters of the function here
	@name varchar(MAX)
)
RETURNS BIT
AS
BEGIN

	if  @name like '%[^a-zA-Z0-9 ]%'
		return 0

	return 1
END
go

----------

CREATE FUNCTION [dbo].[checkISBN]
(
	-- the parameters of the function here
	@ISBN varchar(MAX)
)
RETURNS BIT
AS
BEGIN

	if  @ISBN like '%[^a-zA-Z0-9]%' or (len(@ISBN) != 10 and len(@ISBN) != 13)
		return 0

	return 1
END
go

---------

CREATE FUNCTION [dbo].[checkPhone]
(
	-- the parameters of the function here
	@phone_number varchar(MAX)
)
RETURNS BIT
AS
BEGIN

	if  @phone_number like '[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]'
		return 1

	return 0
END
go


--------

