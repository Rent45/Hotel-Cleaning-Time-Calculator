# Hotel Cleaning Time Calculator

**Two implementations included:** C++ and Python.
This repository contains a small university project that computes cleaning time for apartments (single-room and multi-room) in a hotel, provides a small interactive menu to manage the hotel, and reads/writes apartment data from a plain text file.

---

## Table of contents

* Features
* File / input format
* C++ version — Requirements
* Python version — Requirements
* Example (sample data & interaction)
* Design & OOP mapping (where the four OOP principles are used)
* Common problems & troubleshooting

---

## Features

* Represent apartments as:

  * **Single-room apartment** (single cleaning time).
  * **Multi-room apartment** (per-room cleaning time + number of rooms).
* Interactive text menu:

  * compute cleaning time for selected apartments,
  * manage (add / delete) apartments,
  * list apartments,
  * exit the program.
* Persists apartment data using a plain text file (`rooms.txt`).
* Two language versions (C++ and Python) so you can compare idioms and OOP usage.

---

You can keep both implementations in the same Git repo (use `cpp/` and `python_project/` folders) or split them into different repos — whatever fits your workflow.

---

## File / input format

Place the apartment data file next to the executable or the script. Each line represents one apartment. Simple, space-separated values:

```
<apartment_number> <cleaning_time_per_room_or_total> [room_count]
```

Examples:

```
1 15 2    # apartment 1: per-room cleaning time 15 minutes, 2 rooms (multi-room)
2 39 3    # apartment 2: per-room cleaning time 39 minutes, 3 rooms (multi-room)
3 38      # apartment 3: single-room, total cleaning time 38 minutes
```

Rules the code assumes:

* If `room_count` is present and > 0 → multi-room apartment (cleaning_time is *per-room* time).
* If `room_count` is missing → single-room apartment (cleaning_time is total cleaning time).

---

## C++ version —  Requirements

* C++20-capable compiler (GCC/Clang/MSVC).
* CMake 3.16+.

## Python version —  Requirements

* Python 3.8+ (3.10/3.11 recommended)
* No external packages required (stdlib only)

## Example (sample data & interaction)

**Sample `rooms.txt`:**

```
1 15 2
2 39 3
3 38
4 37
5 36 5
```

**Expected behavior (menu-driven):**

* View all apartments
* Choose apartments to clean and optionally specify how many rooms (for multi-room apartments)
* Program prints the selected apartments and the cleaning time formatted as hours and minutes

Example textual output:

```
Tasks to clean (number of rooms cannot go beyond max):
  Apartment 1: 10 room(s)
  Apartment 2: all rooms
  Apartment 3: single-room

The cleaning will take 1 hours and 8 minutes
```

---

## Design & OOP mapping — where the four OOP principles are used

Below are the most prominent cases (applies to both C++ and Python versions):

### 1) Encapsulation

* Apartment internals (`number`, cleaning-time fields) are private (C++) or protected-by-convention (`_field`) in Python. Access is through public methods (getters and behavior methods).

### 2) Abstraction

* `Apartment` defines an abstract interface (pure virtual functions in C++; `ABC` / `@abstractmethod` in Python). The rest of the program manipulates `Apartment` objects through that interface, not by their concrete details.

### 3) Inheritance

* `SingleApartment` and `MultiApartment` inherit from `Apartment` and implement/override the required interface.

### 4) Polymorphism

* The hotel class stores base-class references/pointers (`Apartment*` / `unique_ptr<Apartment>` in C++ or references in Python) and calls virtual methods; actual runtime dispatch executes derived-class code.

---

## Common problems & troubleshooting

### File not found / relative path issues

* Many IDEs run executables with the working directory set to the `build/` folder (CMake) or the project root. If your `ifstream` or `open()` fails, check the working directory in the run configuration, or use an absolute path during testing.

### `bad_function_call` (menu)

* Means a callable stored in a `std::function` (C++) or `Callable` (Python) was empty. Make sure each menu entry gets a valid function object when building the menu.

### Abstract-class / `make_unique` errors (C++)

* If you try to construct a derived class but it still has not implemented all pure virtual functions, the compiler will error. Implement all required virtual methods in derived classes.
