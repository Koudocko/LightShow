#ifndef EXPR_H
#define EXPR_H

class Expr{
public:
    enum State { addE, subE, mulE, divE, andE, orE, notE, valE };

    ~Expr();
    Expr(int& valE);
    Expr(int&& valE);
    static Expr* makeExpr(int& valE);
    static Expr* makeExpr(int&& valE);
    int getData();
    void refresh();

    static Expr* addF(Expr* opA, Expr* opB);
    static Expr* subF(Expr* opA, Expr* opB);
    static Expr* mulF(Expr* opA, Expr* opB);
    static Expr* divF(Expr* opA, Expr* opB);
    static Expr* andF(Expr* opA, Expr* opB);
    static Expr* orF(Expr* opA, Expr* opB);
    static Expr* notF(Expr* op);

private:
    Expr* operandA{nullptr}, *operandB{nullptr}; 
    int& dataRef, dataTemp, exprState;
};

#endif