#ifndef LS_H
#define LS_H

#include <Arduino.h>
#include "expr.h"

#define DIGITAL 0
#define ANALOG 1

class LightShow{
public:
   void begin();
   void refresh();
   void push(unsigned long pin, unsigned long length, Expr* expr, int mode);
   
private:
   struct Light{
      Light(unsigned long pin, unsigned long length, Expr* expr, int mode) : pinNum{pin}, lightLength{length}, valExpr{expr}, writeMode{mode}{}
      
      Expr* valExpr;
      int writeMode;
      unsigned long lightLength, timeStart{}, timeElapsed{};
      unsigned long pinNum;
      Light* next{nullptr};
   };
   
   unsigned long size{};
   Light* head{nullptr}, *tail{nullptr}, *curr{nullptr};
};

#endif