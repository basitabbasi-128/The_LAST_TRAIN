#include "level.h"
#include "util.h"
#include <fstream>
#include <cstring>
#include<iostream>
#include <cstdlib> //convert '111' into int 111
using namespace std;
const char* getEntityName(char entitySymbol){
if (entitySymbol=='<'){return "MASTER_KEY";}
else if(entitySymbol==' '){return "None";}
else if(entitySymbol==';'){return "CONTROL_PANEL";}
else if(entitySymbol=='('){return "LIFT_PASS";}
else if(entitySymbol=='!'){return "PASSENGER";}
else if(entitySymbol=='%'){return "MEDICAL_KIT";}
else if(entitySymbol=='$'){return "EMERGENCY_CARD";}
else if(entitySymbol=='2'){return "CLUE_2";}
else if(entitySymbol==')'){return "ENERGY_PACK";}
else if(entitySymbol==ENT_EMERGENCY_TOOLKIT){return "EMERGENCY_TOOLKIT";}
else if(entitySymbol=='4'){return "CLUE_4";}
else if(entitySymbol==ENT_FUSE){return "FUSE";}
else if(entitySymbol==ENT_CAT){return "CAT";}
else if(entitySymbol=='7'){return "CLUE_7";}
else if(entitySymbol=='@'){return "CAT_CARRIER";}
else if(entitySymbol=='&'){return "OBSERVATION_TOKEN";}
else if(entitySymbol=='^'){return "CABINET_TRAIN_KEY";}
else{return "unknownentity";}}

bool validateStartingRoom(int startFloor, int startRoom,const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1]){
(void)horizontalConn;
if (startFloor < 1 || startFloor > NUM_FLOORS ||startRoom < 1 || startRoom > ROOMS_PER_FLOOR) {return false;}
else{return true;}}


bool loadInitialState(const char* filename,int& playerFloor, int& playerRoom,int& energy, int& time, int& score,char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft){
    (void)playerFloor;
    (void)playerRoom;
    ifstream file(filename);
    if (!file.is_open()) {return false;}
    inventoryCount=0;
    emergencyTripsLeft=0;
    for (int i = 0; i < MAX_INVENTORY_CAPACITY; i++) {inventory[i] = ' ';}
    for (int i = 0; i < NUM_OBJECTIVES; i++) {objectives[i] = false;}
    string line;
    while(file.getline(file,line)){
    char* colon = strchr(line, ':');
    if(colon !=nullptr){
    *colon='\0';
    char* value=colon+1;
    if (stringEquals(line,"INITIAL_ENERGY")){energy=atoi(value);}
    else if (stringEquals(line,"INITIAL_TIME")){time=atoi(value);}
    else if (stringEquals(line,"INITIAL_SCORE")){score=atoi(value);}
    else if (stringEquals(line,"INITIAL_INVENTORY")){if(stringEquals(value,"NONE"))inventoryCount=0;}
    else if (stringEquals(line,"PASSENGER_RESCUED")){objectives[OBJ_PASSENGER_RESCUED] = stringEquals(value,"YES");}
    else if (stringEquals(line,"CAT_RESCUED")){objectives[OBJ_CAT_SECURED] = stringEquals(value,"YES");}
    else if (stringEquals(line, "CABINET_UNLOCKED")){objectives[OBJ_CABINET_UNLOCKED] = stringEquals(value,"YES");}
    else if (stringEquals(line, "TRAIN_KEY_COLLECTED")){objectives[OBJ_TRAIN_KEY] = stringEquals(value,"YES");}
    else if (stringEquals(line, "FUSE_INSTALLED")){objectives[OBJ_FUSE_INSTALLED] = stringEquals(value,"YES");}
    else if (stringEquals(line, "LIFT_PASS_COLLECTED")) {objectives[OBJ_LIFT_PASS] = stringEquals(value,"YES");}
    else if (stringEquals(line, "TRAIN_PREPARED")){objectives[OBJ_TRAIN_PREPARED] = stringEquals(value,"YES");}}}
    return true;}
