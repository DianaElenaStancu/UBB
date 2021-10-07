
"""2. Se da data nașterii (zi/luna/an), determinați vârsta persoanei in zile."""
import datetime

string_date = input()
day, month, year = [int(x) for x in string_date.split("/") if x.strip()]
#print(day, month, year)
birth_date = datetime.date(year, month, day)
end_date = date.today()
time_difference = end_date - birth_date
ageInDays = time_difference.days
print(ageInDays)
