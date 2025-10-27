from apartment import Apartment

class Multapartment(Apartment):
    def __init__(self, number: int, cleaning_time_per_room: float, room_amount: int) -> None:
        super().__init__(number, cleaning_time_per_room)
        self._room_amount = int(room_amount)

    @property
    def room_amount(self) -> int:
        return self._room_amount

    def get_time(self) -> float:
        return self.cleaning_time_per_room*self.room_amount

    def get_time_with_rooms(self, rooms_to_clean: int) -> float:
        if rooms_to_clean == 0: return self.cleaning_time_per_room*self._room_amount
        n = min(self.room_amount, int(rooms_to_clean))
        return float(n) * self.cleaning_time_per_room

    def is_single(self) -> bool:
        return False