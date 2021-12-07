from repository.repofile import Repo
from service.service import Service
from testing.tests import test_run_all
from ui.console import Console

test_run_all()
repo = Repo("repository/tv_shows.txt")
service = Service(repo)
console = Console(service)
console.run()