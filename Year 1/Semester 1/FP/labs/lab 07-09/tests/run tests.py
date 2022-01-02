from domain.entities import *
from domain.validators import *
from repository.events_repo import *
from service.events_service import *


def test_all():
    #domain
    test_entities = entities_TEST()
    test_entities.run()
    test_validator = validator_TEST()
    test_validator.run()
    #repo
    test_repo = repo_TEST()
    test_repo.run()
    #srv
    test_srv =srv_TEST()
    test_srv.run()

    print("test passed :)")

test_all()