# hotel_repository.py
from pathlib import Path

from hotel import Hotel
from multapartment import Multapartment
from singlapartment import Singlapartment


class HotelRepository:
    def __init__(self, file_path: str | Path):
        self.file = Path(file_path)

    def read_from_file(self) -> Hotel:
        hotel = Hotel()
        if not self.file.exists():
            return hotel
        with self.file.open("r", encoding="utf-8") as f:
            for line in f:
                line = line.strip()
                if not line or line.startswith("#"):
                    continue
                parts = line.split()
                # expected: number time [rooms]
                if len(parts) < 2:
                    continue
                num = int(parts[0])
                time = float(parts[1])
                rooms = int(parts[2]) if len(parts) >= 3 else 0
                if rooms:
                    hotel.add_apartment(Multapartment(num, time, rooms))
                else:
                    hotel.add_apartment(Singlapartment(num, time))
        return hotel

    def rewrite_file(self, hotel: Hotel) -> None:
        with self.file.open("w", encoding="utf-8") as f:
            for apt in hotel.output_apartments():
                if apt.is_single():
                    f.write(f"{apt.number} {apt.cleaning_time_per_room}\n")
                else:
                    f.write(f"{apt.number} {apt.get_time()} {apt.room_amount}\n")
