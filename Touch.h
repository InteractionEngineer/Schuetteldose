#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>

class Touch
{
public:
    Touch(int);
    bool isTouched();
    void print();

private:
    int _pin;
};

#endif // TOUCH_H