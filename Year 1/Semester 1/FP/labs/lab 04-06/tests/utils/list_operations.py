from app.utils.list_operations import add_pocket_to_list, valid_period, remove_pocket_with_destination, remove_pocket_with_smaller_duration, remove_pocket_with_greater_price, fits_in_the_period, nr_pockets_with_given_destination, average_price_of_pockets_with_given_destination, ordered_pockets_by_price_with_given_destination, remove_pocket_with_same_month, remove_pocket_with_greater_price_and_different_destination, make_list_copy
from app.domain.travel_packages import *
from app.domain.history import generate_pockets

def test_add_pocket_to_list():
    test_list = []
    pocket1 = create_pocket(date(2022, 10, 1), date(2022, 10, 12), 'New York', 1000)
    pocket2 = create_pocket(date(2023, 11, 3), date(2023, 11, 10), 'Tokyo', 2400)

    add_pocket_to_list(test_list, pocket1)
    assert(len(test_list)==1)
    assert(get_start_date(test_list[0]).day == 1)
    assert(get_start_date(test_list[0]).month == 10)
    assert(get_start_date(test_list[0]).year == 2022)
    assert(get_finish_date(test_list[0]).day == 12)
    assert(get_finish_date(test_list[0]).month == 10)
    assert(get_finish_date(test_list[0]).year == 2022)
    assert(get_destination(test_list[0]) == 'New York')
    assert (get_price(test_list[0]) == 1000)

    add_pocket_to_list(test_list, pocket2)
    assert (len(test_list) == 2)
    assert (get_start_date(test_list[0]).day == 1)
    assert (get_start_date(test_list[0]).month == 10)
    assert (get_start_date(test_list[0]).year == 2022)
    assert (get_finish_date(test_list[0]).day == 12)
    assert (get_finish_date(test_list[0]).month == 10)
    assert (get_finish_date(test_list[0]).year == 2022)
    assert (get_destination(test_list[0]) == 'New York')
    assert (get_price(test_list[0]) == 1000)

    assert (get_start_date(test_list[1]).day == 3)
    assert (get_start_date(test_list[1]).month == 11)
    assert (get_start_date(test_list[1]).year == 2023)
    assert (get_finish_date(test_list[1]).day == 10)
    assert (get_finish_date(test_list[1]).month == 11)
    assert (get_finish_date(test_list[1]).year == 2023)
    assert (get_destination(test_list[1]) == 'Tokyo')
    assert (get_price(test_list[1]) == 2400)

    print("test_add_pocket_to_list passed")

def test_valid_period():
    assert(valid_period(date(2022, 10, 12), date(2022, 10, 20)) == True)
    assert(valid_period(date(2022, 10, 12), date(2022, 10, 12)) == False)
    assert (valid_period(date(2022, 10, 12), date(2022, 10, 2)) == False)
    assert (valid_period(date(2022, 10, 12), date(2022, 9, 20)) == False)
    assert (valid_period(date(2022, 10, 12), date(2020, 10, 20)) == False)
    print("test_valid_period passed")

def test_remove_pocket_with_destination():
    test_list1 = generate_pockets()
    init_len = len(test_list1)
    destination_test = 'Paris'
    test_list1 = remove_pocket_with_destination(test_list1, destination_test)

    assert(len(test_list1) == init_len - 2)
    assert(len([pocket for pocket in test_list1 if get_destination(pocket) == destination_test]) == 0)
    init_len = len(test_list1)

    test_list1 = remove_pocket_with_destination(test_list1, destination_test)
    assert(len(test_list1) == init_len)

    destination_test = 'Brasov'
    test_list1 = remove_pocket_with_destination(test_list1, destination_test)
    assert(len(test_list1) == init_len)

    test_list2 = []
    test_list2 = remove_pocket_with_destination(test_list2, destination_test)
    assert (len(test_list2) == 0)

    destination_test = ''
    test_list1 = remove_pocket_with_destination(test_list1, destination_test)
    assert (len(test_list1) == init_len)
    test_list2 = remove_pocket_with_destination(test_list2, destination_test)
    assert (len(test_list2) == 0)

    print("test_remove_pocket_with_destination passed")

def test_remove_pocket_with_smaller_duration():
    test_list1 = generate_pockets()
    duration = 7
    init_len = len(test_list1)
    test_list1 = remove_pocket_with_smaller_duration(test_list1, duration)
    assert(len(test_list1) == init_len - 2)
    duration = 30
    test_list1 = remove_pocket_with_smaller_duration(test_list1, duration)
    assert(len(test_list1) == 1)
    duration = 31
    test_list1 = remove_pocket_with_smaller_duration(test_list1, duration)
    assert (len(test_list1) == 1)
    duration = 32
    test_list1 = remove_pocket_with_smaller_duration(test_list1, duration)
    assert (len(test_list1) == 0)
    test_list1 = remove_pocket_with_smaller_duration(test_list1, duration)
    assert (len(test_list1) == 0)
    print("test_remove_pocket_with_smaller_duration passed")

def test_remove_pocket_with_greater_price():
    test_list = generate_pockets()
    init_len = len(test_list)
    price = 1500
    test_list = remove_pocket_with_greater_price(test_list, price)
    assert(len(test_list) == init_len - 1)
    price = 1000
    test_list = remove_pocket_with_greater_price(test_list, price)
    assert (len(test_list) == init_len - 3)
    price = 0
    test_list = remove_pocket_with_greater_price(test_list, price)
    assert (len(test_list) == 0)
    print("test_remove_pocket_with_greater_price passed")

def test_fits_in_the_period():
    assert(fits_in_the_period(date(2021, 10, 10), date(2021, 10, 20), date(2021, 10, 13), date(2021, 10, 30)) == False)
    assert (fits_in_the_period(date(2021, 10, 10), date(2021, 10, 20), date(2021, 10, 10), date(2021, 10, 20)) == True)
    assert (fits_in_the_period(date(2021, 10, 10), date(2021, 10, 20), date(2021, 9, 1), date(2021, 11, 1)) == True)
    assert (fits_in_the_period(date(2021, 10, 10), date(2021, 10, 20), date(2021, 9, 1), date(2021, 10, 9)) == False)
    assert (fits_in_the_period(date(2021, 10, 10), date(2021, 10, 20), date(2021, 10, 14), date(2021, 10, 19)) == False)
    print("test_fits_in_the_period passed")

def test_nr_pockets_with_given_destination():
    test_list = generate_pockets()
    assert(nr_pockets_with_given_destination(test_list, 'paris') == 2)
    assert (nr_pockets_with_given_destination(test_list, 'tenerife') == 1)
    assert (nr_pockets_with_given_destination(test_list, 'viena') == 1)
    assert (nr_pockets_with_given_destination(test_list, 'praga') == 0)
    test_list = []
    assert (nr_pockets_with_given_destination(test_list, 'kiev') == 0)
    print("test_nr_pockets_with_given_destination passed")

def test_average_price_of_pockets_with_given_destination():
    test_list = generate_pockets()
    assert(average_price_of_pockets_with_given_destination(test_list, 'paris') == 1200)
    assert(average_price_of_pockets_with_given_destination(test_list, 'viena') == 500)
    assert(average_price_of_pockets_with_given_destination(test_list, 'london') == 0)
    test_list.append(create_pocket(date(2021, 11, 20), date(2021,11,30), 'Paris', 229))
    assert (average_price_of_pockets_with_given_destination(test_list, 'paris') == 2629/3)
    print("test_average_price_of_pockets_with_given_destination")

def test_ordered_pockets_by_price_with_given_destination():
    test_list = generate_pockets()
    test_list.append(create_pocket(date(2021, 11, 3), date(2021, 11, 10), 'Tenerife', 2400))
    assert(ordered_pockets_by_price_with_given_destination(test_list, date(2021, 11, 3), date(2021, 11, 10)) == [create_pocket(date(2021, 11, 3), date(2021, 11, 10), 'Tenerife', 1200), create_pocket(date(2021, 11, 3), date(2021, 11, 10), 'Tenerife', 2400)])
    assert (ordered_pockets_by_price_with_given_destination(test_list, date(2024, 11, 3), date(2024, 11, 10)) == [])
    print("test_ordered_pockets_by_price_with_given_destination passed")

def test_remove_pocket_with_greater_price_and_different_destination():
    test_list = generate_pockets()
    destination = 'Paris'
    price = 200
    test_list = remove_pocket_with_greater_price_and_different_destination(test_list, price, destination)
    assert(2 == len(test_list))

    test_list = generate_pockets()
    destination = 'Viena'
    price = 1200
    test_list = remove_pocket_with_greater_price_and_different_destination(test_list, price, destination)
    assert (4 == len(test_list))

    test_list = generate_pockets()
    destination = 'Bucuresti'
    price = 100
    test_list = remove_pocket_with_greater_price_and_different_destination(test_list, price, destination)
    assert (0 == len(test_list))
    print("test_remove_pocket_with_greater_price_and_different_destination passed")

def test_remove_pocket_with_same_month():
    test_list = generate_pockets()
    month = 11
    test_list = remove_pocket_with_same_month(test_list, month)
    assert(len(test_list) == 4)

    month = 2
    test_list = remove_pocket_with_same_month(test_list, month)
    assert (len(test_list) == 3)

    month = 12
    test_list = remove_pocket_with_same_month(test_list, month)
    assert (len(test_list) == 3)

    month = 8
    test_list = remove_pocket_with_same_month(test_list, month)
    assert (len(test_list) == 2)

    month = 3
    test_list = remove_pocket_with_same_month(test_list, month)
    assert (len(test_list) == 1)

    month = 4
    test_list = remove_pocket_with_same_month(test_list, month)
    assert (len(test_list) == 0)

    month = 4
    test_list = remove_pocket_with_same_month(test_list, month)
    assert (len(test_list) == 0)
    print("test_remove_pocket_with_same_month passed")

def test_make_list_copy():
    lst = generate_pockets()
    new_lst = make_list_copy(lst)
    assert(lst == new_lst)

    print("test_make_list_copy passed")