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
   RingBuffer<Semaphore*>* semaphores;
   RingBuffer<Lane*>* lanes;

   EventList* eventList;

   int actualTime;

   int semaphoreDelay;
   int executionTime;
   int vehiclesThroughSemaphores;
   int vehiclesThroughSystem;

public:
  ~App()= default;
  App(int _semaphoreDelay, int execTime);

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
  void end();
};

#endif // INCLUDED_APP_H
