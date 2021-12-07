from repository.filerepo import RepoFile
from service.service import Service
from testing.tests import Test
from ui.console import Console

test = Test()
test.run_all_tests()
print("Tests passed :)")
repo = RepoFile("repository/elicoptere_repo.txt")
srv = Service(repo)
console = Console(srv)
console.run()