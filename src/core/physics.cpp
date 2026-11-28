#include "physics.h"
#include "util.h"
#include "switches.h"
// Movement validation and resource adjustments without structures

// Connection types used only by this file
static const char STAIRS_CONN = 'S';
static const char LIFT1_CONN = '1';
static const char LIFT2_CONN = '2';
// check if two rooms are connected and gives the connection type
bool isDirectlyConnected (int fromF, int fromR, int toF, int toR,
                         const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
                         char& outConnType)
                         {
                            if (fromF != toF) return false;
                            if (fromR - toR != 1 && fromR - toR != -1) return false;
                            int index;
                            if (fromR < toR) index = fromR - 1;
                            else index = toR - 1;
                            outConnType = horizontalConn[fromF - 1][index];    
                            return true;    
                         }

// takes coonection type and checks if palyer is allowed to pass through it or not, it also checks required items in inventory,remaining emergency trips, if lift 2 is operational
bool canTraverse(int targetFloor, int targetRoom, char connType,
                 const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                 int emergencyTripsLeft, bool lift2Operational)
                 {
                   if (targetFloor < 1 || targetFloor > NUM_FLOORS || targetRoom < 1 || targetRoom > ROOMS_PER_FLOOR) return false;
                   if (connType == CONN_SOLID_WALL) return false;
                   if (connType == CONN_DOOR) return true;
                   if (connType == CONN_WINDOW) return true;
                   if (connType == CONN_LOCKED_DOOR)
                   return hasItem(inventory, inventoryCount, ENT_MASTER_KEY);
                   if (connType == STAIRS_CONN) return true;
                   if (connType == LIFT1_CONN) return true;
                   if (connType == LIFT2_CONN) return lift2Operational || emergencyTripsLeft > 0;

                   return false;
                  }

