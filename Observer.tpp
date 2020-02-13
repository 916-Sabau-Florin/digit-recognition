#pragma once

template <class T>
class Observer
{
public:
    virtual void onNotify(T message) = 0;
private:
};
