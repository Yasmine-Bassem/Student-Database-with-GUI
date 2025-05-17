#include <gtk/gtk.h>
#include "GTKHelpers.h"
#include "SDB.h"
#include "SDBAPP.h"

int main(int argc, char *argv[]) {


    gtk_init(&argc, &argv);
    load_css();
    // Create main window
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_window), "Student Database System");
    gtk_window_set_default_size(GTK_WINDOW(main_window), 600, 400);
    gtk_container_set_border_width(GTK_CONTAINER(main_window), 10);
    //for logo
    gtk_window_set_icon_from_file(GTK_WINDOW(main_window), "logo.PNG", NULL);

    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    init_restore_data();

    // Show main menu
    show_main_menu();

    gtk_widget_show_all(main_window);
    gtk_main();

    return 0;
}
