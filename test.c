#include"./librairie/init.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
  FILE *fd = fopen("./data/flights.csv","r");
  if(fd!=NULL)
    {
      printf("fichier ouvert\n");
      
      struct vol vol;
      char str[200];
      for(int j=0;j<4;j++)
	{
	  if(j==0){
	    fscanf(fd,"%s",str);
	  }
	  else{
	    fscanf(fd,"%d,%d,%d,%s,%s,%d,%f,%f,%d,%d,%f,%hd,%hd",
		   &vol.MONTH,
		   &vol.DAY,
		   &vol.WEEKDAY,
		   vol.ORG_AIR,
		   vol.DEST_AIR,
		   &vol.SCHED_DEP,
		   &vol.DEP_DELAY,
		   &vol.AIR_TIME,
		   &vol.DIST,
		   &vol.SCHED_ARR,
		   &vol.ARR_DELAY,
		   &vol.DIVERTED,
		   &vol.CANCELLED);
	    printf("%d ,%d ,%d ,%s ,%s ,%d ,%f ,%f ,%d ,%d ,%f ,%hd ,%hd \n",vol.MONTH,vol.DAY,vol.WEEKDAY,vol.ORG_AIR,vol.DEST_AIR,vol.SCHED_DEP,vol.DEP_DELAY,vol.AIR_TIME,vol.DIST,vol.SCHED_ARR,vol.ARR_DELAY,vol.DIVERTED,vol.CANCELLED);
	  }
	}
      /*
      char str[200];
      fscanf(fd,"%s",str);
      char * strtoken;
      for(int i=0;i<5;i++)
	{
	  strtoken = strtok(str,",");
	  while(strtoken!=NULL)
	    {
	      printf("%s,",strtoken);
	      strtoken = strtok(NULL,",");
	    }
	  fscanf(fd,"%s",str);
	  printf("\n");
	  }
      */
      fclose(fd);
    }
  else
    {
      printf("non\n");
    }
  
}
