#ifndef HOTELREPOSITORY_H
#define HOTELREPOSITORY_H
#include <string>
#include <utility>
#include "hotel.h"
using namespace std;

class HotelRepository {
  string file_name;
public:
  explicit HotelRepository(string  name):file_name(move(name)){};
  Hotel readFromFile() const;
  void rewriteFile(const Hotel& hotel) const;
};

#endif //HOTELREPOSITORY_H
