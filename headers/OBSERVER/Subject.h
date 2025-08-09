#pragma once
#include "OBSERVER/Observer.h"
#include <vector>
using namespace std;

class Subject{
protected:
    vector<Observer*> observers;
public:
    void deleteAllObservers() {
        observers.clear();
    }
    void attachObserver(Observer* obs){
        observers.push_back(obs);
    }
    void removeObserver(Observer* obs){
         observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
    }
public:
    void notify(const EventType& event, void* data = nullptr) {
        for (auto obs : observers)
            obs->onNotify(event, data);
    }

};