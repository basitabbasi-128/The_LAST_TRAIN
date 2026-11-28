#include "level.h"
#include "util.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
using namespace std;

const char* getEntityName(char entitySymbol) {
    if (entitySymbol == '<') return "MASTER_KEY";
    else if (entitySymbol == ' ') return "None";
    else if (entitySymbol == ';') return "CONTROL_PANEL";
    else if (entitySymbol == '(') return "LIFT_PASS";
    else if (entitySymbol == '!') return "PASSENGER";
    else if (entitySymbol == '%') return "MEDICAL_KIT";
    else if (entitySymbol == '$') return "EMERGENCY_CARD";
    else if (entitySymbol == '2') return "CLUE_2";
    else if (entitySymbol == ')') return "ENERGY_PACK";
    else if (entitySymbol == ENT_EMERGENCY_TOOLKIT) return "EMERGENCY_TOOLKIT";
    else if (entitySymbol == '4') return "CLUE_4";
    else if (entitySymbol == ENT_FUSE) return "FUSE";
    else if (entitySymbol == ENT_CAT) return "CAT";
    else if (entitySymbol == '7') return "CLUE_7";
    else if (entitySymbol == '@') return "CAT_CARRIER";
    else if (entitySymbol == '&') return "OBSERVATION_TOKEN";
    else if (entitySymbol == '^') return "CABINET_TRAIN_KEY";
    else return "unknownentity";}

bool validateStartingRoom(int startFloor,int startRoom,const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1]) {(void)horizontalConn;
    if (startFloor < 1 || startFloor > NUM_FLOORS ||startRoom < 1 || startRoom > ROOMS_PER_FLOOR) {return false;}
    return true;}

bool loadInitialState(const char* filename,int& playerFloor,int& playerRoom,int& energy,int& time,int& score,char inventory[MAX_INVENTORY_CAPACITY],int& inventoryCount,bool objectives[NUM_OBJECTIVES],int& emergencyTripsLeft) {
    (void)playerFloor;
    (void)playerRoom;
    ifstream file(filename);
    if (!file.is_open()) {return false;}
    inventoryCount = 0;
    emergencyTripsLeft = 0;
    for (int i = 0; i < MAX_INVENTORY_CAPACITY; i++) {inventory[i] = ENT_NONE;}
    for (int i = 0; i < NUM_OBJECTIVES; i++) {objectives[i] = false;}
    char line[MAX_LINE_LEN];
    while (file.getline(line, MAX_LINE_LEN)) {
        char* colon = strchr(line, ':');
        if (colon != nullptr) {
            *colon = '\0';
            char* value = colon + 1;
            if (stringEquals(line, "INITIAL_ENERGY")) {energy = atoi(value);}
            else if (stringEquals(line, "INITIAL_TIME")) {time = atoi(value);}
            else if (stringEquals(line, "INITIAL_SCORE")) {score = atoi(value);}
            else if (stringEquals(line, "INITIAL_INVENTORY")) {if (stringEquals(value, "NONE")) {inventoryCount = 0;}}
            else if (stringEquals(line, "PASSENGER_RESCUED")) {objectives[OBJ_PASSENGER_RESCUED] =stringEquals(value, "YES");}
            else if (stringEquals(line, "CAT_RESCUED")) {objectives[OBJ_CAT_SECURED] =stringEquals(value, "YES");}
            else if (stringEquals(line, "CABINET_UNLOCKED")) {objectives[OBJ_CABINET_UNLOCKED] =stringEquals(value, "YES");}
            else if (stringEquals(line, "TRAIN_KEY_COLLECTED")) {objectives[OBJ_TRAIN_KEY] =stringEquals(value, "YES");}
            else if (stringEquals(line, "FUSE_INSTALLED")) {objectives[OBJ_FUSE_INSTALLED] =stringEquals(value, "YES");}
            else if (stringEquals(line, "LIFT_PASS_COLLECTED")) {objectives[OBJ_LIFT_PASS] =stringEquals(value, "YES");}
            else if (stringEquals(line, "TRAIN_PREPARED")) {objectives[OBJ_TRAIN_PREPARED] =stringEquals(value, "YES");}}}

    file.close();
    return true;}

bool loadBuildingMap(const char* filename,char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]){
    ifstream mapFile(filename);
    if (!mapFile.is_open()) {return false;}
    for (int floor = 0; floor < NUM_FLOORS; floor++) {
        for (int connection = 0;
             connection < ROOMS_PER_FLOOR - 1;
             connection++) {horizontalConn[floor][connection] = CONN_NONE;}
        for (int room = 0; room < ROOMS_PER_FLOOR; room++) {
            entityCounts[floor][room] = 0;
            for (int item = 0; item < MAX_ENTITIES_PER_ROOM; item++) {
                roomEntities[floor][room][item] = ENT_NONE;}}}
    string line;
    int currentFloor = -1;
    int roomLabelColumn[ROOMS_PER_FLOOR];
    bool expectingEntityLine = false;
    while (getline(mapFile, line)) {
        int lineLength = line.length();
        bool hasRoomLabels = false;
        for (int i = 0; i + 4 < lineLength; i++) {
            if (line[i] == 'F' &&line[i + 1] >= '1' && line[i + 1] <= '5' &&line[i + 2] == '-' &&line[i + 3] == 'R' &&line[i + 4] >= '1' && line[i + 4] <= '4') {
                currentFloor = line[i + 1] - '1';
                int roomIndex = line[i + 4] - '1';
                roomLabelColumn[roomIndex] = i;
                hasRoomLabels = true;}}
        if (hasRoomLabels) {
            for (int room = 0; room < ROOMS_PER_FLOOR - 1; room++) {int start = roomLabelColumn[room] + 5;int end = roomLabelColumn[room + 1];
                for (int column = start; column < end; column++) {
                    if (line[column] == 'D' ||line[column] == 'W' ||line[column] == '#' ||(line[column] == 'L' &&line[column + 1] != '1' &&line[column + 1] != '2')) {horizontalConn[currentFloor][room] = line[column];}}}
            expectingEntityLine = true;
            continue;}
        if (expectingEntityLine) {expectingEntityLine = false;
            for (int column = 0; column < lineLength; column++) {
                char symbol = line[column];
                if (symbol != ENT_NONE &&
                    !stringEquals(getEntityName(symbol), "unknownentity")) {
                    int roomIndex = 0;
                    if (column >=(roomLabelColumn[0] + roomLabelColumn[1]) / 2) {roomIndex = 1;}
                    if (column >=(roomLabelColumn[1] + roomLabelColumn[2]) / 2) {roomIndex = 2;}
                    if (column >=(roomLabelColumn[2] + roomLabelColumn[3]) / 2) {roomIndex = 3;}
                    if (entityCounts[currentFloor][roomIndex] <
                        MAX_ENTITIES_PER_ROOM) {
                        int slot = entityCounts[currentFloor][roomIndex];
                        roomEntities[currentFloor][roomIndex][slot] = symbol;
                        entityCounts[currentFloor][roomIndex]++;}}}}}

    mapFile.close();
    return true;}