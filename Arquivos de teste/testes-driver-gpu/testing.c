#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(int argc, char const *argv[])
{

  char buffer[5] = "12345";
  
  printf("%d\n%d",sizeof(buffer), strlen(buffer));
  return 0;
}
