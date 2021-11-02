from app.domain.history import *
from app.domain.travel_packages import get_price, create_pocket
from app.utils.list_operations import add_pocket_to_list, remove_pocket_with_destination

def test_setup_history():
    history = setup_history(True)
    assert(len(history) == 2)
    assert(type(history) == list)
    assert(len(get_pocket_list(history)) == 6)
    assert(type(get_pocket_list(history)) == list)
    assert(get_price(get_pocket_list(history)[0]) == 1200)
    print("test_setup_history passed")

def test_undo():
    history = setup_history(True)
    test_lst1 = generate_pockets()
    new_pocket = create_pocket(date(2021, 10, 7),date(2021, 11, 7), 'Cluj', 3700)
    add_pocket_to_list(test_lst1, new_pocket)
    add_new_list_to_history(history, test_lst1)
    undo(history)
    assert(len(history) == 2)
    assert(len(get_pocket_list(history)) == 6)

    test_lst2 = generate_pockets()
    destination = 'paris'
    test_lst2 = remove_pocket_with_destination(test_lst2, destination)
    add_new_list_to_history(history, test_lst2)
    undo(history)
    assert(len(history) == 2)
    assert(len(get_pocket_list(history)) == 6)

    history = setup_history(True)
    test_lst1 = generate_pockets()
    new_pocket = create_pocket(date(2021, 10, 7), date(2021, 11, 7), 'Cluj', 3700)
    add_pocket_to_list(test_lst1, new_pocket)
    add_new_list_to_history(history, test_lst1)
    assert (len(history) == 3)

    test_lst2 = generate_pockets()
    destination = 'paris'
    test_lst2 = remove_pocket_with_destination(test_lst2, destination)
    add_new_list_to_history(history, test_lst2)
    assert (len(history) == 4)
    undo(history)
    assert (len(history) == 3)
    undo(history)
    assert (len(history) == 2)
    undo(history)
    assert (len(history) == 1)
    try:
        undo(history)
        assert (False)
    except:
        assert (True)
    print("test_undo passed")

def test_add_new_list_to_history():
    history = setup_history(False)
    test_lst = generate_pockets()
    add_new_list_to_history(history, test_lst)
    assert(len(history) == 2)
    print("test_add_new_list_to_history passed")