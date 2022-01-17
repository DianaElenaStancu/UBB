from domain.entities import Bug
from repository.repository import Repository
from service.service import Service


class Test:
    def run_all_test(self):
        self.__test_domain()
        self.__test_repository()
        self.__test_service()

    def __test_domain(self):
        bug = Bug(9,"frontend","app crashes randomly",6)
        alt_bug = Bug(13,"backend","database exceeds memory quota",9)
        assert bug.getId() == 9
        assert bug.getComponentaAfectata() == "frontend"
        assert bug.getDescriere() == "app crashes randomly"
        assert bug.getPrioritate() == 6
        assert bug == bug
        assert bug != alt_bug

    def __test_repository(self):
        with open("testing/test_repo.txt", "w") as f:
            f.write("9,frontend,app crashes randomly,6")
            f.write("\n")
            f.write("\n")
            f.write("13,backend,database exceeds memory quota,9")
        repo = Repository("testing/test_repo.txt")
        bug1 = Bug(9,"frontend","app crashes randomly",6)
        bug2 = Bug(13,"backend","database exceeds memory quota",9)
        bugs = repo.getAll()
        assert len(bugs) == 2
        assert bugs[0] == bug1
        assert bugs[1] == bug2

    def __test_service(self):
        with open("testing/test_repo.txt", "w") as f:
            f.write("9,frontend,app crashes randomly,6")
            f.write("\n")
            f.write("\n")
            f.write("13,backend,database exceeds memory quota,9")
            f.write("\n")
            f.write("4,backend,server crashes on duplicate id,8")
        repo = Repository("testing/test_repo.txt")
        srv = Service(repo)
        bug1 = Bug(9, "frontend", "app crashes randomly", 6)
        bug2 = Bug(13, "backend", "database exceeds memory quota", 9)
        bug3 = Bug(4,"backend","server crashes on duplicate id",8)

        #testam cerinta 1
        bugs = srv.cautaDupaDescriere("crashes")
        assert len(bugs) == 2
        assert bugs[0] == bug3
        assert bugs[1] == bug1

        #testam cerinta 2
        bugs_dict = srv.mediePrioritati()
        assert len(bugs_dict) == 2
        assert bugs_dict["backend"] == 8.5
        assert bugs_dict["frontend"] == 6.0


