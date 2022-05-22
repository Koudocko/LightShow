#ifndef LS_H
#define LS_H

#include <Arduino.h>

class LightShow{
public:
   void begin();
   void run();
   void push(unsigned long pin, unsigned long length, int& value);
   
private:
   struct Light{
      Light(unsigned long pin, unsigned long length, int& value) : pinNum{pin}, lightLength{length}, lightValue{value}{}
      
      int& lightValue;
      unsigned long lightLength, timeStart{}, timeElapsed{};
      unsigned long pinNum;
      Light* next{nullptr};
   };
   
   unsigned long size{};
   Light* head{nullptr}, *tail{nullptr}, *curr{nullptr};
};

#endif