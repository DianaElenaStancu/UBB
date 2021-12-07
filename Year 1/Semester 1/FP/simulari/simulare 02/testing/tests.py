from domain.entities import TvShow, ShowEvaluation
from repository.repofile import Repo


def test_run_all():
    test_create_TvShow()
    test_repo()
    test_create_ShowEvaluation()
    print("tests passed :)")

def test_create_TvShow():
    tv_show = TvShow("COM1", "The Good Place", "fantasy comedy", 53)
    assert tv_show.getId() == "COM1"
    assert tv_show.getTitlu() == "The Good Place"
    assert tv_show.getGen() == "fantasy comedy"
    assert tv_show.getNumarEps() == 53
    assert tv_show == tv_show

def test_create_ShowEvaluation():
    tv_show = TvShow("COM1", "The Good Place", "fantasy comedy", 53)
    show_evaluation_1 = ShowEvaluation(tv_show, 10)
    assert show_evaluation_1.get_preference() == "disliked"
    show_evaluation_2 = ShowEvaluation(tv_show, 40)
    assert show_evaluation_2.get_preference() == "favorite"
    show_evaluation_3 = ShowEvaluation(tv_show, 20)
    assert show_evaluation_3.get_preference() == "if_bored"

def test_repo():
    with open("testing/test_tv_show.txt", 'w') as f:
        f.write("COM1, The Good Place, fantasy comedy, 53")
        f.write("\n")
        f.write("\n")
        f.write("THR1, Mindhunter, psychological thriller, 19")
    repo = Repo("testing/test_tv_show.txt")
    tv_show_1 = TvShow("COM1", "The Good Place", "fantasy comedy", 53)
    tv_show_2 = TvShow("THR1", "Mindhunter", "psychological thriller", 19)
    tv_shows = repo.getAll()
    assert len(tv_shows) == 2
    assert tv_shows[0] == tv_show_1
    assert tv_shows[1] == tv_show_2
    try:
        repo.cauta_dupa_ID("dsaj")
        assert False
    except:
        assert True

    show_cautat = repo.cauta_dupa_ID("THR1")
    assert tv_show_2 == show_cautat

