 #include "../includes/print_fromProc.h"

char buffer[MAX_BUFFER];
char temp_buffer[20];
char temp_buffer2[20];
struct CPU temp_cpu;
struct header hdr;
struct proc_stats p_stat; 
struct mem_disk md;


const char * datos_sistema_table[] = {
  "  <div class=\"panel panel-primary\">",
  "<div class=\"panel-heading\">",
  "Datos del Sistema",
  "</div>",
  "<div class=\"panel-body\">",
  " <table class=\"table\">",
  "<thead>",
  "<tr>",
  "<th> Hostname </th>",
  "<th> Fecha y Hora </th>",
  "</tr>",
  "</thead>",
  "<tbody>",
  NULL
};

const char * info_kernel_table[] = {
  "  <div class=\"panel panel-primary\">",
  "<div class=\"panel-heading\">",
  "Informacion del Kernel",
  "</div>",
  "<div class=\"panel-body\">",
  " <table class=\"table\">",
  "<thead>",
  "<tr>",
  "<th> Modelo y Tipo CPU </th>",
  "<th> Version de Kernel </th>",
  "</tr>",
  "</thead>",
  "<tbody>",
  NULL
};

const char * info_memoria_table[] = {
  "  <div class=\"panel panel-primary\">",
  "<div class=\"panel-heading\">",
  "Informacion de la Memoria",
  "</div>",
  "<div class=\"panel-body\">",
  " <table class=\"table\">",
  "<thead>",
  "<tr>",
  "<th> Memoria Total del Sistema </th>",
  "<th> Memoria Libre </th>",
  "</tr>",
  "</thead>",
  "<tbody>",
  NULL
};
const char * end_of_table[] = {
  "</tbody>",
  "</table>",
  "</div>",
  "</div>",
  NULL
};
const char * uptime_table[] = {
  "  <div class=\"panel panel-primary\">",
  "<div class=\"panel-heading\">",
  "Uptime",
  "</div>",
  "<div class=\"panel-body\">",
  " <table class=\"table\">",
  "<thead>",
  "<tr>",
  "<th> Tiempo transcurrido desde que se inicio el SO </th>",
  "</tr>",
  "</thead>",
  "<tbody>",
  NULL
};

void print_cte_to_file(const char * to_print[], FILE *f)
{
  for (int i = 0; to_print[i] != NULL; ++i)
  {
    fprintf(f,"%s", to_print[i]);

  }

  return;
}

void print_uptime (FILE *f){

  file_open((char*)"/proc/uptime", buffer);
  print_cte_to_file(uptime_table, f);

  print_clock((struct tm *)sec_to_Time(proc_uptime(buffer)),(char *)"Tiempo transcurrido desde que se inicio el SO: ",0, f);
  print_cte_to_file(end_of_table, f);
}

void print_model_type(FILE *f){


  file_open((char*)"/proc/cpuinfo", buffer);
  proc_model_type(buffer,&temp_cpu);
  print_cte_to_file(info_kernel_table, f);
  fprintf(f, "<tr>\n");
  fprintf(f, "<td> %s %s </td> \n",  temp_cpu.model, temp_cpu.type);
  
  //fprintf ( f, "Modelo y Tipo CPU: %s(%s)\n",temp_cpu.model ,temp_cpu.type );

  //printf("Modelo y Tipo CPU: %s(%s)\n",temp_cpu.model ,temp_cpu.type);
} 

void print_initTime(){
	file_open((char*)"/proc/uptime", buffer);
    //print_clock((struct tm *)sec_to_Time(proc_init_time(buffer)),(char *)"Hora en que se inicio el SO:",1);
}

void print_stat(){
	printf("%s\n","------------------------------------------------------" );
	file_open((char*)"/proc/stat", buffer);
  proc_stat(buffer, &p_stat);
  num_to_norm(atoi(p_stat.ctxt),temp_buffer2);
  printf("%s %s\n","Cantidad de cambios de contexto: ", temp_buffer2);
  num_to_norm(atoi(p_stat.n_proc),temp_buffer2);

  printf("%s %s\n","Número de procesos creados desde el inicio del sistema:", temp_buffer2);

    //print_clock((struct tm *)sec_to_Time(p_stat.time_user),(char *)"Tiempo de CPU utilizado para usuarios: ",0);
    //print_clock((struct tm *)sec_to_Time(p_stat.time_sys),(char *)"Tiempo de CPU utilizado para sistema: ",0);
    //print_clock((struct tm *)sec_to_Time(p_stat.time_idle),(char *)"Tiempo de CPU utilizado para proceso idle: ",0);

  print_initTime();
  printf("%s\n","------------------------------------------------------" );
}

void print_kernel_version(FILE *f){
	file_open((char*)"/proc/version", buffer);
 proc_kernel_version(buffer,& temp_cpu);
 fprintf(f, "<td> %s </td> \n", temp_cpu.kernel_version);
 fprintf(f, "</tr>\n");
 print_cte_to_file(end_of_table,f);
 //fprintf ( f, "Version de Kernell: %s \n",temp_cpu.kernel_version );

    //printf("Version de Kernell: %s \n",temp_cpu.kernel_version);
}

void print_header(FILE *f){

	file_open((char*)"/proc/sys/kernel/hostname", buffer);
	//printf("%s\n", "------------------------------------------------------");
  //fprintf ( f, "%s\n", "------------------------------------------------------" );
  proc_header(buffer,&hdr);

  print_cte_to_file(datos_sistema_table, f);
  fprintf(f, "<tr>\n");
  fprintf(f, "<td> %s </td> \n",  hdr.hostname);
  print_clock(hdr.time_now,(char *)"[DATE & TIME]",1, f);
  //fprintf ( f, "[HOSTNAME] %s", hdr.hostname );

    //printf("[HOSTNAME] %s", hdr.hostname );
  print_cte_to_file(end_of_table,f);
  //fprintf ( f, "%s\n", "------------------------------------------------------" );

  	//printf("%s\n","------------------------------------------------------" );
}

void print_file_sys_count(){
	file_open((char*)"/proc/filesystems", buffer);
 printf("Cantidad de sistemas de archivo soportados por kernell: %i\n", proc_file_sys_count(buffer));
}

void print_diskstat (){
	printf("%s\n","------------------------------------------------------" );
	file_open((char *) "/proc/diskstats", buffer);
  proc_diskstat(buffer,&md);
  num_to_norm(md.disk_rw,temp_buffer2);
  printf("%s : %s\n","Numero de Peticiones al disco",temp_buffer2);
}

void print_meminfo  (FILE *f){
	file_open((char *) "/proc/meminfo", buffer);
  proc_meminfo(buffer,&md);
  num_to_norm(md.mem_total,temp_buffer2);
  num_to_norm(md.mem_free,temp_buffer);

  print_cte_to_file(info_memoria_table, f);
  fprintf(f, "<tr>\n");
  fprintf(f, "<td> %s </td> \n",  temp_buffer2);
  fprintf(f, "<td> %s </td> \n",  temp_buffer);
  print_cte_to_file(end_of_table,f);

  //fprintf ( f, "%s %sB \n%s %sB\n","Memoria Total del Sistema:",temp_buffer2,"Memoria Libre:",temp_buffer );

  //printf("%s %sB \n%s %sB\n","Memoria Total del Sistema:",temp_buffer2,"Memoria Libre:",temp_buffer); 
}

void print_loadavg  (){
	file_open((char *) "/proc/loadavg", buffer);
  proc_loadavg(buffer,&md);
  printf("Carga promedio en el último minuto: %.2f\n", md.load_min);
  printf("%s\n","------------------------------------------------------" );
}
