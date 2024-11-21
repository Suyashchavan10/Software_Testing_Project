// bool valid_age(int age) {
//   if (age >= 21) {
//     return true;
//   }
//   return false;
// }
#include "./functions.h"

int main() {
  // Age age1(25);
  // bool test1 = age1.get_age() == 10;
  // if (!test1) {
  //   /// test failed
  //   return 1;
  // }

  Age age1(25);
  bool test1 = age1.valid_age() == true;
  if (!test1) {
    /// test failed
    return 1;
  }

  // bool test2 = valid_age(20) == false;
  // if (!test2) {
  //   /// test failed
  //   return 1;
  // }

  // bool test3 = valid_age(21) == true;
  // if (!test3) {
  //    /// test failed
  //    return 1;
  // }

  /// success
  return 0;
}