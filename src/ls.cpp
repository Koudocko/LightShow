#include "ls.h"

void LightShow::begin(){
    head->timeStart = millis();
    head->timeElapsed = millis()-curr->timeStart;
}

void LightShow::refresh(){
    curr->valExpr->refresh();
    
    curr->timeElapsed = millis()-curr->timeStart;
    
    if (curr->timeElapsed >= curr->lightLength){
        if (curr->next)
            curr = curr->next;  
        else
            curr = head;

        curr->timeStart = millis();
        curr->timeElapsed = millis()-curr->timeStart;
    }
    
    if (curr->writeMode)
        analogWrite(curr->pinNum, curr->valExpr->dataRef);
    else
        digitalWrite(curr->pinNum, curr->valExpr->dataRef);
}

void LightShow::push(unsigned long pin, unsigned long length, Expr* expr, int mode){
    if (!size){
        head = new Light(pin, length, expr, mode);
        tail = head, curr = head;
        ++size;
        return;
    }

    tail->next = new Light(pin, length, expr, mode);
    tail = tail->next;
    ++size;
}
 