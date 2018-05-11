#include <vector>
#include <cstdlib>
#include "Semaphore.h"

Semaphore::Semaphore(bool _isOpen, Lane* _lanes[], int * _odds, int _gapTime) : 
isOpen(_isOpen), odds(_odds), gapTime(_gapTime), remTimeToOpen(0), currentLane_(_lanes[0])
{
   lanes= new ArrayList<Lane*>(std::size_t(3));
   
   for (int i= 0; i < 3; i++)
      lanes->push_back(_lanes[i]);

}

Lane* Semaphore::laneAvailable()
{
   Vehicle* vehicle= currentLane_->front();
   int laneChoice= calcOdd(vehicle);
   Lane* nextLane= lanes->at(laneChoice);
   if (!isOpen)
      throw RedSignException();
   if (!nextLane->laneFull(vehicle)) {
      currentLane_->eraseCar();
      nextLane->newVehicle(vehicle);
      return nextLane;
   }
   nextLane= currentLane_;
   return nextLane;
}

void Semaphore::switchOpenSemaphore(int actualTime)
{
   if (isOpen)
      calcEvent(actualTime);
   isOpen= !isOpen;
}

int Semaphore::calcEvent(int actualTime)
{
   return actualTime + this->gapTime;
}

int Semaphore::calcOdd(Vehicle * vehicle)
{
   int* new_odds= odds;
   int numberOfLanes= lanes->size();
   int laneChoice= vehicle->lane();
   std::vector<int> comp;
   comp.at(0)= odds[0];
   for (int i= 1; i < numberOfLanes; i++)
      comp.at(i)= comp.at(i -1) + odds[i];
   for (int i = 0; i < numberOfLanes; i++) {
      if (laneChoice <= comp.at(i))
         return i;
   }
   return -1;
}
