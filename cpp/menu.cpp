#include "menu.h"
#include <iostream>

Menu::Menu(string title): title(move(title)){}

void Menu::add(const string& key, const string& description, function<bool()> action) {
    items[key] = make_pair(description, move(action));
}

void Menu::add(const string& key, const string& description, function<void()> action) {
    // Wrap void() -> bool() returning true so the menu keeps running by default
    function<bool()> wrapper = [action = move(action)]() mutable -> bool {
        action();
        return true;
    };
    add(key, description, move(wrapper));
}

void Menu::show() const {
    cout << endl << "=== " << title << " ===" << endl;
    for (const auto& it : items) {
        cout << it.first << ". " << it.second.first << endl;
    }
    cout << endl;
}

bool Menu::execute(const string& key) {
    const auto it = items.find(key);
    if (it == items.end()) {
        cout << "Unknown option: " << key << endl;
        return true; // continue by default on unknown key
    }
    // call action and return its boolean (true -> continue, false -> stop)
    try {
        return it->second.second();
    } catch (const exception& ex) {
        cerr << "Action threw exception: " << ex.what() << endl;
        return true;
    } catch (...) {
        cerr << "Action threw unknown exception" << endl;
        return true;
    }
}

void Menu::run() {
    string choice;
    bool keepGoing = true;
    while (keepGoing) {
        show();
        cout << "Enter option (key): ";
        if (!getline(cin >> ws, choice)) {
            cout << endl << "Input closed. Exiting." << endl;
            break;
        }
        // trim whitespace from both ends (simple)
        const auto first = choice.find_first_not_of(" \t\r\n"); //a space (' '), tab ('\t'), carriage return ('\r'), or newline ('\n')
        if (first == string::npos) {
            // empty input -> repeat
            continue;
        }
        auto last = choice.find_last_not_of(" \t\r\n");
        string key = choice.substr(first, last - first + 1);

        keepGoing = execute(key);
    }
}
