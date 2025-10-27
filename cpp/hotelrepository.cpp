#include "hotelrepository.h"
#include "multapartment.h"
#include "singlapartment.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Hotel HotelRepository::readFromFile() const {
    Hotel hotel;
    ifstream fin(file_name);
    if (!fin) {
        cerr << "Unable to open file for reading: " << file_name << endl;
        return hotel;
    }

    string line;
    while (getline(fin, line)) {
        // skip empty / whitespace-only lines
        if (line.find_first_not_of(" \t\r\n") == string::npos) continue;

        istringstream iss(line);
        int room;
        double time;
        int amount;

        if (!(iss >> room >> time)) {
            // malformed line: ignore or log
            cerr << "Skipping malformed line: " << line << endl;
            continue;
        }

        if (iss >> amount) {
            // line had three tokens -> multapartment
            hotel.addApartment(make_unique<Multapartment>(room, time, amount));
        } else {
            // only two tokens -> single-room apartment
            hotel.addApartment(make_unique<Singlapartment>(room, time));
        }
    }

    return hotel;
}


void HotelRepository::rewriteFile(const Hotel& hotel) const {
    ofstream ofs(file_name, ios::trunc);
    if (!ofs) {
        cerr << "Unable to open file for writing: " << file_name << endl;
        return;
    }

    for (Apartment* room : hotel.outputApartments()) {
        ofs << room->getNumber() << " " << room->getTime();
        if (!room->isSingle()) {
            // getRoomAmount exists in base now
            ofs << " " << room->getRoomAmount();
        }
        ofs << endl;
    }
}
