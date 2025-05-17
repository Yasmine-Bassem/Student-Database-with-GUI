
#include "SDBAPP.h"
#include "repository.h"

// Global student database head pointer
student *listhead = NULL;


// the main menu buttons
void on_main_menu_button_clicked(GtkWidget *widget, gpointer data) {
    int choice = GPOINTER_TO_INT(data);

    switch(choice) {
        case 1: show_add_entry_form(); break;
        case 2: show_get_used_size(); break;
        case 3: show_read_entry_form(); break;
        case 4: show_id_list(); break;
        case 5: show_check_id_form(); break;
        case 6: show_delete_entry_form(); break;
        case 7: show_enter_marks_form(); break;
        case 8: show_display_marks_form(); break;
        case 9: show_about_page(); break;
        case 0: gtk_main_quit(); break;//built-in function
        default: break;
    }
}

void init_restore_data(){

    //load cache
    repo_restore(&listhead);
}

// adding a student
void on_add_student_submit(GtkWidget *widget, gpointer data) {
    GtkWidget *form = (GtkWidget*)g_object_get_data(G_OBJECT(widget), "form");
    GtkWidget *entry_add_id = (GtkWidget*)g_object_get_data(G_OBJECT(form), "entry_add_id");
    GtkWidget *entry_add_name = (GtkWidget*)g_object_get_data(G_OBJECT(form), "entry_add_name");
    GtkWidget *entry_add_year = (GtkWidget*)g_object_get_data(G_OBJECT(form), "entry_add_year");

    uint32 id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_add_id)));
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(entry_add_name));
    uint32 year = atoi(gtk_entry_get_text(GTK_ENTRY(entry_add_year)));

    if (id == 0 || strlen(name) == 0 || year == 0) {
        show_message("Error", "Please fill in all fields with valid data");
        return;
    }
    for (int i = 0; name[i] != '\0'; i++) {
        if (g_ascii_isdigit(name[i])) {
            show_message("Error", "Name should not contain numbers");
            return;
        }
    }
    if(year<1 || year >5){
        show_message("Error", "Please Enter Student's Year Correctly");
        return;
    }

     if (SDB_AddEntry(&listhead, id, name, year)) {
        show_message("Success", "Student added successfully!");
        show_main_menu();
    }
}


// Signal handler for deleting a student
void on_delete_student_submit(GtkWidget *widget, gpointer data) {
    GtkWidget *form = (GtkWidget*)g_object_get_data(G_OBJECT(widget), "form");
    GtkWidget *id_entry = (GtkWidget*)g_object_get_data(G_OBJECT(form), "id_entry");
    uint32 id = atoi(gtk_entry_get_text(GTK_ENTRY(id_entry)));

    if (id == 0) {
        show_message("Error", "Please enter a valid student ID");
        return;
    }

    if (show_confirm_dialog("Confirm Delete", "Are you sure you want to delete this student?")) {
        if (SDB_DeletEntry(&listhead, id)) {
            show_message("Success", "Student deleted successfully!");
        } else {
            show_message("Error", "Student not found!");
        }
    }
    show_main_menu();
}

//for viewing student details
void on_view_student_submit(GtkWidget *widget, gpointer data) {
    GtkWidget *form = (GtkWidget*)g_object_get_data(G_OBJECT(widget), "form");
    GtkWidget *id_entry = (GtkWidget*)g_object_get_data(G_OBJECT(form), "id_entry");
    uint32 id = atoi(gtk_entry_get_text(GTK_ENTRY(id_entry)));

    if (id == 0) {
        show_message("Error", "Please enter a valid student ID");
        return;
    }

    student result;
    if (SDB_ReadEntry(listhead, id, &result)) {
        char message[512];
        snprintf(message, sizeof(message),
                "Student Details:\n\n"
                "ID: %u\n"
                "Name: %s\n"
                "Year: %u\n"
                "English: %u\n"
                "Arabic: %u\n"
                "Maths: %u\n"
                "Total: %u",
                result.Student_ID,
                result.Student_Name,
                result.Student_year,
                result.English,
                result.Arabic,
                result.Maths,
                result.Total);

        show_message("Student Information", message);
    } else {
        show_message("Error", "Student not found!");
    }
}

//entering marks
void on_enter_marks_submit(GtkWidget *widget, gpointer data) {
    GtkWidget *form = (GtkWidget*)g_object_get_data(G_OBJECT(widget), "form");
    GtkWidget *id_entry = (GtkWidget*)g_object_get_data(G_OBJECT(form), "id_entry");
    GtkWidget *english_entry = (GtkWidget*)g_object_get_data(G_OBJECT(form), "english_entry");
    GtkWidget *arabic_entry = (GtkWidget*)g_object_get_data(G_OBJECT(form), "arabic_entry");
    GtkWidget *maths_entry = (GtkWidget*)g_object_get_data(G_OBJECT(form), "maths_entry");

    uint32 id = atoi(gtk_entry_get_text(GTK_ENTRY(id_entry)));
    uint32 english = atoi(gtk_entry_get_text(GTK_ENTRY(english_entry)));
    uint32 arabic = atoi(gtk_entry_get_text(GTK_ENTRY(arabic_entry)));
    uint32 maths = atoi(gtk_entry_get_text(GTK_ENTRY(maths_entry)));

    if (id == 0) {
        show_message("Error", "Please enter a valid student ID");
        return;
    }
    if(english>100 || english<0 ||arabic>100 || arabic<0 ||maths>100||maths<0){
        show_message("Error", "Please enter  valid Degrees");
        return;
    }
    if (EnterMarks(&listhead, id, english, arabic, maths)) {
        show_message("Success", "Marks entered successfully!");
        show_main_menu();
    } else {
        show_message("Error", "Student not found!");
    }
}

// for checking id existence
void on_check_id_submit(GtkWidget *widget, gpointer data) {
    GtkWidget *form = (GtkWidget*)g_object_get_data(G_OBJECT(widget), "form");
    GtkWidget *id_entry = (GtkWidget*)g_object_get_data(G_OBJECT(form), "id_entry");
    uint32 id = atoi(gtk_entry_get_text(GTK_ENTRY(id_entry)));

    if (id == 0) {
        show_message("Error", "Please enter a valid student ID");
        return;
    }

    if (SDB_IsIdExist(listhead, id)) {
        show_message("ID Check", "Student ID exists in the database");
    } else {
        show_message("ID Check", "Student ID does not exist");
    }
}




void on_display_marks_submit(GtkWidget *widget, gpointer data) {
    GtkWidget *form = (GtkWidget*)g_object_get_data(G_OBJECT(widget), "form");
    GtkWidget *id_entry = (GtkWidget*)g_object_get_data(G_OBJECT(form), "id_entry");
    uint32 id = atoi(gtk_entry_get_text(GTK_ENTRY(id_entry)));

    uint32 english, arabic, maths, total;
    char name[MAX_NAME_LENGTH];
    uint32 year;

    if (DisplayMarks(listhead, id, &english, &arabic, &maths, &total, name, &year)) {
        char message[512];
        snprintf(message, sizeof(message),
                "Student: %s\nYear: %u\n\n"
                "English: %u\nArabic: %u\nMaths: %u\n\n"
                "Total: %u",
                name, year, english, arabic, maths, total);
        show_message("Student Marks", message);
    } else {
        show_message("Error", "Student not found!");
    }
}
