#include "expr.h"

Expr::Expr(int& valE) : dataRef{valE}{
    exprState = State::valE;
}

Expr::Expr(int&& valE) : dataTemp{valE}, dataRef{dataTemp}{
    exprState = State::valE;
}

Expr* Expr::makeExpr(int& valE){
    return new Expr(valE);
}

Expr* Expr::makeExpr(int&& valE){
    return new Expr(valE);
}

Expr* Expr::addF(Expr* opA, Expr* opB){
    Expr* newExpr = new Expr(opA->dataRef+opB->dataTemp);
    newExpr->operandA = opA, newExpr->operandB = opB;
    newExpr->exprState = State::addE;
    return newExpr;
}

Expr* Expr::subF(Expr* opA, Expr* opB){
    Expr* newExpr = new Expr(opA->dataRef-opB->dataTemp);
    newExpr->operandA = opA, newExpr->operandB = opB;
    newExpr->exprState = State::subE;
    return newExpr;
}

Expr* Expr::mulF(Expr* opA, Expr* opB){
    Expr* newExpr = new Expr(opA->dataRef*opB->dataTemp);
    newExpr->operandA = opA, newExpr->operandB = opB;
    newExpr->exprState = State::mulE;
    return newExpr;
}

Expr* Expr::divF(Expr* opA, Expr* opB){
    Expr* newExpr = new Expr(opA->dataRef/opB->dataTemp);
    newExpr->operandA = opA, newExpr->operandB = opB;
    newExpr->exprState = State::divE;
    return newExpr;
}

Expr* Expr::modF(Expr* opA, Expr* opB){
    Expr* newExpr = new Expr(opA->dataRef%opB->dataTemp);
    newExpr->operandA = opA, newExpr->operandB = opB;
    newExpr->exprState = State::modE;
    return newExpr;
}

Expr* Expr::andF(Expr* opA, Expr* opB){
    Expr* newExpr = new Expr(opA->dataRef && opB->dataTemp);
    newExpr->operandA = opA, newExpr->operandB = opB;
    newExpr->exprState = State::andE;
    return newExpr;
}

Expr* Expr::orF(Expr* opA, Expr* opB){
    Expr* newExpr = new Expr(opA->dataRef || opB->dataTemp);
    newExpr->operandA = opA, newExpr->operandB = opB;
    newExpr->exprState = State::orE;
    return newExpr;
}

Expr* Expr::notF(Expr* op){
    Expr* newExpr = new Expr(!op->dataRef);
    newExpr->operandA = op;
    newExpr->exprState = State::notE;
    return newExpr;
}

void Expr::refresh(){
    if (exprState != State::valE){
        operandA->refresh();
        if (exprState != State::notE)
            operandB->refresh();

        switch(exprState){
            case State::addE: 
                dataRef = operandA->dataRef+operandB->dataRef;
                break;
            case State::subE: 
                dataRef = operandA->dataRef-operandB->dataRef;
                break;
            case State::mulE: 
                dataRef = operandA->dataRef*operandB->dataRef;
                break;
            case State::divE: 
                dataRef = operandA->dataRef/operandB->dataRef;
                break;
            case State::modE: 
                dataRef = operandA->dataRef%operandB->dataRef;
                break;
            case State::andE: 
                dataRef = operandA->dataRef && operandB->dataRef;
                break;
            case State::orE: 
                dataRef = operandA->dataRef || operandB->dataRef;
                break;
            case State::notE: 
                dataRef = !operandA->dataRef;
                break;
        }
    }
}

Expr::~Expr(){
    if (operandA)
        delete operandA;
    if (operandB)
        delete operandB;
}

int Expr::getData(){
    return dataRef;
}