from domain.travel_packages import *
from domain.history import *
from utils.list_operations import *


def run_tests():
    test_create_pocket()
    test_add_pocket_to_list()
    test_valid_period()
    test_remove_pocket_with_destination()
    test_remove_pocket_with_smaller_duration()
    test_fits_in_the_period()
    test_nr_pockets_with_given_destination()
    test_average_price_of_pockets_with_given_destination()
    test_ordered_pockets_by_price_with_given_destination()
    test_remove_pocket_with_greater_price_and_different_destination()
    test_remove_pocket_with_same_month()
    test_setup_history()
    test_undo()
    test_add_new_list_to_history()
    test_make_list_copy()

run_tests()