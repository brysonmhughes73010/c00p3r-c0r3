#ifndef BLUEDUCKY_H
#define BLUEDUCKY_H

#include <Arduino.h>

class BlueDucky {
public:
    void init();
    void executePayload(const String& payload);
};

#endif
