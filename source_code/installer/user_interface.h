#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include <gtk/gtk.h>

extern GtkWidget *window;
extern GtkWidget *status_label;
extern GtkWidget *working_label;
extern GtkWidget *install_button;

extern GtkAlertDialog *success_alert;

void create_user_interface (GtkApplication *app, gpointer user_data);

#endif
