
#include "user_interface.h"
#include "prufus.h"

GtkWidget* selected_iso_label;
GtkWidget* disk_label;
GtkWidget* devices_drop_down;
GtkWidget *window;
GtkWidget *status_label;
GtkWidget *working_label;
GtkWidget *create_usb_button;
GtkWidget *choose_iso_button;
GtkWidget *cancel_button;

GtkAlertDialog *write_usb_warning;
GtkAlertDialog *success_alert;

void create_user_interface(GtkApplication *app, gpointer user_data)
{
  GtkWidget *box;
  GtkWidget* title;
  GtkWidget* description;
  GtkWidget* header_box;
  GtkWidget* action_box;
  GtkWidget* select_iso_box;

  GtkWidget* select_iso_drop_down;

  GtkWidget* separator;

  
  GtkWidget* change_name; 

  GtkFileDialog* choose_iso_dialog;

  GtkFileFilter* iso_filter = gtk_file_filter_new();
  gtk_file_filter_add_suffix(iso_filter, "iso");

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "prufus");
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 650);

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
  gtk_widget_set_halign (box, GTK_ALIGN_FILL);
  gtk_widget_set_valign (box, GTK_ALIGN_FILL);
  gtk_widget_set_hexpand(box,FALSE);

  header_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign (header_box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (header_box, GTK_ALIGN_CENTER);

  action_box= gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign (action_box, GTK_ALIGN_END);
  gtk_widget_set_valign (action_box, GTK_ALIGN_START);
  gtk_widget_set_vexpand(action_box,TRUE);

  select_iso_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_halign (select_iso_box, GTK_ALIGN_FILL);
  gtk_widget_set_valign (select_iso_box, GTK_ALIGN_FILL);


  
  separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);


  choose_iso_dialog = gtk_file_dialog_new();
  gtk_file_dialog_set_default_filter(choose_iso_dialog,iso_filter);

  select_iso_drop_down = gtk_drop_down_new(NULL, NULL);
  gtk_drop_down_set_factory(GTK_DROP_DOWN(select_iso_drop_down), NULL);

  selected_iso_label = gtk_label_new("None .iso selected");
  
  status_label = gtk_label_new("Nothing to do");
  
  //disk_label = gtk_label_new(buffer_disk_name);

  //create UI
  create_usb_button = gtk_button_new_with_label ("Create bootable USB");
  choose_iso_button = gtk_button_new_with_label ("Select .iso");

  cancel_button = gtk_button_new_with_label ("Cancel");
  gtk_widget_set_sensitive(cancel_button, FALSE);//disabled on start

  title = gtk_label_new("prufus");
  PangoAttrList *const Attrs = pango_attr_list_new();
  PangoAttribute *const SizeAttr = pango_attr_size_new(40 * PANGO_SCALE);
  pango_attr_list_insert(Attrs, SizeAttr);
  gtk_label_set_attributes((GtkLabel*)title,Attrs);

  description = gtk_label_new("Create bootable USB from .iso images");
  
  GtkStringList *list = gtk_string_list_new(NULL);
  for (size_t i = 0; i < disk_counter; ++i) {
    char text[128] = {0};
    snprintf(text, 128, "%s %s %s", disks[i].device, disks[i].name, disks[i].size);
    gtk_string_list_append(list, text);
  }
  devices_drop_down = gtk_drop_down_new(G_LIST_MODEL(list), NULL);

  g_signal_connect (cancel_button, "clicked", G_CALLBACK (cancel), NULL);
  g_signal_connect (create_usb_button, "clicked", G_CALLBACK (make_usb), NULL);
  g_signal_connect (choose_iso_button, "clicked", G_CALLBACK (choose_iso), choose_iso_dialog);
  
  gtk_box_append (GTK_BOX (box), header_box);

  gtk_box_append (GTK_BOX (header_box), title);
  gtk_box_append (GTK_BOX (header_box), description);
  gtk_box_append (GTK_BOX (action_box), create_usb_button);
  
  gtk_box_append (GTK_BOX (select_iso_box), choose_iso_button);
  gtk_box_append (GTK_BOX (select_iso_box), selected_iso_label);

  gtk_box_append (GTK_BOX (box), select_iso_box);

  
  GtkWidget* box_disk = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0); 
  
  GtkWidget* separator_disk1 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  GtkWidget* box_disk_label = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); 
  gtk_box_append (GTK_BOX (box_disk_label), separator_disk1);

  //gtk_box_append (GTK_BOX (box_disk_label), disk_label);
  GtkWidget* separator_disk2 = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_box_append (GTK_BOX (box_disk_label), separator_disk2);


  GtkWidget* disk_button = gtk_button_new_with_label("Change destination USB");
  //gtk_box_append (GTK_BOX (box_disk), disk_button);
  gtk_box_append (GTK_BOX (box_disk), box_disk_label);


  gtk_box_append (GTK_BOX (box), box_disk);
  gtk_box_append (GTK_BOX (box), devices_drop_down);

  //gtk_box_append (GTK_BOX (box), select_iso_drop_down);
  gtk_box_append (GTK_BOX (box), action_box);
  
  GtkWidget* status_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
  gtk_widget_set_halign (status_box, GTK_ALIGN_FILL);
  gtk_widget_set_valign (status_box, GTK_ALIGN_END);

  GtkWidget* status_label_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_valign (status_label_box, GTK_ALIGN_FILL);
  gtk_widget_set_halign (status_label_box, GTK_ALIGN_FILL);

  GtkWidget* cancel_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign (cancel_box, GTK_ALIGN_END);
  gtk_widget_set_valign (cancel_box, GTK_ALIGN_END);
  

  working_label = gtk_label_new("");//empty

  gtk_box_append (GTK_BOX (status_label_box), status_label);
  gtk_box_append (GTK_BOX (status_label_box), working_label);
  
  gtk_box_append (GTK_BOX (status_box), cancel_box);

  gtk_box_append (GTK_BOX (cancel_box), cancel_button);
  
  gtk_box_append (GTK_BOX (status_box), status_label_box);

  gtk_box_append (GTK_BOX (box), status_box);

  
  gtk_window_set_child (GTK_WINDOW (window), box);

  gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

  //success dialog
  
  success_alert = gtk_alert_dialog_new("Success, now you can disconnect your USB!");


  gtk_window_present (GTK_WINDOW (window));
}
