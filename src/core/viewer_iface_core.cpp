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


void renderDashboard(int playerFloor, int playerRoom, int energy, int time, int score,const char inventory[MAX_INVENTORY_CAPACITY],int inventoryCount, int emergencyTripsLeft) {
    cout << "\n   STATUS ";
    cout << "Location: Floor " << playerFloor<< ", Room " << playerRoom << endl;
    cout << "Energy: " << energy<< "   Time: " << time<< "   Score: " << score << endl;
    cout << "Inventory: ";
    if (inventoryCount == 0) {cout << "Empty";}
    else {for (int i = 0; i < inventoryCount; i++) {cout << getEntityName(inventory[i]) << " ";}}
    cout << "\nEmergency trips left: " << emergencyTripsLeft << endl;}



