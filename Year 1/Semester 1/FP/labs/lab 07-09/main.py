from domain.validators import PersonValidator, EventValidator
from repository.events_repo import EventsRepository, PersonsRepository
from service.events_service import PersonService, EventService
from ui.console import Console

PersonValidator = PersonValidator()
PersonRepository = PersonsRepository()
PersonService = PersonService(PersonRepository, PersonValidator)

EventValidator = EventValidator()
EventRepository = EventsRepository()
EventService = EventService(EventRepository, EventValidator)

ui = Console(PersonService, EventService)
ui.show_ui()