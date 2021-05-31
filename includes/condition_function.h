//test sur le nombres de paramètres
int number_parameter_test(struct line_arguments, int,int);

//test sur la longueur des parametres
int lenght_parameter_test(struct line_arguments, size_t, int);

//builder de mask limit et time
char build_mask_time_limit(struct line_arguments, int);

//test si le char* est bien un int avant conversion de celui ci
int wrong_int_test(char*, int);

//test validité day format
int date_format_test(char*, int);

//time test
int time_test(int,int);

//limit test
int limit_test(int, int);

//test validité jour et mois
int day_and_month_valid_test(int, int, int);


