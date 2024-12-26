#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "glib.h"
#include "gtk/gtk.h"
#include "user_interface.h"

bool can_update_status = true;

bool can_update_working_status = true;

bool success = false;

#define SUCCESS '8'
#define DEPENDENCIES '2'
#define ERROR 'e'

void set_working_label(char* working){
  gtk_label_set_text(GTK_LABEL(working_label),working);
}

void update_working_label(){
  while(can_update_working_status == true){
    set_working_label(".");
    usleep(500000) ;
    set_working_label("..");
    usleep(500000) ;
    set_working_label("....");
    usleep(500000) ;
    set_working_label("......");
    usleep(500000) ;
  }
  set_working_label("");
}

void set_status_text(char* status){
  gtk_label_set_text(GTK_LABEL(status_label), status);
}

void update_status_finish(GObject *source_object, GAsyncResult *res, gpointer user_data){

  can_update_status = false;
  can_update_working_status = false;

  
  if(success == true){
    gtk_alert_dialog_show(success_alert,GTK_WINDOW(window));
  }
}

void update_status(){
  
  can_update_working_status = true;

  GTask* working_task = g_task_new(NULL,NULL,NULL,NULL);
  g_task_run_in_thread(working_task,update_working_label);
  
  usleep(500000); // wait for status file
  while (can_update_status == true) {
    int status_file_descriptor = open("/tmp/prufus/status", O_RDONLY);
    if (status_file_descriptor == -1) {
      g_print("Error open status file\n");
      perror("Status:");
    }
    char status;
    read(status_file_descriptor, &status, 1);//we read one byte or character
    close(status_file_descriptor);
    
    switch (status) {
    case SUCCESS: {
      can_update_status = false;
      can_update_working_status = false;
      success = true;
      set_status_text("prufus installed");
      break;
    }
    case DEPENDENCIES: {
      set_status_text("Installing dependencies");
      break;
    }
    case ERROR: {
      set_status_text("ERROR");
      can_update_status = false;
      can_update_working_status = false;
      return;
      
      break;
    }
    }
  }
  g_print("Finish status update\n");
}


void install_prufus(GtkWidget *widget, gpointer data)
{

    GError *error_open = NULL;
    char *make_usb_command[] = {"./install.sh", NULL};
    
    char* current_directory = g_get_current_dir();

    char *environment[] = {NULL};
    gboolean result = g_spawn_async(
        current_directory, make_usb_command, environment, 
        G_SPAWN_SEARCH_PATH | G_SPAWN_CHILD_INHERITS_STDIN,
        NULL, NULL, NULL, &error_open);
    if (!result) {
      if (error_open != NULL) {
        g_print("Error %s\n", error_open->message);
        g_error_free(error_open);
      }
    }
    can_update_status = true; 
    success = false;
    GTask* update_status_task = g_task_new(NULL,NULL,update_status_finish,NULL);
    g_task_run_in_thread(update_status_task,update_status);


}

int main(int arguments_count, char **arguments_value)
{
  GtkApplication *prufus_application;

  int status;

  prufus_application = 
    gtk_application_new ("org.gtk.prufus_installer", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(prufus_application, "activate", 
      G_CALLBACK (create_user_interface), NULL);

  status = g_application_run(G_APPLICATION (prufus_application), 
      arguments_count, arguments_value);

  g_object_unref (prufus_application);

  return status;
}

