#ifndef GTK_HELPERS_H
#define GTK_HELPERS_H

#include <gtk/gtk.h>
#include "SDB.h"
#include "SDBAPP.h"

extern GtkWidget *main_window;
extern GtkWidget *current_content;

void load_css(void);
void refresh_content(GtkWidget *new_content);
void show_message(const gchar *title, const gchar *message);
gboolean show_confirm_dialog(const gchar *title, const gchar *message);

void show_main_menu();
void show_add_entry_form();
void show_get_used_size();
void show_read_entry_form();
void show_id_list();
void show_check_id_form();
void show_delete_entry_form();
void show_enter_marks_form();
void show_display_marks_form();
void show_about_page();
#endif // GTK_HELPERS_H
