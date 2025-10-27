#ifndef APARTMENT_H
#define APARTMENT_H

class Apartment {
  int number;
protected:
  double room_time;
public:
  explicit Apartment(const int Number = 0, const double time = 0):number(Number),room_time(time){}
  int getNumber() const {return number;}
  virtual double getTime() const = 0;
  virtual double getTime(int number_rooms) const = 0;
  virtual bool isSingle() const = 0;
  virtual int getRoomAmount() const = 0;
  virtual ~Apartment() = default;
};

#endif //APARTMENT_H
