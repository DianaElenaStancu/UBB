from repository.repository import Repository
from service.service import Service
from testing.tests import Test
from ui.console import Console

test = Test()
test.run_all_test()
print("tests passed :)")
repo = Repository("repository/bugs.txt")
srv = Service(repo)
console = Console(srv)
console.run()