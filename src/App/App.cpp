#include "App.h"

App::App(int _semaphoreDelay, int execTime) : semaphoreDelay(_semaphoreDelay), executionTime(execTime), actualTime(0)
{
   semaphores= new RingBuffer<Semaphore*>();
   lanes= new RingBuffer<Lane*>();
   eventList= new EventList();
   
   initializeComponents();
   callAsciiArt();
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
   Lane* O1OESTE= new Lane();
}

void App::launch()
{
}

void App::generateVehicleEvents()
{
}

void App::generateSemaphoreArrivalEvents()
{
}

void App::generateSemaphoreOpeningEvents()
{
}

void App::vehicleAtSemaphore(Event * actual)
{
}

Semaphore * App::searchSemaphore(Lane * _lane)
{
   return nullptr;
}

void App::runEvents()
{
}

void App::countVehicles()
{
}

void App::end()
{
}
