#pragma once
#include <vector>
#include "Observer.tpp"

template <class T>
class Subject
{
public:
    void notify(T message)
    {
        for(auto obs:observers)
            obs->onNotify(message);
    }

    void addObserver(Observer<T> *obs)
    {
        observers.push_back(obs);
    }
private:
    std::vector<Observer<T>*> observers;
};
