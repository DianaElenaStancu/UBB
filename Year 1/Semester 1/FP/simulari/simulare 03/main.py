from repository.repository import Repo
from service.service import Service
from ui.console import Console

repo = Repo("repository/picturi.txt")
srv = Service(repo)
console = Console(srv)
console.run()
