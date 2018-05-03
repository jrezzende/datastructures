#include "Vehicle.h"
#include "MyRandom.h"
#include <cstdlib>

Vehicle::Vehicle()
{
   vehicleSize= MyRandom::generate(2, 8) + 3;
   laneDecision= MyRandom::generate(1, 100) + 1;
}
