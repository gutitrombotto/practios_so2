#include "../includes/tools.h"

void file_open(const char* path, char * buffer){

  FILE* fp;
  size_t bytes_read;

  memset(buffer, 0, MAX_BUFFER);  /*limpio el buffer*/  
  fp = fopen (path, "r");
  if (fp == NULL) {

      int errnum;
      errnum = errno;
      fprintf(stderr, "Value of errno: %d\n", errno);
      perror("Error en funcion file_open");
      fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
      exit(EXIT_FAILURE);
   }
   else {
      bytes_read = fread (buffer, 1, MAX_BUFFER, fp);
      fclose (fp); 
   }
  
  if (bytes_read == 0 || bytes_read == sizeof (buffer)){ 
    printf("%s\n","Error de lectura, no se puedo completar el buffer" );
    exit(EXIT_FAILURE);
  }

}

char* string_parse(const char * buffer,char * string, int ch){
  char * output;
  const char tok[2]= "\n";
  
  output =strstr((char*)buffer, string);
  
  
  strtok(output,tok);
  output = strchr(strrchr(output,ch),' ');

  if (output == NULL) {
    printf("%s\n", "Error en parseo no se encontro la palabra buscada");
    exit(EXIT_FAILURE);
  }
  return output;
}

void num_to_norm(const int num, char result[20]){
  float num2=num;
  int errnum;
  memset(result, 0, 20);
  

  if (num >1000 && num < 1000000){
    num2=num/1000.0;
    errnum=sprintf(result,"%1.3fK",num2);
  }
  else if (num >1000000){
    num2=num/1000000.0;
    errnum=sprintf(result,"%1.3fG",num2);
  }
  else
    errnum=sprintf(result,"%1.3f",num2);
  if (errnum < 0)
  {
    perror("Error en funcion num_to_norm");
    exit(EXIT_FAILURE);
  }
}
