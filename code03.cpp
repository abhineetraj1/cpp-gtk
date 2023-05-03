#include <gtk/gtk.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

// Update the clock label with the current time
gboolean update_clock(gpointer data)
{
    // Get the clock label widget
    GtkWidget* label = static_cast<GtkWidget*>(data);

    // Get the current time
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Format the time string
    strftime(buffer, sizeof(buffer), "%I:%M:%S %p", timeinfo);
    string time_str(buffer);

    // Update the label
    gtk_label_set_text(GTK_LABEL(label), time_str.c_str());

    // Return true to keep the function running
    return true;
}

int main(int argc, char* argv[])
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Clock");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 300, 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    // Create the clock label
    GtkWidget* label = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(label), "<span font_desc='48'>00:00:00 AM</span>");
    gtk_container_add(GTK_CONTAINER(window), label);

    // Start updating the clock label
    g_timeout_add_seconds(1, update_clock, label);

    // Show the window and start the main loop
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
