#include "logger.h"
#include "util.h"
#include <fstream>
using namespace std;
// File persistence for savegame.txt and game_summary.txt using primitive variables

bool saveGameStateToFile(const char* filename,
                         int playerFloor, int playerRoom,
                         int energy, int time, int score,
                         const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                         const bool objectives[NUM_OBJECTIVES], int emergencyTripsLeft,
                         const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                         const int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]){
                            ofstream file(filename);
                            if (!file) return false;
                            file << "playerfloor " << playerFloor << endl;
                            file << "playerroom " << playerRoom << endl;
                            file << "energy " << energy << endl;
                            file << "time " << time << endl;
                            file << "score " << score << endl;
                            file << "inventorycount " << inventoryCount << endl;
                            file << "inventory";
                            for (int i = 0; i < inventoryCount; i++) {file << " " << inventory[i];}
                            file << endl;
                            file << "objectives";
                            for (int i = 0; i < NUM_OBJECTIVES; i++){ file << " " << objectives[i];}
                            file << endl;
                            file << "emergencytripsleft " << emergencyTripsLeft << endl;
                            file << "entitycounts" << endl;
                            for (int i = 0; i < NUM_FLOORS; i++){
                              for (int j = 0; j < ROOMS_PER_FLOOR; j++) {file << entityCounts[i][j] << " ";}
                              file << endl;
                            }
                            file << "roomentities" <<  endl;
                            for (int i = 0; i < NUM_FLOORS; i++){
                                for (int j = 0; j < ROOMS_PER_FLOOR; j++){
                                    for (int k = 0; k < entityCounts[i][j]; k++){file << roomEntities[i][j][k] << " ";}
                                    file << endl;
                                   }
                            }
                           file.close();
                           return true;
                           }

                         