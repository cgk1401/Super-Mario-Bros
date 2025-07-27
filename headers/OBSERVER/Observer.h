#pragma once
#include "EventDataBase.h"
using namespace std;

class Observer{
public:
    virtual void onNotify(const EventType& event, void* data = nullptr) = 0;
    virtual ~Observer() = default;
};