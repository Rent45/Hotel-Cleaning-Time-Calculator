#ifndef SINGLAPARTMENT_H
#define SINGLAPARTMENT_H
#include "apartment.h"

class Singlapartment: public Apartment{
public:
  explicit Singlapartment(const int Number = 0, const double time = 0):Apartment(Number, time){}
  double getTime() const override {return this->room_time;}
  bool isSingle() const override {return true;}
  double getTime(int) const override { return this->room_time; }
  int getRoomAmount() const override { return 1; }
};

#endif //SINGLAPARTMENT_H
