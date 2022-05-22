#include "ls.h"

void LightShow::begin(){
    head->timeStart = millis();
    head->timeElapsed = millis()-curr->timeStart;
}

void LightShow::run(){
    curr->timeElapsed = millis()-curr->timeStart;
    
    if (curr->timeElapsed >= curr->lightLength){
        if (curr->next)
            curr = curr->next;  
        else
            curr = head;

        curr->timeStart = millis();
        curr->timeElapsed = millis()-curr->timeStart;
    }
    
    analogWrite(curr->pinNum, curr->lightState);
}

void LightShow::push(unsigned long pin, unsigned long length, int& value){
    if (!size){
        head = new Light(pin, length, value);
        tail = head, curr = head;
        ++size;
        return;
    }

    tail->next = new Light(pin, length, value);
    tail = tail->next;
    ++size;
}
 