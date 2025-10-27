# menu.py
from typing import Callable, Dict, Tuple, Any

class Menu:
    """
    Menu maps keys (str) to (description, action).
    An action is a callable with no args. It can return bool:
      - If returns False -> menu stops.
      - If returns True or None -> menu continues.
    """
    def __init__(self, title: str = "=== The Menu ==="):
        self.title = title
        self.items: Dict[str, Tuple[str, Callable[[], Any]]] = {} #a callable that takes no parameters and returns anything.

    def add(self, key: str, description: str, action: Callable[[], Any]) -> None:
        self.items[key] = (description, action)

    def show(self) -> None:
        print()
        print(self.title)
        #self.items → the dictionary that stores your menu options.
        #.items() → the dictionary method that gives you the list of(key, value) pairs from that dictionary.
        for k, (desc, _) in self.items.items():
            print(f"{k}. {desc}")

    def run(self) -> None:
        while True:
            self.show()
            choice = input("\nEnter option (key): ").strip()
            if choice == "":
                continue
            entry = self.items.get(choice)
            if entry is None:
                print("Unknown option. Try again.")
                continue
            desc, action = entry
            if not action:
                print(f"Option {choice} has no action.")
                continue
            try:
                res = action()
            except Exception as e:
                print("Action threw exception:", e)
                # keep loop alive
                continue
            # interpret return value
            if isinstance(res, bool) and res is False:
                break
