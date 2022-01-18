from repository.repository import StudentRepository, LabRepository
from ui.console import LabController

studentRepo = StudentRepository("repository/student.txt")
labRepo = LabRepository("repository/labs.txt")
labController = LabController(studentRepo, labRepo)
labController.run()