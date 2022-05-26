#ifndef LS_H
#define LS_H

#include <Arduino.h>
#include "expr.h"

#define DIGITAL 0
#define ANALOG 1

class LightShow{
public:
   LightShow(int iter = -1) : cycles{iter}, copyCycles{iter}{}
   ~LightShow();
	
   void refreshAll();
   void onSwitch(void (*func)());
   bool active();
   void reset();
   void refreshLight();
   void push(unsigned long pin, unsigned long length, Expr& expr, int mode);
   
private:
   struct Light{
      Light(unsigned long pin, unsigned long length, Expr* expr, int mode) : pinNum{pin}, lightLength{length}, valExpr{expr}, writeMode{mode}{}
      
      Expr* valExpr;
      int writeMode;
      unsigned long lightLength, timeStart{}, timeElapsed{};
      unsigned long pinNum;
      Light* next{nullptr};
   };
   
   bool state{true}, begin{};
   int cycles, copyCycles;
   unsigned long size{};
   Light* head{}, *tail{}, *curr{};
   void (*callback)(){};
};

#endif