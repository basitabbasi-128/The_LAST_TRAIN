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


void renderRoomDetails(int floor, int room,const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],int entityCount) {
    cout << "\n--- ROOM DETAILS ---\n";
    cout << "Floor " << floor << ", Room " << room << endl;
    if (entityCount == 0) {cout << "No items in this room.\n";
    return;}
    cout << "Items: ";
    for (int i = 0; i < entityCount; i++) {cout << getEntityName(roomEntities[floor - 1][room - 1][i]) << " ";}
    cout << endl;}


    void renderObjectivesChecklist(const bool objectives[NUM_OBJECTIVES]) {
    cout << "\n--- OBJECTIVES ---\n";
    cout << (objectives[OBJ_MASTER_KEY] ? "[X] " : "[ ] ") << "Master Key\n";
    cout << (objectives[OBJ_CLUE_4] ? "[X] " : "[ ] ") << "Clue 4\n";
    cout << (objectives[OBJ_CLUE_2] ? "[X] " : "[ ] ") << "Clue 2\n";
    cout << (objectives[OBJ_CLUE_7] ? "[X] " : "[ ] ") << "Clue 7\n";
    cout << (objectives[OBJ_CABINET_UNLOCKED] ? "[X] " : "[ ] ") << "Cabinet unlocked\n";
    cout << (objectives[OBJ_TRAIN_KEY] ? "[X] " : "[ ] ") << "Train key\n";
    cout << (objectives[OBJ_FUSE_COLLECTED] ? "[X] " : "[ ] ") << "Fuse collected\n";
    cout << (objectives[OBJ_FUSE_INSTALLED] ? "[X] " : "[ ] ") << "Fuse installed\n";
    cout << (objectives[OBJ_LIFT_PASS] ? "[X] " : "[ ] ") << "Lift pass\n";
    cout << (objectives[OBJ_LIFT2_ACTIVE] ? "[X] " : "[ ] ") << "Lift 2 activated\n";
    cout << (objectives[OBJ_PASSENGER_RESCUED] ? "[X] " : "[ ] ") << "Passenger rescued\n";
    cout << (objectives[OBJ_CAT_CARRIER] ? "[X] " : "[ ] ") << "Cat carrier\n";
    cout << (objectives[OBJ_CAT_SECURED] ? "[X] " : "[ ] ") << "Cat secured\n";
    cout << (objectives[OBJ_TRAIN_PREPARED] ? "[X] " : "[ ] ") << "Train prepared\n";
    cout << (objectives[OBJ_MISSION_WON] ? "[X] " : "[ ] ") << "Mission won\n";
    cout << (objectives[OBJ_MISSION_FAILED] ? "[X] " : "[ ] ") << "Mission failed\n";}


