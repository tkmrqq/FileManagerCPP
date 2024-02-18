#ifndef EXP_H
#define EXP_H

#include "cstring"
#include "iostream"

class Exp
{
    int code;
    char msg[80]{};

public:
    Exp();
    Exp(int, char[]);
    void show();
};

class ExpInput : public Exp
{
public:
    ExpInput(int a, char *b) : Exp(a, b){};
};

class ExpFile : public Exp
{
public:
    ExpFile() : Exp(){};
    ExpFile(int code_t, char msg_t[80]) : Exp(code_t, msg_t){};
};

class ExpCout : public Exp
{
    ExpCout() : Exp(){};
    ExpCout(int code_t, char msg_t[80]) : Exp(code_t, msg_t){};
};

#endif // EXP_H
