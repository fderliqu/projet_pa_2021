#include "../includes/init.h"
#include "../includes/condition_function.h"

int number_parameter_test(struct line_arguments liste, int nbr)
{
    if(liste.dernier > nbr)
    {
        printf("Too many argument in show-airport parameter\n");
        printf("--> Expected 1 argument, show-airport has %d arguments\n",liste.dernier);
        return 0;
    }
    if(liste.dernier < nbr)
    {
        printf("Error : Not enough argument in show-airport parameter\n");
        printf("--> Expected %d argument, show-airport has %d argument\n",nbr,liste.dernier);
        return 0;
    }
    return 1;
}

int lenght_parameter_test(struct line_arguments liste, size_t lenght)
{
    if(strlen(liste.arg[liste.dernier]) != lenght)
    {
        printf("Error : Parameter 1 is incorrect\n");
        printf("--> Expected a lenght of %d letters, parameter has a lenght of %d letter(s)\n",lenght,strlen(liste.arg[1]));
        return 0;
    }
    return 1;
}