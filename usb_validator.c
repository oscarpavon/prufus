#include <string.h>
#include "prufus.h"

#include "scripts_names.h"

char buffer_disks_info[60*10];

char buffer_disk_name[128];

Disk valid_disks[10];

Disk disks[10];

void get_string(int type){
    char buffer[256];
    memset(buffer,0,sizeof(buffer));
    int counter = 0;
    int local_disk_counter = 0;

    
    int offset = 0;
    for(int i = 0 ; ;i++){
      if(buffer_disk_name[i] == '\0')
        break;
      if(buffer_disk_name[i] != '\n'){
        buffer[counter] = buffer_disk_name[i];
        counter++; 
      }else {
        if(type == NAME){
          memcpy(disks[local_disk_counter].name, buffer, counter);
          offset += counter;
        }else if(type == DEVICE){
          memcpy(disks[local_disk_counter].device, buffer, counter);
        }else if(type == SIZE){
          memcpy(disks[local_disk_counter].size, buffer, counter);
        }
        local_disk_counter++;
        if(type == DEVICE_COUNT){
          disk_counter++;
        }
        counter = 0;
      }
    }
  
}

void get_string_from_file(FILE *script_file) {
  memset(buffer_disk_name, 0, sizeof(buffer_disk_name));
  char buffer[128];
  memset(buffer,0,sizeof(buffer));
  int offset = 0;
  while (fgets(buffer, sizeof(buffer), script_file) !=
         NULL) {

    int len = strlen(buffer);
    memcpy(&buffer_disk_name[offset], buffer, len);
    offset += len;
  }
  
}

void get_usb_disks(){
    FILE *script_file;
    script_file = popen(get_devices_names_script, "r");

    get_string_from_file(script_file); 
    get_string(NAME);

    pclose(script_file);
  

    script_file = popen(get_devices_script, "r");

    get_string_from_file(script_file); 
    get_string(DEVICE);
    pclose(script_file);

    script_file = popen(get_devices_size_script, "r");

    get_string_from_file(script_file); 
    get_string(SIZE);

    get_string(DEVICE_COUNT);

    pclose(script_file);
     

    for(int i = 0; i< disk_counter; i++){
      printf("%s %s %s\n",disks[i].name, disks[i].size, disks[i].device);
    }
    
    //filters disks
    int valid_disks_counter = 0;
    bool has_m2 = false;

    for(int i = 0; i< disk_counter; i++){
      if(strncmp(disks[i].device, "/dev/nv",7) == 0){
        has_m2 = true;
      }
    }
    
    memset(&valid_disks,0,sizeof(valid_disks));


    //if has m2 disk we suppose we have USBs in /dev/sd* unless some other SATA disk
    if (has_m2) {

      for (int i = 0; i < disk_counter; i++) {
        if (strncmp(disks[i].device, "/dev/sd", 7) == 0) {
          Disk* valid_disk = &disks[i];
          memcpy(&valid_disks[valid_disks_counter], valid_disk, sizeof(Disk));
          valid_disks_counter++;
          printf("Valid disk: %s\n",disks[i].device); 
        }
      }
    }else{//if not has m2 we suppose the main disk it's /dev/sda
      for (int i = 0; i < disk_counter; i++) {
        if (strncmp(disks[i].device, "/dev/sda", 8) == 0) {
		continue;
        }
        Disk* valid_disk = &disks[i];
        memcpy(&valid_disks[valid_disks_counter], valid_disk, sizeof(Disk));
        valid_disks_counter++;
        printf("Valid disk: %s\n",disks[i].device); 
      }
    }

    printf("Valid disks %d\n",valid_disks_counter); 

    for(int i = 0; i< valid_disks_counter; i++){
      printf("%s %s %s\n",valid_disks[i].name, 
          valid_disks[i].size, valid_disks[i].device);
    }

    disk_counter = valid_disks_counter;

    int offset = 0;
    for(int i = 0; i < disk_counter; i++){
      sprintf(buffer_disks_info+offset, "%s %s", valid_disks[i].name,valid_disks[i].size);
      offset += DISKS_INFO_OFFSET;
    }


}
