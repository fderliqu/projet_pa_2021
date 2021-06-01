#include "../includes/init.h"
#include "../includes/condition_function.h"

int number_parameter_test(struct line_arguments liste, int nbr, int nbr_optionnal)
{
    if(liste.dernier > nbr + nbr_optionnal)
    {
        printf("Error : Too many argument in show-airport parameter\n");
        printf("--> Expected a maximum of %d argument(s), function has %d arguments\n",nbr_optionnal+nbr,liste.dernier);
        return 0;
    }
    if(liste.dernier < nbr - nbr_optionnal)
    {
        printf("Error : Not enough argument in show-airport parameter\n");
        printf("--> Expected a minimum of %d argument(s), function has %d argument(s)\n",nbr-nbr_optionnal,liste.dernier);
        return 0;
    }
    return 1;
}

int lenght_parameter_test(struct line_arguments liste, size_t lenght, int occ_test)
{
    if(strlen(liste.arg[occ_test]) != lenght)
    {
        printf("Error : Parameter 1 is incorrect\n");
        printf("--> Expected a lenght of %d letters, parameter has a lenght of %d letter(s)\n",lenght,strlen(liste.arg[occ_test]));
        return 0;
    }
    return 1;
}

char build_mask_time_limit(struct line_arguments liste, int size_with_no_option)
{
    if(liste.dernier == size_with_no_option)return timeOFF_limitOFF;
    if(liste.dernier == size_with_no_option+1)
    {
        char tmp[10];
        strcpy(tmp,liste.arg[size_with_no_option+1]);
        char *token = strtok(tmp,"=");
        if(!strcmp(token,"limit"))return limitON;
        return timeON;
    }
    return timeON_limitON;
}

int wrong_int_test(char* str_test, int arg_occ)
{
    int i=0;
    char c;
    c=str_test[i];
    while(c!= '\0')
    {
        if(c > '9' || c < '0')
        {
            printf("Error: type passed in parameter %d is incorrect\n",arg_occ);
            printf("--> Excepted a int, argument <%s> is a type char*\n",str_test);
            return 0;
        }
        i++;
        c = str_test[i];
    }
    return 1;
}

int date_format_test(char* m_d, int arg_occ)
{
    char* token;
    char test[7];
    strcpy(test,m_d);
    size_t max_lenght = strlen(m_d); 
    token = strtok(test,"-");
    size_t lenght = strlen(token);
    if(lenght == max_lenght)
    {
        printf("Error: argument passed in position %d didn't respect format\n",arg_occ);
        printf("--> Excepted M-D, argument passed <%s> didn't have '-' separator\n",m_d);
        return 0;
    }
    return 1;
}

int time_test(int time,int arg_occ)
{
    if( time >= 10000)
    {
        printf("Error: argument passed in position %d is not a correct time\n",arg_occ);
        printf("--> Excepted a HHMM format,argument passed <%d> didn't respect that",time);
        return 0;
    }
    if( time%100 > 59 || time/100 > 23)
    {
        printf("Error: argument passed in position %d is not a correct time\n",arg_occ);
        printf("--> Excepted a hour between 0 and 23 and minute between 0 and 60,argument passed <%d> didn't respect that",time);
        return 0;
    }
    return 1;
}

int limit_test(int limit, int arg_occ)
{
    if(limit<0)
    {
        printf("Error: argument passed in position %d is not a correct limit\n",arg_occ);
        printf("--> Excepted a positive value,argument passed is a negative values");
        return 0;
    }
    return 1;
}

int day_and_month_valid_test(int M, int J, int arg_occ)
{
    if(J<1 || J>31)
	{
		printf("Error: argument passed in position %d is not a correct day\n",arg_occ);
        printf("--> Excepted a value between 1 and 31, argument passed is %d\n",J);
		return 0;
	}
	if(M<1 || M>12)
	{
		printf("Error: argument passed in position %d is not a correct day\n",arg_occ);
        printf("--> Excepted a value between 1 and 12, argument passed is %d\n",M);
		return 0;
	}
    return 1;
}