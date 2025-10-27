#include "apartment.h"
#include "hotel.h"

#include <cmath>
#include <math.h>
#include <vector>


void Hotel::addApartment(unique_ptr<Apartment> apartment) {
  if (!apartment) return;
  removeApartment(apartment->getNumber());
  rooms.push_back(move(apartment));
}

bool Hotel::removeApartment(const int apartment) {
  for (auto it = rooms.begin(); it != rooms.end(); ) {
    if (*it && (*it)->getNumber() == apartment) {
      rooms.erase(it);
      return true;
    }
    ++it;
  }
  return false;
}


Apartment* Hotel::findApartment(const int number) const {
  for (auto& it : rooms) {
    if (it && it->getNumber() == number) return it.get();
  }
  return nullptr;
}

double Hotel::countTime(const vector<int>& apartments) const {
  double sum = 0;
  for (size_t i = 0; i < apartments.size(); ) {
    Apartment* ap = findApartment(apartments[i]);
    if (!ap) {
      // skip unknown apartment number — or handle error
      ++i;
    } else if (ap->isSingle()) {
      sum += ap->getTime();
      ++i;
    } else {
      if (i + 1 >= apartments.size()) break; // malformed input
      sum += ap->getTime(apartments[i+1]);
      i += 2;
    }
  }
  return sum;
}

vector<Apartment*> Hotel::outputApartments() const {
  vector<Apartment*> out;
  out.reserve(rooms.size());
  for (const auto& it : rooms) if (it) out.push_back(it.get());
  return out;
}