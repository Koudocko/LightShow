#ifndef LS_H
#define LS_H

#include <Arduino.h>

class LightShow{
public:
   void begin();
   void run();
   void push(unsigned long pin, unsigned long length, bool& condition);
   
private:
   struct Light{
      Light(unsigned long pin, unsigned long length, bool& condition) : pinNum{pin}, lightLength{length}, lightState{condition}{}
      
      bool& lightState;
      unsigned long lightLength, timeStart{}, timeElapsed{};
      unsigned long pinNum;
      Light* next{nullptr};
   };
   
   bool state;
   unsigned long delay, size{};
   Light* head{nullptr}, *tail{nullptr}, *curr{nullptr};
};

#endif