#include "menu.h"
#include <iostream>
#include <cmath>
#include <sstream>

#include "hotel.h"
#include "hotelrepository.h"
#include "multapartment.h"
#include "singlapartment.h"

string format_minutes(const double minutes) {
    ostringstream f;
    f << floor(minutes / 60) << " hours and " << fmod(minutes, 60) << " minutes";
    return f.str();
}

void cleanSomeRooms(const Hotel& hotel) {
    cout << "Select the number of apartments to clean: ";
    int number_of_apartments;
    if (!(cin >> number_of_apartments) || number_of_apartments <= 0) {
        cout << "Invalid number." << endl;
        cin.clear();
        cin.ignore();
        return;
    }

    vector<int> number_vector;
    for (int i = 0; i < number_of_apartments; i++) {
        cout << "Enter the apartment number to clean: ";
        int apt_number;
        if (!(cin >> apt_number)) {
            cout << "Invalid input. Please enter an integer apartment number." << endl;
            cin.clear();
            cin.ignore();
            --i; // repeat this iteration
            continue;
        }

        const Apartment* apt = hotel.findApartment(apt_number);
        if (!apt) {
            cout << "Apartment " << apt_number << " not found. Try again." << endl;
            --i; // repeat this iteration
            continue;
        }

        number_vector.push_back(apt_number);

        if (!apt->isSingle()) {
            cout << "Enter the number of rooms in this apartment to clean (0 = all): ";
            int roomsToClean;
            if (!(cin >> roomsToClean) || roomsToClean < 0) {
                cout << "Invalid number of rooms." << endl;
                cin.clear();
                cin.ignore();
                number_vector.pop_back(); // remove apt_number so we redo this iteration
                --i;
                continue;
            }
            number_vector.push_back(roomsToClean);
        }
    }

    // Print user-entered tasks summary before computing time
    cout << endl << "Tasks to clean (number of rooms cannot go beyond max):" << endl;
    for (size_t idx = 0; idx < number_vector.size(); idx++) {
        const int apt = number_vector[idx];
        const Apartment* aptPtr = hotel.findApartment(apt);
        if (!aptPtr) {
            cout << "  Apartment " << apt << "  (not found)" << endl;
            continue;
        }
        if (!aptPtr->isSingle()) {
            if (idx + 1 < number_vector.size()) {
                int rooms = 0;
                rooms = number_vector[++idx]; // consume rooms count
                if (rooms == 0)
                    cout << "  Apartment " << apt << ": all rooms" << endl;
                else
                    cout << "  Apartment " << apt << ": " << rooms << " room(s)" << endl;
            } else {
                // missing rooms entry => assume all
                cout << "  Apartment " << apt << ": all rooms" << endl;
            }
        } else {
            cout << "  Apartment " << apt << ": single-room" << endl;
        }
    }

    const double minutes = hotel.countTime(number_vector);
    cout << endl << "The cleaning will take " << format_minutes(minutes) << endl;
}

void addSingle(Hotel& hotel) {
    cout << "Enter the number of the apartment to add (if it exists, it will be replaced): ";
    int number;
    if (!(cin >> number)) {cout << "Invalid input. Please try again" << endl; return;};
    cout << "Enter the cleaning time of the apartment: ";
    double time;
    if (!(cin >> time)) {cout << "Invalid input. Please try again" << endl; return;};
    hotel.addApartment(make_unique<Singlapartment>(number, time));
    cout << "Single-room apartment number " << number << " added." << endl;
}

void addMulti(Hotel& hotel) {
    cout << "Enter the number of the apartment to add (if it exists, it will be replaced): ";
    int number;
    if (!(cin >> number)) {cout << "Invalid input. Please try again" << endl; return;};
    cout << "Enter the cleaning time of every room in the apartment (one number): ";
    double time;
    if (!(cin >> time)) {cout << "Invalid input. Please try again" << endl; return;};
    cout << "Enter the number of rooms in the apartment: ";
    int amount;
    if (!(cin >> amount)) {cout << "Invalid input. Please try again" << endl; return;};
    hotel.addApartment(make_unique<Multapartment>(number, time, amount));
    cout << "Multiple-room apartment number " << number << " added." << endl;
}

void deleteApartment(Hotel& hotel) {
    cout << "Enter the number of the apartment to delete: ";
    int number;
    if (!(cin >> number)) {cout << "Invalid input. Please try again" << endl; return;};
    if (hotel.removeApartment(number)) {
        cout << "Apartment " << number << " removed." << endl;
    } else {
        cout << "Apartment " << number << " not found." << endl;
    }
}

bool doQuit() {
    // cout << "Goodbye!" << endl;
    return false; // tell menu to stop
}

void manageApartments(Hotel& hotel, const HotelRepository& hotel_repository) {
    Menu manage_options("How do you want to edit the hotel?");
    manage_options.add("s", "Add a single-room apartment", [&hotel]() { addSingle(hotel); });
    manage_options.add("m", "Add a multiple-room apartment", [&hotel]() { addMulti(hotel); });
    manage_options.add("d", "Delete an apartment", [&hotel]() { deleteApartment(hotel); });
    manage_options.add("0", "Return to main menu", function(doQuit));
    manage_options.run();
    hotel_repository.rewriteFile(hotel);
}

void outputAllApartments(const Hotel& hotel) {
    cout << "Here are all of the apartments:" << endl;
    for(auto i : hotel.outputApartments()) {
        if (i->isSingle()) {
            cout << "Apartment number: " << i->getNumber() << ", cleaning time: " << i->getTime() << endl;
        } else {
            cout << "Apartment number: " << i->getNumber() << ", cleaning time of a room: " << format_minutes(i->getTime()) << ", number of rooms: " << i->getRoomAmount() << endl;
        }
    }
}

int main() {
    Menu m("The Menu (type the key and press Enter)");
    const HotelRepository repository("../rooms.txt");
    Hotel hotel = repository.readFromFile();

    // add boolean-returning function
    m.add("1", "Clean some rooms", [&hotel]() { cleanSomeRooms(hotel); });

    // add void function (converted by overload)
    m.add("2", "Manage apartments", [&hotel, &repository]() {manageApartments(hotel, repository); });

    m.add("3", "Output the apartments", [&hotel]() { outputAllApartments(hotel); });

    // add quit action
    m.add("0", "Exit the program", function(doQuit));

    // optionally show once and run interactive loop
    m.run();

    return 0;
}
