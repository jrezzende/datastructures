#include "App.h"

App::App() : actualTime(0), vehiclesThroughSemaphores(0), vehiclesCreatedInSystem(0)
{
   callAsciiArt();

   std::cout << "Enter an integer number for the semaphore delay." << std::endl;
   std::cin >> semaphoreDelay;

   std::cout << "Enter another integer number for the total execution time of the system." << std::endl;
   std::cin >> executionTime;

   this->semaphores= new RingList<Semaphore*>();
   this->lanes= new RingList<Lane*>();
   eventList= new EventList();
   
   initializeComponents();
   
   launch();
}

void App::callAsciiArt()
{
   std::cout << R"(
               TRAFFIC JAM SYSTEM!


                       ##
                      _[]_
                     [____]
                 .----'  '----.
             .===|    .==.    |===.
             \   |   /####\   |   /
             /   |   \####/   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /::::\   |   /
             /   |   \::::/   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /&&&&\   |   /
             /   |   \&&&&/   |   \
             '===|    `""`    |==='
                 '--.______.--'


)" << std::endl;
}

void App::initializeComponents()
{
   Lane* O1WEST = new Lane(2000, 80, 0, 0);
   Lane* N1SOUTH = new Lane(500, 60, 5, 20);
   Lane* N1NORTH = new Lane(500, 60, 0, 0);
   Lane* C1WEST = new Lane(300, 60, 0, 0);
   Lane* N2SOUTH = new Lane(500, 40, 5, 20);
   Lane* N2NORTH = new Lane(500, 40, 0, 0);
   Lane* L1WEST = new Lane(400, 30, 2, 10);
   Lane* L1EAST = new Lane(400, 30, 0, 0);
   Lane* S2NORTH = new Lane(500, 40, 15, 60);
   Lane* S2SOUTH = new Lane(500, 40, 0, 0);
   Lane* C1EAST = new Lane(300, 60, 0, 0);
   Lane* S1NORTH = new Lane(500, 60, 7, 30);
   Lane* S1SOUTH = new Lane(500, 60, 0, 0);
   Lane* O1EAST = new Lane(2000, 80, 2, 10);

   lanes->push(O1WEST);
   lanes->push(N1SOUTH);
   lanes->push(N1NORTH);
   lanes->push(C1WEST);
   lanes->push(N2SOUTH);
   lanes->push(N2NORTH);
   lanes->push(L1WEST);
   lanes->push(L1EAST);
   lanes->push(S2NORTH);
   lanes->push(S2SOUTH);
   lanes->push(C1EAST);
   lanes->push(S1NORTH);
   lanes->push(S1SOUTH);
   lanes->push(O1EAST);

   Lane* laneO1East[4] = { O1EAST, C1EAST, N1NORTH, S1SOUTH };
   int oddsLaneO1East[3] = { 80, 10, 10 };
   Semaphore* semaphore01East = new Semaphore(true, static_cast<Lane**>(laneO1East),
      static_cast<int*>(oddsLaneO1East), semaphoreDelay);

   Lane* laneN1South[4] = { N1SOUTH, C1EAST, O1WEST, S1SOUTH };
   int oddsLaneN1South[3] = { 80, 10, 10 };
   Semaphore* semaphoreN1South = new Semaphore(false, static_cast<Lane**>(laneN1South),
      static_cast<int*>(oddsLaneN1South), semaphoreDelay);

   Lane* laneS1North[4] = { S1NORTH, C1EAST, N1NORTH, O1WEST };
   int oddsLaneS1North[3] = { 80, 10, 10 };
   Semaphore* semaphoreS1North = new Semaphore(false, static_cast<Lane**>(laneS1North),
      static_cast<int*>(oddsLaneS1North), semaphoreDelay);

   Lane* laneC1West[4] = { C1WEST, O1WEST, N1NORTH, S1SOUTH };
   int oddsLaneC1West[3] = { 40, 30, 30 };
   Semaphore* semaphoreC1West = new Semaphore(false, static_cast<Lane**>(laneC1West),
      static_cast<int*>(oddsLaneC1West), semaphoreDelay);

   Lane* laneC1East[4] = { C1EAST, L1EAST, N2NORTH, S2SOUTH };
   int oddsLaneC1East[3] = { 40, 30, 30 };
   Semaphore* semaphoreC1East = new Semaphore(false, static_cast<Lane**>(laneC1East),
      static_cast<int*>(oddsLaneC1East), semaphoreDelay);

   Lane* laneN2South[4] = { N2SOUTH, L1EAST, C1WEST, S2SOUTH };
   int oddsLaneN2South[3] = { 40, 30, 30 };
   Semaphore* semaphoreN2South = new Semaphore(false, static_cast<Lane**>(laneN2South),
      static_cast<int*>(oddsLaneN2South), semaphoreDelay);

   Lane* laneS2North[4] = { S2NORTH, L1EAST, S2SOUTH, C1WEST };
   int oddsLaneS2North[3] = { 40, 30, 30 };
   Semaphore* semaphoreS2North = new Semaphore(false, static_cast<Lane**>(laneS2North),
      static_cast<int*>(oddsLaneS2North), semaphoreDelay);

   Lane* laneL1West[4] = { L1WEST, N2NORTH, C1EAST, S2SOUTH };
   int oddsLaneL1West[3] = { 40, 30, 30 };
   Semaphore* semaphoreL1West= new Semaphore(false, static_cast<Lane**>(laneL1West),
      static_cast<int*>(oddsLaneL1West), semaphoreDelay);

   semaphores->push(semaphore01East);
   semaphores->push(semaphoreN1South);
   semaphores->push(semaphoreS1North);
   semaphores->push(semaphoreC1West);
   semaphores->push(semaphoreC1East);
   semaphores->push(semaphoreN2South);
   semaphores->push(semaphoreS2North);
   semaphores->push(semaphoreL1West);
}

void App::launch()
{
   generateVehicleEvents();
   generateSemaphoreArrivalEvents();
   generateSemaphoreOpeningEvents();
   runEvents();
}

void App::generateVehicleEvents()
{
   Lane* currentLane; 
   Event* event;
   int localTime;
   int nextEvent;
   
   for (int i = 0; i < lanes->ringListSize(); i++) {
      currentLane= lanes->at(i);
      if (currentLane->isSource()) {
         localTime= actualTime;
         while (localTime < executionTime) {
            nextEvent = currentLane->nextEvent(localTime);
         if (nextEvent <= executionTime) {
            event= new Event(nextEvent, 0, new Vehicle(), currentLane);
            eventList->insert_sorted(event);
            localTime= nextEvent;
         }
         break;
         }
      }
   }
}

void App::generateSemaphoreArrivalEvents()
{
   Lane* currentLane;
   Semaphore* semaphore;
   Event* event;

   int arrivalTime, nextEvent;
   int totalSize= eventList->size();
   
   for (int i = 0; i < totalSize; i++) {
      if (eventList->at(i)->type() == 0) {
         arrivalTime= eventList->at(i)->time();
         currentLane= static_cast<Lane*>(eventList->at(i)->related());
         semaphore= searchSemaphore(currentLane);
         nextEvent= currentLane->carArrival(arrivalTime);

         if (nextEvent <= executionTime) {
            event= new Event(nextEvent, 2, semaphore, nullptr);
            eventList->insert_sorted(event);
         }
         break;
      }
   }
}

void App::generateSemaphoreOpeningEvents()
{
   Semaphore* currentSemaphore;
   Semaphore* nextSemaphore;

   Event* firstEvent;
   Event* secondEvent;

   int localTime, nextEvent;

   for (int i = 0; i < semaphores->ringListSize(); i += 2) {
      localTime= actualTime;
      while (localTime < executionTime) {
         currentSemaphore= semaphores->at(i);
         nextSemaphore= semaphores->at(i + 1);
         nextEvent= currentSemaphore->calcEvent(localTime);

         if (nextEvent <= executionTime) {
            firstEvent= new Event(nextEvent, 1, currentSemaphore, nullptr);
            secondEvent= new Event(nextEvent, 1, nextSemaphore, nullptr);
            eventList->insert_sorted(firstEvent);
            eventList->insert_sorted(secondEvent);
         }
         localTime= nextEvent;
      }
   }

}

void App::vehicleAtSemaphore(Event* actualEvent)
{
   Event* event;
   Semaphore* currentSemaphore = static_cast<Semaphore*>(actualEvent->object());
   actualTime = actualEvent->time();
   int nextEvent = -1;
   try {
      Lane* nextLane = currentSemaphore->laneAvailable();
      if (nextLane == currentSemaphore->currentLane()) {
         if (actualTime < currentSemaphore->remaningTime()) {
            nextEvent = actualTime + 1;
            event = new Event(nextEvent, 2, currentSemaphore, nullptr);
         }
         else {
            nextEvent = currentSemaphore->remaningTime() + 1;
            event = new Event(nextEvent, 2, currentSemaphore, nullptr);
         }
      }
      if (nextLane->isSink()) {
         nextEvent = nextLane->carArrival(actualTime);
         event = new Event(nextEvent, 3, nextLane, nullptr);
      }
      Semaphore* semaphore = searchSemaphore(nextLane);
      nextEvent = nextLane->carArrival(actualTime);
      event = new Event(nextEvent, 2, semaphore, nullptr);
   }
   catch (std::exception const &e) {
      nextEvent = currentSemaphore->remaningTime() + 1;
      event = new Event(nextEvent, 2, currentSemaphore, nullptr);
   }
   if (nextEvent != -1 && nextEvent <= executionTime)
      eventList->insert_sorted(event);
}

Semaphore* App::searchSemaphore(Lane* _lane)
{
   for (int i = 0; i < semaphores->size(); i++) {
      Semaphore* currentSemaphore= semaphores->at(i);
      if (currentSemaphore->currentLane() == _lane) {
         return currentSemaphore;
      }
      return nullptr;
   }
}

void App::runEvents()
{
   for (int i = 0; i < eventList->size(); i++) {
      Event* currentEvent = eventList->at(i);
      if (!(actualTime <= executionTime))
         break;
      switch (currentEvent->type()) {

      case 0: {
         Lane* lane= static_cast<Lane*>(currentEvent->related());
         Vehicle* vehicle= static_cast<Vehicle*>(currentEvent->object());
         lane->enqueue(vehicle);
         actualTime= currentEvent->time();
         break;
      }
      case 1: {
         Semaphore* semaphore= static_cast<Semaphore*>(currentEvent->object());
         semaphore->switchOpenSemaphore(actualTime);
         actualTime = currentEvent->time();
         break;
      }
      case 2: {
         vehicleAtSemaphore(currentEvent);
         break;
      }
      case 3: {
         Lane* lane= static_cast<Lane*>(currentEvent->object());
         lane->eraseCar();
         actualTime= currentEvent->time();
         break;
      }
      default:
         std::cout << "Error while processing events" << std::endl;
      }
      eventList->pop_data(currentEvent);
   }
   report();
}

void App::countVehicles()
{
   for (int i = 0; i < lanes->size(); i++) {
      Lane* currentLane = lanes->at(i);
      if (currentLane->isSource())
         vehiclesCreatedInSystem = vehiclesCreatedInSystem + currentLane->vehiclesThrough();
      else
         if (currentLane->isSink()) {
            vehiclesThroughSemaphores= vehiclesThroughSemaphores + currentLane->vehiclesCreated();
         }
   }
}

void App::report()
{
   countVehicles();

   std::cout << "Vehicles created in the system: " << vehiclesCreatedInSystem << std::endl;
   std::cout << "Vehicles that went through semaphores: " << vehiclesThroughSemaphores << std::endl;
   std::cout << std::endl;
}