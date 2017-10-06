#include "../includes/get_fromProc.h"

double proc_uptime (const char * buffer){ 
  int errnum;
  /*file_open((char*)"/proc/uptime", buffer); */
  double uptime;
  errnum=sscanf(buffer," %500lf",&uptime);

  if (errnum == EOF)
  {
    perror("Error en funcion proc_uptime");
    exit(EXIT_FAILURE);
  }
  return uptime;
}

void proc_model_type(const char * buffer, struct CPU * cpu){        //SEPARAR!!!//
  cpu->model = string_parse(buffer,(char*)"model name",':');
  cpu->type = string_parse(buffer,(char*)"vendor_id",' ');
}

double proc_init_time(const char * buffer){
  double seconds = get_sec();
  return seconds - proc_uptime(buffer);
}

void proc_cpu_times(const char * buffer, struct proc_stats * p_stat){
  int errnum;
  errnum=sscanf(buffer,"cpu %500e %*e %500e %500e",&p_stat->time_user,&p_stat->time_sys,&p_stat->time_idle);
  p_stat->time_idle=p_stat->time_idle/100;
  p_stat->time_user=p_stat->time_user/100;
  p_stat->time_sys=p_stat->time_sys/100;

  if (errnum == EOF)
  {
    perror("Error en funcion proc_cpu_times");
    exit(EXIT_FAILURE);
  }
  
}   

void proc_stat(const char * buffer, struct proc_stats * p_stat){
  proc_cpu_times(buffer, p_stat);
  
  p_stat->n_proc = string_parse(buffer,(char*)"processes",' ');
  p_stat->ctxt = string_parse(buffer,(char*)"ctxt",' ');
}

void proc_kernel_version(const char * buffer, struct CPU * cpu){
  
  char * version;
  const char tok[2]= "(";

  version = strstr ((char *)buffer, "version");

  strtok(version,tok); /* obtengo la linea */
  cpu->kernel_version=(char *)memchr(version,' ',strlen(version));

  if (cpu->kernel_version == NULL)
  {
    perror("Error en funcion proc_kernel_version");
    exit(EXIT_FAILURE);
  }

}

void proc_header(const char * host, struct header * hdr){
  time_t tiempo = time(0);
  hdr->time_now = localtime(&tiempo);
  hdr-> hostname = (char *)host;
}

int proc_file_sys_count(const char * buffer){
  const char s[2] = "\n"; 
  char *token;
  int count=0;

  token = strtok((char *)buffer, s);
  while(token != NULL){
      count = count + 1;
      token = strtok(NULL,s);
  }
  if (count==0)
  {
    perror("Error en funcion proc_file_sys_count");
    exit(EXIT_FAILURE);
  }
  return count;
}

void proc_diskstat (const char * buffer, struct mem_disk * md){
  int n_read  = 0;
  int n_write = 0;
  int errnum;
  buffer =  strstr(buffer,"sda");
  errnum=sscanf(buffer,"sda %500i %*i %*i %*i %500i",&n_read,&n_write);
  if (errnum == EOF)
  {
    perror("Error en funcion proc_diskstat");
    exit(EXIT_FAILURE);
  }
  md->disk_rw = n_read + n_write;
}

void proc_meminfo  (const char * buffer, struct mem_disk * md){

  int errnum, errnum2;
  errnum=sscanf(strstr(buffer,"MemTotal"),"MemTotal: %500i", &md->mem_total);
  errnum2=sscanf(strstr(buffer,"MemFree"), "MemFree:  %500i", &md->mem_free);

  if (errnum == EOF || errnum2 == EOF)
  {
    perror("Error en funcion proc_meminfo");
    exit(EXIT_FAILURE);
  }
}

void proc_loadavg  (const char * buffer, struct mem_disk * md){

  int errnum;
  errnum = sscanf(buffer,"%500f",&md->load_min);  
  if (errnum == EOF)
  {
    perror("Error en funcion proc_loadavg");
    exit(EXIT_FAILURE);
  }
}