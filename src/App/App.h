#pragma once
#ifndef INCLUDED_APP_H
#define INCLUDED_APP_H

#include <iostream>
#include "RingList.h"
#include "Event.h"
#include "Semaphore.h"
#include "Lane.h"

class App
{
   RingList<Semaphore*>* semaphores;
   RingList<Lane*>* lanes;

   EventList* eventList;

   int actualTime;

   int semaphoreDelay;
   int executionTime;
   int vehiclesThroughSemaphores;
   int vehiclesCreatedInSystem;

public:
  ~App()= default;
  App();

  void callAsciiArt();
  void initializeComponents();
  void launch();

  void generateVehicleEvents();
  void generateSemaphoreArrivalEvents();
  void generateSemaphoreOpeningEvents();
  void vehicleAtSemaphore(Event* actual);

  Semaphore* searchSemaphore(Lane* _lane);

  void runEvents();
  void countVehicles();
  void report();
};

#endif // INCLUDED_APP_H
