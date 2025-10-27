from abc import ABC, abstractmethod

class Apartment(ABC):
    def __init__(self, number: int = 0, cleaning_time_per_room: float = 0.0) -> None:
        # store in "private" attributes and expose via properties
        self._number = int(number)
        self._cleaning_time_per_room = float(cleaning_time_per_room)

    # properties to allow `apt.number` and `apt.cleaning_time_per_room` access
    @property
    def number(self) -> int:
        return self._number

    @property
    def cleaning_time_per_room(self) -> float:
        return self._cleaning_time_per_room

    # abstract interface
    @abstractmethod
    def get_time(self) -> float:
        ...

    @abstractmethod
    def get_time_with_rooms(self, rooms_to_clean: int) -> float:
        ...

    @abstractmethod
    def is_single(self) -> bool:
        ...