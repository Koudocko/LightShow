#ifndef EXPR_H
#define EXPR_H

class Expr{
public:
    enum State { addE, subE, mulE, divE, modE, andE, orE, notE, valE };

    ~Expr();
    Expr(int& valE);
    Expr(const int& valE);
    Expr(const Expr& copyExpr) = delete;

    static Expr& make(int& valE);
    static Expr& make(const int& valE);

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