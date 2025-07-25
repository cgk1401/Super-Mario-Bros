#pragma once

enum class EventType{
    COIN_COLLECT,
};

class Observer{
public:
    virtual void onNotify(const EventType& event, void* data = nullptr) = 0;
    virtual ~Observer() = default;
};