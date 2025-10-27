from typing import List, Optional
from apartment import Apartment

class Hotel:
    def __init__(self):
        # store apartments as dict number -> Apartment
        self._rooms: dict[int, Apartment] = {}

    def add_apartment(self, apt: Apartment) -> None:
        self._rooms[int(apt.number)] = apt

    def remove_apartment(self, number: int) -> bool:
        return self._rooms.pop(int(number), None) is not None

    def find_apartment(self, number: int) -> Optional[Apartment]:
        return self._rooms.get(int(number))

    def count_time(self, tasks: List[tuple[int, Optional[int]]]) -> float:
        """
        tasks: list of tuples (apartment_number, rooms_to_clean_or_None)
        returns total minutes needed.
        """
        total = 0.0
        for apt_number, maybe_rooms in tasks:
            apt = self.find_apartment(apt_number)
            if apt is None:
                raise KeyError(f"Apartment {apt_number} not found")
            if maybe_rooms is None:
                # For multi apartments, treat it as cleaning ALL rooms.
                total += apt.get_time()
            else:
                total += apt.get_time_with_rooms(maybe_rooms)
        return total

    def output_apartments(self) -> List[Apartment]:
        # Return apartments sorted by number
        return [self._rooms[k] for k in sorted(self._rooms.keys())]
