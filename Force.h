#if !defined(FORCE_H)
#define FORCE_H

#include <Arduino.h>

class Force
{
public:
    Force(int);
    int measure();
    void print();

private:
    int _pin;
};

#endif // FORCE_H
