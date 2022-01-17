from domain.validator import Validator
from repository.repository import Repository
from service.service import Service
from testing.tests import Test
from ui.console import Console

test = Test()
test.runAll()
print("tests passed :)")

val = Validator()
repo = Repository("repository/evenimente.txt")
srv = Service(repo, val)
console = Console(srv)
console.run()