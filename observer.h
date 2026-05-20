#pragma once
#include <string>
#include <iostream>

class IObserver {
public:
    virtual void onEvent(const std::string& eveniment) = 0;
    virtual ~IObserver() = default;
};

class HospitalLogger : public IObserver {
public:
    void onEvent(const std::string& eveniment) override {
        std::cout << "\n[NOTIFICARE SYSTEM - OBSERVER] " << eveniment << "\n";
    }
};