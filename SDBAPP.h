#ifndef _SDBAPP_H
#define _SDBAPP_H

#include "GTKHelpers.h"
#include "platform_types.h"
#include <string>
#include<iostream>
void init_restore_data();

void on_add_student_submit(GtkWidget *widget, gpointer data);
void on_delete_student_submit(GtkWidget *widget, gpointer data);
void on_view_student_submit(GtkWidget *widget, gpointer data);
void on_enter_marks_submit(GtkWidget *widget, gpointer data);
void on_check_id_submit(GtkWidget *widget, gpointer data);
void on_display_marks_submit(GtkWidget *widget, gpointer data);


#endif // _SDBAPP_H
