from app.domain.validators import PersonValidator, EventValidator, ParticipationValidator
from app.repository.events_repo import EventsRepository, PersonsRepository, ParticipationsRepository, \
    PersonsRepositoryFile, EventsRepositoryFile, ParticipationsRepositoryFile
from app.service.events_service import PersonService, EventService, ParticipationService
from ui.console import PersonUI, EventUI, ParticipationUI, Console

PersonValidator = PersonValidator()
#PersonRepository = PersonsRepository()
PersonRepository = PersonsRepositoryFile('data/persons.txt')
PersonService = PersonService(PersonRepository, PersonValidator)
PersonUI = PersonUI(PersonService)

EventValidator = EventValidator()
#EventRepository = EventsRepository()
EventRepository = EventsRepositoryFile('data/events.txt')
EventService = EventService(EventRepository, EventValidator)
EventUI = EventUI(EventService)

#ParticipationRepository = ParticipationsRepository()
ParticipationRepository = ParticipationsRepositoryFile('data/participations.txt')
ParticipationService = ParticipationService(PersonRepository, EventRepository, ParticipationRepository)
ParticipationUI = ParticipationUI(ParticipationService)

ui = Console(PersonUI, EventUI, ParticipationUI)
ui.show_ui()