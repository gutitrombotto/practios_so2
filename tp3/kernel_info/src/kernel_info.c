#include "../includes/print_fromProc.h"


void save_kernel_info_2_file(FILE *f)
{


  /*FILE *f = fopen ( "./info-kernel.txt", "w" );
  if ( f == NULL )
  {
    printf ( "Error opening file!\n" );
    exit ( 1 );
  }*/
  print_header(f);
  print_model_type(f);  
  print_kernel_version(f);
  print_meminfo(f);
  print_uptime(f);
  /*print_file_sys_count(f);*/

  fclose(f);

  return;

}