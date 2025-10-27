from apartment import Apartment

class Singlapartment(Apartment):
    def get_time(self) -> float:
        return float(self.cleaning_time_per_room)

    def get_time_with_rooms(self, rooms_to_clean: int) -> float:
        # for single-room apartment the requested rooms argument is ignored
        return self.get_time()

    def is_single(self) -> bool:
        return True
