# main.py
from menu import Menu
from hotel_repository import HotelRepository
from hotel import Hotel

# helpers
def format_minutes(minutes: float) -> str:
    hours = int(minutes // 60)
    mins = int(minutes % 60)
    return f"{hours} hours and {mins} minutes"

def clean_some_rooms(hotel):
    try:
        n = int(input("Select the number of apartments to clean: "))
        if n <= 0:
            print("Invalid number.")
            return
    except ValueError:
        print("Invalid number.")
        return

    tasks = []
    for i in range(n):
        try:
            apt_num = int(input("Enter the apartment number to clean: "))
        except ValueError:
            print("Invalid apartment number, try again.")
            continue

        apt = hotel.find_apartment(apt_num)
        if apt is None:
            print(f"Apartment {apt_num} not found. Try again.")
            continue

        if not apt.is_single():
            # ask number of rooms; empty or 0 -> treat as "all"
            raw = input("Enter the number of rooms in this apartment to clean (0 = all): ").strip()
            if raw == "":
                rooms = None
            else:
                try:
                    rooms = int(raw)
                    if rooms <= 0:
                        # convention: 0 or negative => all rooms
                        rooms = 0
                except ValueError:
                    print("Invalid rooms number; treating as 'all'.")
                    rooms = None
            tasks.append((apt_num, rooms))
        else:
            tasks.append((apt_num, None))

    if not tasks:
        print("No valid tasks entered.")
        return

    # Print summary of tasks before computing time
    print("\nTasks to clean (number of rooms cannot go beyond max):")
    for apt_num, rooms in tasks:
        apt = hotel.find_apartment(apt_num)
        if apt is None:
            print(f"  Apartment {apt_num}: (not found)")
            continue
        if apt.is_single():
            print(f"  Apartment {apt_num}: single-room")
        else:
            if rooms is None:
                # try to show total room count if available
                try:
                    total_rooms = apt.get_room_amount()
                    print(f"  Apartment {apt_num}: all rooms ({total_rooms})")
                except Exception:
                    print(f"  Apartment {apt_num}: all rooms")
            else:
                print(f"  Apartment {apt_num}: {rooms} room(s)")

    minutes = hotel.count_time(tasks)
    print("\nThe cleaning will take", format_minutes(minutes))

def add_single(hotel: Hotel):
    try:
        num = int(input("Apartment number (if it exists, it will be replaced): "))
        time = float(input("Cleaning time (minutes): "))
    except ValueError:
        print("Invalid input.")
        return
    from singlapartment import Singlapartment
    hotel.add_apartment(Singlapartment(num, time))
    print("Added single apartment", num)

def add_multi(hotel: Hotel):
    try:
        num = int(input("Apartment number (if it exists, it will be replaced): "))
        time = float(input("Cleaning time per room (minutes): "))
        rooms = int(input("Number of rooms total: "))
    except ValueError:
        print("Invalid input.")
        return
    from multapartment import Multapartment
    hotel.add_apartment(Multapartment(num, time, rooms))
    print("Added multi apartment", num)

def delete_apartment(hotel: Hotel):
    try:
        num = int(input("Apartment number to delete: "))
    except ValueError:
        print("Invalid input.")
        return
    ok = hotel.remove_apartment(num)
    print("Deleted" if ok else "Not found")

def output_all_apartments(hotel: Hotel):
    print("Here are all of the apartments:")
    for apt in hotel.output_apartments():
        if apt.is_single():
            print(f"Apartment {apt.number}: single, cleaning time: {format_minutes(apt.get_time())}")
        else:
            try:
                rooms = apt.room_amount
            except ValueError:
                rooms = "?"
            print(f"Apartment {apt.number}: multi, time/room: {format_minutes(apt.get_time_with_rooms(1))}, rooms: {rooms}")

def main():
    repo = HotelRepository("rooms.txt")
    hotel = repo.read_from_file()

    menu = Menu("=== The Menu (type the key and press Enter) ===")
    menu.add("0", "Exit the program", lambda: False)
    menu.add("1", "Clean some rooms", lambda: clean_some_rooms(hotel))
    menu.add("2", "Manage apartments", lambda: manage_apartments(hotel, repo))
    menu.add("3", "Output the apartments", lambda: output_all_apartments(hotel))

    menu.run()
    print("Goodbye!")

def manage_apartments(hotel: Hotel, repository: HotelRepository):
    m = Menu("How do you want to edit the hotel?")
    m.add("S", "Add a single-room apartment", lambda: add_single(hotel))
    m.add("M", "Add a multiple-room apartment", lambda: add_multi(hotel))
    m.add("D", "Delete an apartment", lambda: delete_apartment(hotel))
    m.add("B", "Back to main menu", lambda: False)
    m.run()
    repository.rewrite_file(hotel)

if __name__ == "__main__":
    main()
