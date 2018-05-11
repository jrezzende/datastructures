#pragma once
#ifndef INCLUDED_EVENT_H
#define INCLUDED_EVENT_H

#include "LinkedList.h"

class Event
{
   int eventTime;
   int eventType;

   void* obj;
   void* obj_related;

public:
   Event(int time, int type, void* object, void* rel) : eventTime(time), eventType(type), obj(object), obj_related(rel) {}

   int time() const { return eventTime; }
   int type() const { return eventType; }
   void* object() { return obj; }
   void* related() { return obj_related; }
};

class EventList : public LinkedList<Event*> {
public:
   bool greater(Event* data1, Event* data2) const { return (data1->time() > data2->time()); }
};

#endif // !INCLUDED_EVENT_H
