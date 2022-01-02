from app.domain.validators import PersonValidator, EventValidator, ParticipationValidator
from app.repository.events_repo import EventsRepository, PersonsRepository, ParticipationsRepository, \
    PersonsRepositoryFile, EventsRepositoryFile, ParticipationsRepositoryFile
from app.service.events_service import PersonService, EventService, ParticipationService
from app.utils.id_generator import IdGenerator
from ui.console import PersonUI, EventUI, ParticipationUI, Console


generator = IdGenerator('utils/id_history.txt')
PersonValidator = PersonValidator()
#PersonRepository = PersonsRepository()
PersonRepository = PersonsRepositoryFile('data/persons.txt')
PersonService = PersonService(PersonRepository, PersonValidator, generator)
PersonUI = PersonUI(PersonService)

EventValidator = EventValidator()
#EventRepository = EventsRepository()
EventRepository = EventsRepositoryFile('data/events.txt')
EventService = EventService(EventRepository, EventValidator, generator)
EventUI = EventUI(EventService)

#ParticipationRepository = ParticipationsRepository()
ParticipationRepository = ParticipationsRepositoryFile('data/participations.txt')
ParticipationService = ParticipationService(PersonRepository, EventRepository, ParticipationRepository)
ParticipationUI = ParticipationUI(ParticipationService)

ui = Console(PersonUI, EventUI, ParticipationUI)
ui.show_ui()