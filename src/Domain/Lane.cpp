#include "Lane.h"

Lane::Lane(int size, int avgSpeed, int creationGap, int creationTime) :
totalSize(size), actualSize(0), vehiclesWentThrough(0), vehiclesCreatedInSystem(0),
averageSpeed(avgSpeed)
{
   arrivalTime= totalSize / avgSpeed;
   posCreationTime= creationTime + creationGap;
   negCreationTime= creationTime - creationGap;

   if (creationGap == 0) {
      if (creationTime == 0) {
         sourceLane = false;
         sinkLane = true;
      }
      else if (creationTime == 1) {
         sourceLane = false;
         sinkLane = false;
      }
   }
   else {
      sourceLane= true;
      sinkLane= false;
   }
}

void Lane::newVehicle(Vehicle* v)
{
   auto newSize= actualSize + v->size();
   if (newSize > totalSize)
      return;

   this->enqueue(v);
   actualSize= newSize;
   vehiclesCreatedInSystem++;
}
