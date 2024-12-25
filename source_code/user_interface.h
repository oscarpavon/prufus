#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include <gtk/gtk.h>

extern GtkWidget* selected_iso_label;
extern GtkWidget* disk_label;
extern GtkWidget* devices_drop_down;
extern GtkWidget *window;
extern GtkWidget *status_label;
extern GtkWidget *working_label;
extern GtkWidget *create_usb_button;
extern GtkWidget *choose_iso_button;
extern GtkWidget *cancel_button;

extern GtkAlertDialog *write_usb_warning;
extern GtkAlertDialog *success_alert;

void create_user_interface (GtkApplication *app, gpointer user_data);

#endif
