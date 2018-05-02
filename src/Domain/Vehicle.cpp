#include "Vehicle.h"
#include "MyRandom.h"

Vehicle::Vehicle()
{
   vehicleSize= MyRandom::generate(2, 8) + 3;
   laneDecision= MyRandom::generate(1, 100) + 1;
}
