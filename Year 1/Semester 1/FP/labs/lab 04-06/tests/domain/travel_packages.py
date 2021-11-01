from datetime import date
from app.domain.travel_packages import create_pocket, get_start_date, get_finish_date, get_destination, get_price
def test_create_pocket():
    pocket = create_pocket(date(2021, 10, 21), date(2021, 10, 31), 'Zurich', 1100)
    assert(type(pocket) == dict)
    assert(get_start_date(pocket).day == 21)
    assert (get_start_date(pocket).month == 10)
    assert (get_start_date(pocket).year == 2021)
    assert (get_finish_date(pocket).day == 31)
    assert (get_finish_date(pocket).month == 10)
    assert (get_finish_date(pocket).year == 2021)
    assert (get_destination(pocket) == 'Zurich')
    assert (get_price(pocket) == 1100)
    print("test_create_pocket passed")
    #cazurile cu input gresit trateaza-le!!