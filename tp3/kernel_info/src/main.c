#include "../includes/print_fromProc.h"
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/*#include "../includes/kernel_info.h"
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>*/
void print_man();
const char * options = {"sl: :"}; 

int main (int argc, char ** argv){

/*  FILE *f = fopen ( "./info-kernel.txt", "w" );
  if ( f == NULL )
  {
    printf ( "Error opening file!\n" );
    exit ( 1 );
  }*/

  //save_kernel_info_2_file(f);
  int i;
  int opt;
  int rep = 0;

  FILE *f = fopen ( "../archivos/info-kernel.txt", "w" );
  if ( f == NULL )
  {
    printf ( "Error opening file!\n" );
    exit ( 1 );
  }
  print_header(f);
  print_model_type(f);
  print_kernel_version(f);
  print_meminfo(f);
  print_uptime(f);
  /*print_file_sys_count(f);*/

  fclose(f);
  

 //

  //print_model_type();  

  //print_kernel_version();

  //print_uptime();
  
 // print_file_sys_count();
  
  while((opt = getopt(argc, argv, options)) != -1){
    {

      switch(opt){
        case('s'):
        print_stat();    

        break;
        case('l'):

        rep = atoi(argv[optind++])/atoi(optarg);

        for (i = 0; i < rep; i++){
          print_diskstat();
          //print_meminfo();
          print_loadavg();
          if (i!=rep-1)sleep(atoi(optarg));
        }
        
        break;
        case '?':
        if (optopt == 'l')
          fprintf (stderr, "La opcion -l requiere al menos 2 argumentos\n");
        else print_man();
        return EXIT_FAILURE;
        default:
        break;  
      }
    }
  }
  
  return EXIT_SUCCESS;
}

void print_man(){
  printf("%s\n","Ksamp: permite mostrar de diferentes formas un conjunto de informacion disponible en el directorio /proc " );
  printf("%s\n","Las siguientes opciones eligen la informacion a mostrar:" );
  printf("\t %s\n","-s \t --estadisticas \t \t" );
  printf("\t %s\n","-l \t --estado de disco y memoria: El comando ksamp -l a b imprime repetidamente la informacion cada a segundos; esto se repite hasta que hayan pasado b segundos." );

}
