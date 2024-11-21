#include "./functions.h"

Age::Age(int age){
  this->age = age;
}

bool Age::valid_age() {
  if (this->age >= 21) {
    return true;
  }
  return false;
}

int Age::get_age(){
  return 0;
}