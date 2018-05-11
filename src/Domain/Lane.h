#pragma once
#ifndef INCLUDED_LANE_H
#define INCLUDED_LANE_H

#include "LinkedQueue.h"
#include "Vehicle.h"

class Lane : public LinkedQueue<Vehicle*>
{
   bool sourceLane;
   bool sinkLane;
   
   int totalSize; 
   int actualSize;

   int vehiclesWentThrough;
   int vehiclesCreatedInSystem;

   int averageSpeed;
   int arrivalTime;

   int posCreationTime;
   int negCreationTime;

public:
   ~Lane()= default;
   Lane(int size, int avgspeed, int creationgap, int creationtime);

   void newVehicle(Vehicle* v);
   void eraseCar() { this->dequeue(); vehiclesWentThrough++; }

   int nextEvent(int actualTime) { return (negCreationTime + (MyRandom::generate(1, 100) % posCreationTime - 2 + 1)) + actualTime; }
   int carArrival(int carCreation) { return carCreation + arrivalTime; }

   bool laneFull() { return actualSize >= totalSize; }
   bool laneFull(Vehicle* v) { return actualSize + v->size() > totalSize; }
   bool isSource() { return this->sourceLane; }
   bool isSink() { return this->sinkLane; }

   const int laneSize() { return this->totalSize; }
   const int vehiclesThrough() { return this->vehiclesWentThrough; }
   const int vehiclesCreated() { return this->vehiclesCreatedInSystem; }
};

#endif // !INCLUDED_LANE_H
