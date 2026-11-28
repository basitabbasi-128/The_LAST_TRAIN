#include "viewer_iface.h"
#include "util.h"
#include <iostream>
#include "level.h"
using namespace std;

void renderAsciiBuilding(int playerFloor, int playerRoom) {
    cout << "    BUILDING MAP      ";
for (int floor = NUM_FLOORS; floor >= 1; floor--) {
    cout << "Floor " << floor << ": ";
    for (int room = 1; room <= ROOMS_PER_FLOOR; room++) {
        cout << "[R" << room;
        if (floor == playerFloor && room == playerRoom) {cout << ":P";}
        cout << "] ";}
cout << endl;}}