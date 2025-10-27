#ifndef MULTAPARTMENT_H
#define MULTAPARTMENT_H
#include "apartment.h"
#include <cmath>

class Multapartment: public Apartment {
  int room_amount;
public:
  Multapartment(const int Number = 0, const double time = 0, const int rooms = 0):Apartment(Number,time), room_amount(rooms) {}
  double getTime(const int number_rooms) const override {if(number_rooms<=0) return room_amount*room_time; return fmin(room_amount, number_rooms)*room_time;}
  double getTime() const override {return room_time;}
  int getRoomAmount() const override {return room_amount;}
  bool isSingle() const override {return false;}
};

#endif //MULTAPARTMENT_H
