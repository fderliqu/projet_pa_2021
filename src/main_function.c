#include"../includes/init.h"
#include"../includes/main_function.h"
#include "../includes/show-airport.h"
#include "../includes/show-airlines.h"
#include "../includes/show-flights.h"
#include "../includes/avg-flight-duration.h"
#include "../includes/find-initerary.h"
#include "../includes/most-delayed-flights.h"
#include "../includes/most_delayed_airlines.h"
#include "../includes/most-delayed-airlines-at-airport.h"
#include"../includes/delayed-airline-airline_id.h"
#include"../includes/changed-flights.h"
#include"../includes/quit.h"

int dichotomie(char *l_fct[max_function_lenght], char fct[max_function_lenght])
{
    int first = 0;
    int last = nb_function-1;
    int mid;
    int compare;
    while (first <= last)
    {
        mid = (first+last)/2;
        compare = strncmp(fct,l_fct[mid],max_function_lenght);
        if (compare == 0)return mid;
        if (compare > 0)first = mid+1;
        else last = mid-1;
    }
    return -1;
}

void launch_function(struct line_arguments liste, struct cellule_airport *HT_main[max_Hairport],struct cellule_compagnieDATA *HT_comp_data[max_Hdatacomp])
{
  char *l_fct[nb_function] = {"avg-flight-duration",
                              "changed-flights",
                              "delayed-airline",
                              "find-itinerary",
                              "find-multicity-itinerary",
                              "most-delayed-airlines",
                              "most-delayed-airlines-at-airport",
                              "most-delayed-flights",
                              "quit",
                              "show-airlines",
                              "show-airports",
                              "show-flights",
  };
  /*
  void (*functions[nb_function])(struct line_arguments) = {
    &(init_avg_flight_duration),
    &(init_changed_flight),
    &(init_delayed_airline),
    &(init_find_itinerary),
    &(init_find_multicity_itinerary),
    &(init_most_delayed_airlines),
    &(init_most_delayed_airlines_at_airport),
    &(init_most_delayed_flights),
    &(init_quit),
    &(init_show_airlines),
    &(init_show_airports),
    &(init_show_flights),
  };
  */
  int index = dichotomie(l_fct,liste.arg[0]);
  //*(functions[index])(arg);
  switch (index){
    case 0: init_avg_flight_duration(liste,HT_main); break;
    case 1: init_changed_flights(liste,HT_main); break;
    case 2: init_delayed_airlines(liste,HT_main); break;
    case 3: init_find_itinerary(liste,HT_main); break;

    case 5: init_most_delayed_airlines(liste,HT_main,HT_comp_data); break;
    case 6: init_show_most_delayed_airline_at_airport(liste,HT_main,HT_comp_data) ; break;
    case 7: init_most_delayed_flights(liste,HT_main); break;
    case 8: quit(HT_main,HT_comp_data);return; break;
    case 9: init_show_airlines(liste,HT_main,HT_comp_data); break;
    case 10: init_show_airport(liste,HT_main); break;
    case 11: init_show_flights(liste,HT_main); break;
    default:    
        printf("Error: Can't find the function %s \n",liste.arg[0]);
        break;
    }
}