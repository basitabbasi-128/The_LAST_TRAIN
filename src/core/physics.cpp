#include "physics.h"
#include "util.h"
#include "switches.h"

// Movement validation and resource adjustments without structures

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


