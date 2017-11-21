#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_number(char prompt[], char ** buffer, size_t *buffer_s)
{
  int truth;
  int i;
  truth = 0;
  while(!truth)
    {
      printf("%s\n", prompt);
      getline(buffer, buffer_s, stdin);
      for(i = 0 ; i < *buffer_s - 2; i++)
        {
          if( (*buffer)[i] >= '0' || (*buffer)[i] <= '9')
            truth = 1;
          else
            truth = 0;
        }
    }
  i = strlen(*buffer);
  (*buffer)[i - 1] = '^';
  (*buffer)[i] = '\0';
}
int main(int argc, char *args[])
{
  FILE *file;
  char *buffer;
  size_t buffer_s = 32;
  file = fopen("/dev/ttyUSB0", "r+");
  buffer = (char *)malloc(buffer_s * sizeof(char));
  while(1)
    {
      if(argc > 1)
        {
          fprintf( file, args[1]);
          printf("Command mode used.\n");
          break;
        }
      printf(" ////////////////////////////////////////\n");
      printf(" Any kepress works as well.\n 0 for red.\n 1 for blue.\n 2 for green.\n 4 for color set.\n q to quit.\n");
      getline(&buffer, &buffer_s, stdin);
      fprintf( file, buffer);
      system("/bin/stty cooked");
      if(buffer[0]== 'q')
        {
          break;
        }
      if(buffer[0] == '4')
        {
          for(int i = 0 ; i < buffer_s; i++)
            {
              buffer[i] = 0;
            }
          get_number("Set R value:", &buffer, &buffer_s);
          printf("Writing %s\n", buffer);
          fprintf( file, buffer);
          for(int i = 0 ; i < buffer_s; i++)
            {
              buffer[i] = 0;
            }
          get_number("Set G value:", &buffer, &buffer_s);
          printf("Writing %s\n", buffer);
          fprintf( file, buffer);
          for(int i = 0 ; i < buffer_s; i++)
            {
              buffer[i] = 0;
            }
          get_number("Set B value:", &buffer, &buffer_s);
          printf("Writing %s\n", buffer);
          fprintf( file, buffer);
        }
    }
  fclose(file);
  return 0;
}
