#ifndef HOTEL_H
#define HOTEL_H
#include "apartment.h"
#include "vector"
#include <memory>
using namespace std;

class Hotel {
  vector<unique_ptr<Apartment>> rooms;
public:
  Hotel()=default;
  ~Hotel()=default;
  void addApartment(unique_ptr<Apartment> apartment);
  bool removeApartment(int apartment);
  Apartment* findApartment(int number) const;
  double countTime(const vector<int>& apartments) const;
  vector<Apartment*> outputApartments() const;

  // disable copying (unique_ptr are non-copyable)
  Hotel(const Hotel&) = delete;
  Hotel& operator=(const Hotel&) = delete;

  // allow moving
  Hotel(Hotel&&) noexcept = default;
  Hotel& operator=(Hotel&&) noexcept = default;
};

#endif //HOTEL_H
