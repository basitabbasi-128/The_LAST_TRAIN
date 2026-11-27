#include "switches.h"
#include "util.h"

bool canUseLift1(int fromFloor, int toFloor) {
    if ((fromFloor == 1 && toFloor == 2) ||(fromFloor == 2 && toFloor == 1)) {return true;}
    else {return false;}}

bool canUseLift2(int fromFloor, int toFloor,bool lift2Operational, int emergencyTripsLeft) {
    if (fromFloor != toFloor &&(fromFloor == 2 || fromFloor == 4 || fromFloor == 5) &&(toFloor == 2 || toFloor == 4 || toFloor == 5)) {
        if (lift2Operational == true || emergencyTripsLeft > 0) {return true;}
        else{return false;}}
    else{return false;}}

bool unlockFloor3Door(const char inventory[MAX_INVENTORY_CAPACITY],int inventoryCount) {
    for (int i=0;i<inventoryCount;i++){if (inventory[i] == ENT_MASTER_KEY) {return true;}}
    return false;}