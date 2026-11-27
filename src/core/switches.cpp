#include "switches.h"
#include "util.h"

bool canUseLift1(int fromFloor, int toFloor) {
    if ((fromFloor == 1 && toFloor == 2) ||(fromFloor == 2 && toFloor == 1)) {return true;}
    else {return false;}}
