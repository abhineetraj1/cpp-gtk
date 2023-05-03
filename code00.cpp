#include <gtk/gtk.h>

int main(int argc, char* argv[])
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Abhineet Raj");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    // Create the label
    GtkWidget* label = gtk_label_new("Hello World");
    gtk_container_add(GTK_CONTAINER(window), label);

    // Show the window and start the main loop
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}