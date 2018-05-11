#pragma once
#ifndef INCLUDED_SEMAPHORE_H
#define INCLUDED_SEMAPHORE_H

#include "RedSignException.h"
#include "List.h"
#include "Lane.h"

class Semaphore 
{
   ArrayList<Lane*>* lanes;
   Lane* currentLane_;

   int gapTime;
   int* odds;
   int remTimeToOpen;

   bool isOpen;

public:
   Semaphore(bool _isOpen, Lane* _lanes[], int* _odds, int _gapTime);

   Lane* laneAvailable();
   Lane* currentLane() { return currentLane_; }

   void switchOpenSemaphore(int actualTime);

   int calcEvent(int actualTime);
   int calcOdd(Vehicle* vehicle);
   int gap() { return gapTime; }
   int remaningTime() { return remTimeToOpen; }
   
};

#endif // !INCLUDED_SEMAPHORE_H
