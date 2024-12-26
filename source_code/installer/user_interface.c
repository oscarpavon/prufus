
#include "user_interface.h"
#include "install.h"

GtkWidget *window;
GtkWidget *status_label;
GtkWidget *working_label;
GtkWidget *install_button;

GtkAlertDialog *success_alert;

void create_user_interface(GtkApplication *app, gpointer user_data)
{
  GtkWidget *main_box;
  GtkWidget* title;
  GtkWidget* description;
  GtkWidget* header_box;
  GtkWidget* installer_description_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "prufus Installer");
  gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);

  main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
  gtk_widget_set_halign (main_box, GTK_ALIGN_FILL);
  gtk_widget_set_valign (main_box, GTK_ALIGN_FILL);

  header_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign (header_box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (header_box, GTK_ALIGN_CENTER);

  installer_description_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 15);
  gtk_widget_set_halign (installer_description_box, GTK_ALIGN_START);
  gtk_widget_set_valign (installer_description_box, GTK_ALIGN_START);
  gtk_widget_set_vexpand(installer_description_box,TRUE);

  GtkWidget* body_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
  gtk_widget_set_halign(body_box,GTK_ALIGN_FILL);
  gtk_widget_set_valign(body_box,GTK_ALIGN_FILL);

  GtkWidget* logo = gtk_image_new_from_file("../../logo.png");
  gtk_widget_set_halign(logo,GTK_ALIGN_FILL);
  gtk_widget_set_valign(logo,GTK_ALIGN_FILL);
  gtk_widget_set_vexpand(logo,TRUE);
  gtk_widget_set_hexpand(logo,TRUE);
  

  title = gtk_label_new("prufus");
  PangoAttrList *const Attrs = pango_attr_list_new();
  PangoAttribute *const SizeAttr = pango_attr_size_new(40 * PANGO_SCALE);
  pango_attr_list_insert(Attrs, SizeAttr);
  gtk_label_set_attributes((GtkLabel*)title,Attrs);

  description = gtk_label_new("Installer");

  status_label = gtk_label_new("Press install to begin the installation");
  
  install_button = gtk_button_new_with_label ("Install");
  

  GtkWidget* description_pad = gtk_label_new(" ");
  GtkWidget* description1 = gtk_label_new("Welcome to prufus installer");
  GtkWidget* description2 = gtk_label_new("prufus it's a program for create a bootable USB from .iso images");
  gtk_widget_set_halign (description2, GTK_ALIGN_START);

  GtkWidget* description3 = gtk_label_new("You will have an icon in your desktop after the installation finished");

  gtk_widget_set_halign (description3, GTK_ALIGN_START);
  GtkWidget* description4 = gtk_label_new("A window for enter your password will be appear after you press the install button");
  gtk_widget_set_halign (description4, GTK_ALIGN_START);
  GtkWidget* description5 = gtk_label_new("Select your GNU/Linux distribution");
  gtk_widget_set_halign (description5, GTK_ALIGN_START);

  gtk_box_append (GTK_BOX (installer_description_box), description_pad);
  gtk_box_append (GTK_BOX (installer_description_box), description1);
  gtk_box_append (GTK_BOX (installer_description_box), description2);
  gtk_box_append (GTK_BOX (installer_description_box), description3);
  gtk_box_append (GTK_BOX (installer_description_box), description4);
  gtk_box_append (GTK_BOX (installer_description_box), description5);

  GtkWidget* distribution1 = gtk_check_button_new_with_label("Linux Mint");
  
  gtk_box_append (GTK_BOX (installer_description_box), distribution1);

  gtk_box_append(GTK_BOX(body_box), logo);
  gtk_box_append(GTK_BOX(body_box), installer_description_box);

  g_signal_connect (install_button, "clicked", G_CALLBACK (install_prufus), NULL);
  
  gtk_box_append (GTK_BOX (header_box), title);
  gtk_box_append (GTK_BOX (header_box), description);

  gtk_box_append (GTK_BOX (main_box), header_box);

  
  gtk_box_append (GTK_BOX (main_box), body_box);
  
  GtkWidget* status_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 20);
  gtk_widget_set_halign (status_box, GTK_ALIGN_FILL);
  gtk_widget_set_valign (status_box, GTK_ALIGN_END);

  GtkWidget* status_label_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_valign (status_label_box, GTK_ALIGN_FILL);
  gtk_widget_set_halign (status_label_box, GTK_ALIGN_FILL);

  GtkWidget* install_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_halign (install_box, GTK_ALIGN_END);
  gtk_widget_set_valign (install_box, GTK_ALIGN_END);

  working_label = gtk_label_new("");//empty

  gtk_box_append (GTK_BOX (status_label_box), status_label);
  gtk_box_append (GTK_BOX (status_label_box), working_label);
  
  gtk_box_append (GTK_BOX (install_box), install_button);

  gtk_box_append (GTK_BOX (status_box), install_box);

  gtk_box_append (GTK_BOX (status_box), status_label_box);

  gtk_box_append (GTK_BOX (main_box), status_box);

  
  gtk_window_set_child (GTK_WINDOW (window), main_box);

  gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

  //success dialog
  
  success_alert = gtk_alert_dialog_new("prufus installed successfully, you have an icon in your desktop");


  gtk_window_present (GTK_WINDOW (window));
}
