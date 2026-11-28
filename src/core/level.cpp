#include "level.h"
#include "util.h"
#include <fstream>
#include <cstring>
#include<iostream>
#include <cstdlib> //convert '111' into int 111
using namespace std;

bool validateStartingRoom(int startFloor, int startRoom,const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1]){
(void)horizontalConn;
if (startFloor < 1 || startFloor > NUM_FLOORS ||startRoom < 1 || startRoom > ROOMS_PER_FLOOR) {return false;}
else{return true;}}

const char* getEntityName(char entitySymbol){
if (entitySymbol=='<'){return "MASTER_KEY";}
else if(entitySymbol==' '){return "None";}
else if(entitySymbol==')'){return "ENERGY_PACK";}
else if(entitySymbol==ENT_EMERGENCY_TOOLKIT){return "EMERGENCY_TOOLKIT";}
else if(entitySymbol=='4'){return "CLUE_4";}
else if(entitySymbol==ENT_FUSE){return "FUSE";}

else if(entitySymbol=='@'){return "CAT_CARRIER";}
else if(entitySymbol=='&'){return "OBSERVATION_TOKEN";}
else if(entitySymbol=='^'){return "CABINET_TRAIN_KEY";}
else{return "unknownentity";}}
