from termcolor import colored

from repository.repository import RepoError


class LabController:
    def __init__(self, studentRepo, labRepo):
        self.__studentRepo = studentRepo
        self.__labRepo = labRepo
        self.__cmds = {
            "1": self.__showStudents,
            "2": self.__searchStudentById,
            "4": self.__showStudentLabs,
            "3": self.__assignLabToStudent,
            "5": self.__showLabsForStudents
        }


    def __printMenu(self):
        print(colored("************", 'yellow'))
        print("Comenzi disponibile: ")
        print("0 - exit")
        print("1 - vizualizare lista studenti")
        print("2 - cautare student dupa id")
        print("3 - assignare laborator la un student")
        print("4 - vizualizare toate laboratoarele de la un student")
        print("5 - vizualizare studenti si laboratoare assignate pentru un laborator dat")
        print(colored("************", 'yellow'))

    def run(self):
        exit = False
        while not exit:
            self.__printMenu()
            cmd = input("Comanda ta este: ")
            if cmd in self.__cmds:
                self.__cmds[cmd]()
            elif cmd == "0":
                exit = True
            else:
                print("Comanda indisponibila")

    def __showStudents(self):
        students = self.__studentRepo.getAll()
        print(colored("+++++++++", 'blue'))
        for student in students:
            print(student.to_string())
        print(colored("+++++++++", 'blue'))

    def __searchStudentById(self):
        try:
            id = int(input("Id-ul studentului: "))
            student = self.__studentRepo.searchStudentById(id)
            print(student.to_string())
        except ValueError as ve:
            print(str(ve))
        except RepoError as re:
            print(str(re))

    def __showStudentLabs(self):
        try:
            studentId = int(input("Id-ul studentului: "))
            labs = self.__labRepo.searchStudentLabs(studentId)
            print(colored("+++++++++", 'blue'))
            for lab in labs:
                print(lab.to_string())
            print(colored("+++++++++", 'blue'))
        except ValueError as ve:
            print(str(ve))
            return

    def __showLabsForStudents(self):
        students = self.__studentRepo.getAll()
        print(colored("+++++++++", 'blue'))
        for student in students:
            print("Studentul:", student.to_string(), "are urmatoarele laboratoare de facut: ")
            labs = self.__labRepo.searchStudentLabs(student.getId())
            for lab in labs:
                print(lab.getProblemNumber(), "lab:", lab.getLabNumber())
        print(colored("+++++++++", 'blue'))

    def __assignLabToStudent(self):
        try:
            studentId = int(input("id-ul studentului: "))
            labNumber = int(input("numarul lab-ului: "))
            problemNumber = input("numarul problemei: ")
            student = self.__studentRepo.searchStudentById(studentId)
            lab = self.__labRepo.addLab(studentId, labNumber, problemNumber)
            print(lab.to_string(), "adaugat cu succes!")
        except ValueError as ve:
            print(str(ve))
        except RepoError as re:
            print(str(re))
