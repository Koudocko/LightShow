#include "ls.h"

void LightShow::begin(){
    head->timeStart = millis();
    head->timeElapsed = millis()-curr->timeStart;
}

void LightShow::refresh(){
    if (state){
        curr->valExpr->refresh();
        
        curr->timeElapsed = millis()-curr->timeStart;
        
        if (curr->timeElapsed >= curr->lightLength){
            if (curr->next)
                curr = curr->next;  
            else if (--cycles)
                curr = head;
            else
                state = false;
                
            if (cycles < 0) cycles = -1;
            curr->timeStart = millis();
            curr->timeElapsed = millis()-curr->timeStart;
        }
        
        if (curr->writeMode)
            analogWrite(curr->pinNum, curr->valExpr->getData());
        else
            digitalWrite(curr->pinNum, curr->valExpr->getData());
    }
}

void LightShow::push(unsigned long pin, unsigned long length, Expr& expr, int mode){
    if (!size){
        head = new Light(pin, length, &expr, mode);
        tail = head, curr = head;
        ++size;
        return;
    }

    tail->next = new Light(pin, length, &expr, mode);
    tail = tail->next;
    ++size;
}

LightShow::~LightShow(){
    while(head){
        delete head->valExpr;
        head = head->next;
    }
}