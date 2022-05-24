#ifndef EXPR_H
#define EXPR_H

class Expr{
public:
    enum State { addE, subE, mulE, divE, modE, andE, orE, notE, valE };

    ~Expr();
    Expr(int& valE);
    Expr(int&& valE);

    static Expr& make(int& valE);
    static Expr& make(int&& valE);

    int getData();
    void refresh();

    Expr& operator+(Expr& op);
    Expr& operator-(Expr& op);
    Expr& operator*(Expr& op);
    Expr& operator/(Expr& op);
    Expr& operator%(Expr& op);
    Expr& operator&&(Expr& op);
    Expr& operator||(Expr& op);
    Expr& operator!();

private:
    Expr* operandA{nullptr}, *operandB{nullptr}; 
    int& dataRef, dataTemp, exprState;
};

#endif

/*
lights.push(8, 500, Expr::makeExpr(var1) && Expr::makeExpr(var2), DIGITAL);
*/