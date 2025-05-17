#include "GTKHelpers.h"
#include <string>

// Global widgets
GtkWidget *main_window = NULL;
GtkWidget *current_content = NULL;

typedef struct {
    GtkWidget *id_entry;
    GtkWidget *name_entry;
    GtkWidget *year_entry;
} StudentFormData;


void load_css(void) {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    GError *error = NULL;
    gtk_css_provider_load_from_path(provider, "style.css", &error);
    if (error) {
        g_printerr("Error loading CSS file: %s\n", error->message);
        g_error_free(error);
    }

    g_object_unref(provider);
}
void refresh_content(GtkWidget *new_content) {
    if (current_content) {
        gtk_container_remove(GTK_CONTAINER(gtk_widget_get_parent(current_content)), current_content);
    }
    current_content = new_content;
    gtk_container_add(GTK_CONTAINER(main_window), current_content);
    gtk_widget_show_all(main_window);
}

void show_message(const gchar *title, const gchar *message) {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(main_window),
                                            GTK_DIALOG_MODAL,
                                            GTK_MESSAGE_INFO,
                                            GTK_BUTTONS_OK,
                                            "%s", message);
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

gboolean show_confirm_dialog(const gchar *title, const gchar *message) {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(main_window),
                                            GTK_DIALOG_MODAL,
                                            GTK_MESSAGE_QUESTION,
                                            GTK_BUTTONS_YES_NO,
                                            "%s", message);
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    return (response == GTK_RESPONSE_YES);
}

void show_main_menu() {
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *label = gtk_label_new("Student Database System");

    // Create buttons for each option
    GtkWidget *buttons[10];
    const gchar *button_labels[] = {
        "Add Student Data",
        "Get Database Size",
        "Read Student Data",
        "List All Student IDs",
        "Check ID Existence",
        "Delete Student Data",
        "Enter Student Marks",
        "Display Student Marks",
        "About",
        "Exit"
    };

    for (int i = 0; i < 10; i++) {
        buttons[i] = gtk_button_new_with_label(button_labels[i]);
        gtk_box_pack_start(GTK_BOX(vbox), buttons[i], FALSE, FALSE, 0);
    }

    // Connect signals
    g_signal_connect(buttons[0], "clicked", G_CALLBACK(show_add_entry_form), NULL);
    g_signal_connect(buttons[1], "clicked", G_CALLBACK(show_get_used_size), NULL);
    g_signal_connect(buttons[2], "clicked", G_CALLBACK(show_read_entry_form), NULL);
    g_signal_connect(buttons[3], "clicked", G_CALLBACK(show_id_list), NULL);
    g_signal_connect(buttons[4], "clicked", G_CALLBACK(show_check_id_form), NULL);
    g_signal_connect(buttons[5], "clicked", G_CALLBACK(show_delete_entry_form), NULL);
    g_signal_connect(buttons[6], "clicked", G_CALLBACK(show_enter_marks_form), NULL);
    g_signal_connect(buttons[7], "clicked", G_CALLBACK(show_display_marks_form), NULL);
    g_signal_connect(buttons[8], "clicked", G_CALLBACK(show_about_page), NULL);
    g_signal_connect(buttons[9], "clicked", G_CALLBACK(gtk_main_quit), NULL);

    refresh_content(vbox);
}
//menu buttons
/*--------1---------*/
void show_add_entry_form() {
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *hbox;  
    GtkWidget *label; 
    GtkWidget *entry_add_id, *entry_add_name, *entry_add_year;
    GtkWidget *button;

    // ID Entry
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    label = gtk_label_new("Student ID:      ");
    entry_add_id = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), entry_add_id, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(form), hbox, FALSE, FALSE, 0);

    // Name Entry
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    label = gtk_label_new("Student Name:");
    entry_add_name = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), entry_add_name, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(form), hbox, FALSE, FALSE, 0);

    // Year Entry
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    label = gtk_label_new("Student Year:   ");
    entry_add_year = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), entry_add_year, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(form), hbox, FALSE, FALSE, 0);

    // Save entries in form object data with new names
    g_object_set_data(G_OBJECT(form), "entry_add_id", entry_add_id);
    g_object_set_data(G_OBJECT(form), "entry_add_name", entry_add_name);
    g_object_set_data(G_OBJECT(form), "entry_add_year", entry_add_year);

    // Submit button
    button = gtk_button_new_with_label("Add Student");
    g_object_set_data(G_OBJECT(button), "form", form);
    g_signal_connect(button, "clicked", G_CALLBACK(on_add_student_submit), NULL);
    gtk_box_pack_start(GTK_BOX(form), button, FALSE, FALSE, 0);

    // Back button
    button = gtk_button_new_with_label("Back to Menu");
    g_signal_connect(button, "clicked", G_CALLBACK(show_main_menu), NULL);
    gtk_box_pack_start(GTK_BOX(form), button, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), form, FALSE, FALSE, 0);

    refresh_content(vbox);
}
/*--------2---------*/
void show_get_used_size() {
    uint32 size;
    SDB_GetUsedSize(listhead, &size);

    char message[100];
    snprintf(message, sizeof(message),
            "Number of students in the database: %u", size);

    show_message("Database Size", message);
}
/*--------3---------*/
void show_read_entry_form() {
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // ID Entry
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *label = gtk_label_new("Student ID:");
    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(form), hbox, FALSE, FALSE, 0);

    // Submit button
    GtkWidget *button = gtk_button_new_with_label("View Student");
    g_signal_connect(button, "clicked", G_CALLBACK(on_view_student_submit), NULL);
    g_object_set_data(G_OBJECT(button), "form", form);

    // Back button
    GtkWidget *back_button = gtk_button_new_with_label("Back to Menu");
    g_signal_connect(back_button, "clicked", G_CALLBACK(show_main_menu), NULL);

    gtk_box_pack_start(GTK_BOX(form), button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), form, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), back_button, FALSE, FALSE, 0);

    g_object_set_data(G_OBJECT(form), "id_entry", entry);
    refresh_content(vbox);
}
/*--------4---------*/
void show_id_list() {
    uint32 ids[100]; // Assuming max 100 students
    uint32 count = 0;

    if (!SDB_GetList(listhead, ids, &count)) {
        show_message("Information", "The database is empty");
        return;
    }

    GtkWidget *dialog = gtk_dialog_new_with_buttons("Student IDs",
                                                  GTK_WINDOW(main_window),
                                                  GTK_DIALOG_MODAL,
                                                  "Close",
                                                  GTK_RESPONSE_OK,
                                                  NULL);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *list = gtk_text_view_new();
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(list));

    gtk_text_view_set_editable(GTK_TEXT_VIEW(list), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(list), FALSE);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
                                 GTK_POLICY_AUTOMATIC,
                                 GTK_POLICY_AUTOMATIC);

    std::string id_list;
    for (uint32 i = 0; i < count; i++) {
        id_list += "ID " + std::to_string(i+1) + ": " + std::to_string(ids[i]) + "\n";
    }

    gtk_text_buffer_set_text(buffer, id_list.c_str(), -1);
    gtk_container_add(GTK_CONTAINER(scroll), list);
    gtk_box_pack_start(GTK_BOX(content_area), scroll, TRUE, TRUE, 0);
    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
/*--------5---------*/
void show_check_id_form() {
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // ID Entry
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *label = gtk_label_new("Student ID:");
    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(form), hbox, FALSE, FALSE, 0);

    // Check button
    GtkWidget *button = gtk_button_new_with_label("Check ID");
    g_signal_connect(button, "clicked", G_CALLBACK(on_check_id_submit), NULL);
    g_object_set_data(G_OBJECT(button), "form", form);

    // Back button
    GtkWidget *back_button = gtk_button_new_with_label("Back to Menu");
    g_signal_connect(back_button, "clicked", G_CALLBACK(show_main_menu), NULL);

    gtk_box_pack_start(GTK_BOX(form), button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), form, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), back_button, FALSE, FALSE, 0);

    g_object_set_data(G_OBJECT(form), "id_entry", entry);
    refresh_content(vbox);
}
/*--------6---------*/
void show_delete_entry_form() {
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // ID Entry
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *label = gtk_label_new("Student ID:");
    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(form), hbox, FALSE, FALSE, 0);

    // Delete button
    GtkWidget *button = gtk_button_new_with_label("Delete Student");
    g_signal_connect(button, "clicked", G_CALLBACK(on_delete_student_submit), NULL);
    g_object_set_data(G_OBJECT(button), "form", form);

    // Back button
    GtkWidget *back_button = gtk_button_new_with_label("Back to Menu");
    g_signal_connect(back_button, "clicked", G_CALLBACK(show_main_menu), NULL);

    gtk_box_pack_start(GTK_BOX(form), button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), form, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), back_button, FALSE, FALSE, 0);

    g_object_set_data(G_OBJECT(form), "id_entry", entry);
    refresh_content(vbox);
}
/*--------7---------*/
void show_enter_marks_form() {
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // ID Entry
    GtkWidget *hbox_id = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *label_id = gtk_label_new("Student ID:  ");
    GtkWidget *entry_id = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox_id), label_id, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_id), entry_id, TRUE, TRUE, 0);

    // Marks Entries
    GtkWidget *hbox_eng = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *label_eng = gtk_label_new("English Mark:");
    GtkWidget *entry_eng = gtk_entry_new();

    GtkWidget *hbox_ar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *label_ar = gtk_label_new("Arabic Mark: ");
    GtkWidget *entry_ar = gtk_entry_new();

    GtkWidget *hbox_math = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *label_math = gtk_label_new("Maths Mark: ");
    GtkWidget *entry_math = gtk_entry_new();

    // Pack all entries
    gtk_box_pack_start(GTK_BOX(hbox_eng), label_eng, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_eng), entry_eng, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(hbox_ar), label_ar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_ar), entry_ar, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(hbox_math), label_math, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_math), entry_math, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(form), hbox_id, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(form), hbox_eng, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(form), hbox_ar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(form), hbox_math, FALSE, FALSE, 0);

    // Submit button
    GtkWidget *button = gtk_button_new_with_label("Enter Marks");
    g_signal_connect(button, "clicked", G_CALLBACK(on_enter_marks_submit), NULL);
    g_object_set_data(G_OBJECT(button), "form", form);

    // Back button
    GtkWidget *back_button = gtk_button_new_with_label("Back to Menu");
    g_signal_connect(back_button, "clicked", G_CALLBACK(show_main_menu), NULL);

    gtk_box_pack_start(GTK_BOX(vbox), form, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), back_button, FALSE, FALSE, 0);

    // Store entry references
    g_object_set_data(G_OBJECT(form), "id_entry", entry_id);
    g_object_set_data(G_OBJECT(form), "english_entry", entry_eng);
    g_object_set_data(G_OBJECT(form), "arabic_entry", entry_ar);
    g_object_set_data(G_OBJECT(form), "maths_entry", entry_math);

    refresh_content(vbox);
}
/*--------8---------*/
void show_display_marks_form() {
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // ID Entry
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *label = gtk_label_new("Student ID:");
    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(form), hbox, FALSE, FALSE, 0);

    // View button
    GtkWidget *button = gtk_button_new_with_label("View Marks");
    g_signal_connect(button, "clicked", G_CALLBACK(on_display_marks_submit), NULL);
    g_object_set_data(G_OBJECT(button), "form", form);

    // Back button
    GtkWidget *back_button = gtk_button_new_with_label("Back to Menu");
    g_signal_connect(back_button, "clicked", G_CALLBACK(show_main_menu), NULL);

    gtk_box_pack_start(GTK_BOX(form), button, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), form, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), back_button, FALSE, FALSE, 0);

    g_object_set_data(G_OBJECT(form), "id_entry", entry);
    refresh_content(vbox);
}
/*--------9---------*/
void show_about_page() {
    const gchar *about_text =
        "The idea of the application is to enter student data (name, ID, etc.)\n"
        "and store it in a database. The user is allowed to modify this data,\n"
        "such as adding or deleting, and he can view this data.\n"
        "Developed by:\n"
        "  - Yasmine Bassem\n"
        "  - Youssef Samy\n"
        "  - Yahia Mohamed\n"
        "  - Marwa Abd Al-Nasser\n\n";

    show_message("About", about_text);
}