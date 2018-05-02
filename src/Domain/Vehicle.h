#pragma once
#ifndef INCLUDED_VEHICLE_H
#define INCLUDED_VEHICLE_H

class Vehicle
{
   int vehicleSize;
   int laneDecision;

public:
   ~Vehicle()= default;
   Vehicle();

   const int size() { return vehicleSize; }
   const int lane() { return laneDecision; }
};

#endif // INCLUDED_VEHICLE_H