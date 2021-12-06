class IdGenerator:
    def __init__(self, filename):
        self.__filename = filename

    def __load_from_file(self):
        try:
            f = open(self.__filename, 'r')
        except IOError as ve:
            return #raise IdGenerator(str(ve))
        line = f.read()

        person_id, event_id, participation_id = [id.strip() for id in line.split(" ")]
        f.close()
        return [int(person_id), int(event_id), int(participation_id)]

    def __save_to_file(self, ids):
        with open(self.__filename, 'w') as f:
            f.write(str(ids[0])+" "+str(ids[1])+" "+str(ids[2]))

    def generate_id(self, entity):
        ids = self.__load_from_file()
        if(entity == "person"):
            pos = 0
        elif(entity == "event"):
            pos = 1
        else:
            pos = 2
        ids[pos] += 1
        self.__save_to_file(ids)
        return ids[pos]



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



