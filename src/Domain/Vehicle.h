#pragma once
#ifndef INCLUDED_VEHICLE_H
#define INCLUDED_VEHICLE_H

#include "MyRandom.h"

class Vehicle
{
   int vehicleSize;
   int laneDecision;

public:
   ~Vehicle()= default;
   Vehicle() { vehicleSize = MyRandom::generate(2, 8) + 3; laneDecision = MyRandom::generate(1, 100) + 1; }

   const int size() { return vehicleSize; }
   const int lane() { return laneDecision; }
};

#endif // INCLUDED_VEHICLE_H