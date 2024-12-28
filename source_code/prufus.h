#ifndef _PRUFUS_H_
#define _PRUFUS_H_

#include <gtk/gtk.h>

#define MAX_DISKS 10
#define MAX_PATH_LEN 128

typedef enum
{
    FORMAT = '1',
    TEMP,
    MOUNT,
    COPY,
    COPY_BIG,
    SYNC,
    CLEAN,
    SUCCESS,
}
stage_t;

void cancel(GtkWidget *widget, gpointer data);
void make_usb(GtkWidget *widget, gpointer data);
void choose_iso(GtkWidget *widget, gpointer data);

typedef struct MakeUSB{
  char* device;
  char iso_path[MAX_PATH_LEN];
} MakeUSB;

typedef struct Disk {
    char *device;
    char *name;
    char *size;
} Disk;


extern size_t disk_counter;

extern Disk disks[MAX_DISKS];
size_t get_usb_disks(void);

#endif
