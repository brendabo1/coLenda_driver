#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define MAX_LINE_SIZE 256

int main() {

    FILE *fd;
    char line[MAX_LINE_SIZE];
    char *driver_name = "colenda_driver";
    int major = 0;
    char string[200];
    

    system("insmod Driver/colenda_driver.ko");
    usleep(5000000);

    fd = fopen("/proc/devices", "r");

    if(fd == NULL) {
        printf("erro ao abrir arquivo\n");
        return -1;
    }

    while(fgets(line, sizeof(line), fd)){
        if(strstr(line, driver_name) != NULL){
            sscanf(line, "%d %s", &major, driver_name);
            break;
        }
    }

    sprintf(string, "mknod /dev/colenda c %d 0", major);

    system(string);
    


    return 0;
}
