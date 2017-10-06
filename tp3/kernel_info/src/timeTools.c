#include "../includes/timeTools.h"

double get_sec(){
  const long minute = 60;
  const long hour = minute * 60;
  const long day = hour * 24;

  time_t tiempo = time(0);
  struct tm *hora = localtime(&tiempo);

  return ((hora->tm_mday*day) + (hora->tm_hour*hour) + (hora->tm_min*minute) + (hora->tm_sec));
}  

struct tm *sec_to_Time(double sec){
  long time_up;

  const long minute = 60;
  const long hour = minute * 60;
  const long day = hour * 24;

  time_t tiempo = time(0);
  struct tm *hora = localtime(&tiempo);
  time_up = (long)sec;

  hora->tm_year = (2000+(time_up/day));
  hora->tm_hour =((time_up % day) / hour);
  hora->tm_min = (time_up % hour) / minute;
  hora->tm_sec = time_up % minute;

  return hora;
}

void print_clock(struct tm * hora, char * txt, int index, FILE *f){
  char output[100];
  int errnum;
  if (index){
    hora->tm_year = 2016;
    errnum=strftime(output,50,"  %d/%m/%y  %H:%M:%S",hora);
   }
  else errnum=strftime(output,50,"%yD %X",hora);
  if (errnum == 0)
  {
    perror("Error en funcion print_clock");
    exit(EXIT_FAILURE);
  }
  //fprintf ( f, "%s%s\n",txt,output );
  fprintf(f, "<td> %s </td> \n",  output);
  fprintf(f, "</tr>\n");

  //printf("%s%s\n",txt,output);
}