#include "push_swap.h"
#include <stdio.h>

void    errormsg()
{
    write(1,"Error", 5);
}

int main(int ac, char **av)
{
    if (ac >= 2)
    {
        int tac;
        int msg;


        msg = digitc(av[1]);
        if(msg == 0 || msg == -1)
        {
            errormsg();
            return -1;
        }
    }
}