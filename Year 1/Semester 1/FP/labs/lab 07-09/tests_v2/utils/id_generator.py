from app.utils.id_generator import IdGenerator


def test_IdGenerator():
    generator = IdGenerator("test_id_generator.txt")
    idp = generator.generate_id("person")
    assert idp == 1
    ide = generator.generate_id("event")
    assert ide == 1
    idr = generator.generate_id("participation")
    assert idr == 1
    idr = generator.generate_id("participation")
    assert idr == 2