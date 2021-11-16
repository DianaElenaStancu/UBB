from domain.entities import *
from domain.validators import *
from repository.events_repo import *
from service.events_service import *

def test_all():
    #domain
    test_create_person()
    test_create_event()
    test_validate_event()
    test_validate_person()
    test_validate_event_date()
    test_validate_event_time()
    test_validate_person_name()
    test_validate_person_address()
    test_validate_event_description()
    #repo
    test_store_person()
    test_delete_person()
    test_modify_person_name()
    test_modify_person_address()
    test_store_event()
    test_delete_event()
    test_modify_event_date()
    test_modify_event_time()
    test_modify_event_description()
    test_search_person_by_value()
    test_search_event_by_value()
    #srv
    test_add_person()
    test_add_event()
    test_del_person()
    test_del_event()
    test_modify_event()
    test_modify_person()
    test_search_event()
    test_search_person()

    print("test passed :)")

test_all()