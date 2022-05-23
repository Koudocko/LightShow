#ifndef LS_H
#define LS_H

#include <Arduino.h>

#define DIGITAL 0
#define ANALOG 1

class LightShow{
public:
   void begin();
   void run();
   void push(unsigned long pin, unsigned long length, int& value, int mode);
   
private:
   struct Light{
      Light(unsigned long pin, unsigned long length, int& value, int mode) : pinNum{pin}, lightLength{length}, lightValue{value}, writeMode{mode}{}
      
      int& lightValue, writeMode;
      unsigned long lightLength, timeStart{}, timeElapsed{};
      unsigned long pinNum;
      Light* next{nullptr};
   };
   
   unsigned long size{};
   Light* head{nullptr}, *tail{nullptr}, *curr{nullptr};
};

#endif