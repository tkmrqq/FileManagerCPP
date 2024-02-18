#include "exp.h"

Exp::Exp()
{
    code = 0;
}

Exp::Exp(int code_t, char msg_t[80])
{
    code = code_t;
    strcpy(msg, msg_t);
}
void Exp::show()
{
    std::cout << "Error: " << code << " " << msg << std::endl;
}

void CheckLength(char *str, int min, int max)
{
    if (strlen(str) > max || strlen(str) < min) {
        throw Exp(104, "Bad size");
    }
}

void checkChar(char *str)
{
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] < 'A' || str[i] > 'z')
            throw Exp(105, "Input only english letters.");
    }
}

void checkField(int x)
{
    if (x < 0)
        throw Exp(106, "Num must be > 0");
}
