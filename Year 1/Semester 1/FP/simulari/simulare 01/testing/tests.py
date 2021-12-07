from domain.entities import Elicopter
from repository.filerepo import RepoFile
from service.service import Service


class Test:
    def run_all_tests(self):
        self.__domain_tests()
        self.__repo_tests()
        self.__service_tests()

    def __domain_tests(self):
        elicopter1 = Elicopter(1, "Flamingo", "agricultura vacanta medical", 2014)
        elicopter2 = Elicopter(2, "Apache", "militar medical", 2019)
        assert elicopter1.getId() == 1
        assert elicopter1.getNume() == "Flamingo"
        assert elicopter1.getScopuri() == "agricultura vacanta medical"
        assert elicopter1.getAnFabricatie() == 2014
        assert elicopter1 != elicopter2
        assert elicopter1 == elicopter1

    def __repo_tests(self):
        with open("test_repo.txt", 'w') as f:
            f.write("12,Flamingo,agricultura vacanta medical,2014")
            f.write("\n")
            f.write("2,Apache,militar medical,1995")
        repo = RepoFile("test_repo.txt")
        elicoptere = repo.getAll()
        assert len(elicoptere) == 2
        elicopter1 = Elicopter(12, "Flamingo", "agricultura vacanta medical", 2014)
        elicopter2 = Elicopter(2, "Apache", "militar medical", 2019)
        assert elicopter1 == elicoptere[0]
        assert elicopter2 == elicoptere[1]

    def __service_tests(self):
        with open("test_repo.txt", 'w') as f:
            f.write("12,Flamingo,agricultura vacanta medical,2014")
            f.write("\n")
            f.write("2,Apache,militar medical,1995")
            f.write("\n")
            f.write("45,Stark Rebound,militar livrare,2019")
        elicopter1 = Elicopter(12, "Flamingo", "agricultura vacanta medical", 2014)
        elicopter2 = Elicopter(2, "Apache", "militar medical", 2019)
        elicopter3 = Elicopter(45,"Stark Rebound","militar livrare",2019)
        repo = RepoFile("test_repo.txt")
        srv = Service(repo)

        #teste pentru cerinta 1
        elicoptere_sortate = srv.findByScope("medical")
        assert len(elicoptere_sortate)
        assert elicoptere_sortate[0] == elicopter1
        assert elicoptere_sortate[1] == elicopter2

        #teste pentru cerinta 2
        elicoptere_dict = srv.getAllScopes()
        assert len(elicoptere_dict) == 5
        assert elicoptere_dict["agricultura"] == ["2014"]
        assert elicoptere_dict["medical"] == ["2014", "1995"]
        assert elicoptere_dict["vacanta"] == ["2014"]
        assert elicoptere_dict["militar"] == ["1995","2019"]
        assert elicoptere_dict["livrare"] == ["2019"]


