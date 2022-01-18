from domain.entitities import Student, Lab

class RepoError(Exception):
    pass

class StudentRepository:
    def __init__(self, filename):
        self.__filename = filename
        self.__students = []
        self.__loadFromFile()

    def __loadFromFile(self):
        with open(self.__filename, "r") as f:
            self.__students = []
            for line in f:
                line = line.strip()
                try:
                    attrs = line.split(";")
                    id = int(attrs[0])
                    name = attrs[1]
                    student = Student(id, name)
                    self.__students.append(student)
                except:
                    continue

    def __saveToFile(self):
        with open(self.__filename, "w") as f:
            for student in self.__students:
                f.write(student.to_string())
                f.write("\n")

    def searchStudentById(self, id):
        for student in self.__students:
            if student.getId() == id:
                return student
        raise RepoError("nu exista student cu id-ul dat")


    def getAll(self):
        self.__loadFromFile()
        return self.__students


class LabRepository:
    def __init__(self, filename):
        self.__filename = filename
        self.__labs = []
        self.__loadFromFile()

    def __loadFromFile(self):
        with open(self.__filename, "r") as f:
            self.__labs = []
            for line in f:
                line = line.strip()
                try:
                    attrs = line.split(";")
                    studentId = int(attrs[0])
                    labNumber = int(attrs[1])
                    problemNumber = attrs[2]
                    lab = Lab(studentId, labNumber, problemNumber)
                    self.__labs.append(lab)
                except:
                    continue

    def searchStudentLabs(self, studentId):
        searchedLabs =[]
        for lab in self.__labs:
            if lab.getStudentId() == studentId:
                searchedLabs.append(lab)
        return searchedLabs


    def addLab(self, studentId, labNumber, problemNumber):
        lab = Lab(studentId, labNumber, problemNumber)
        if lab in self.__labs:
            raise RepoError("laboratorul deja assignat")
        self.__labs.append(lab)
        self.__saveToFile()
        return lab


    def __saveToFile(self):
        with open(self.__filename, "w") as f:
            for lab in self.__labs:
                f.write(lab.to_string())
                f.write("\n")

    def getAll(self):
        self.__loadFromFile()
        return self.__labs