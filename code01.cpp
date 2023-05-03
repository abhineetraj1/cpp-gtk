#include <gtk/gtk.h>

// Callback function for the "Hello" button
void on_hello_button_clicked(GtkButton* button, gpointer data) {
    g_print("Hello, World!\n");
}

int main(int argc, char** argv) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK App");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Create a vertical box container to hold widgets
    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a label
    GtkWidget* label = gtk_label_new("Welcome to my GTK app!");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    // Create a button
    GtkWidget* button = gtk_button_new_with_label("Hello");
    g_signal_connect(button, "clicked", G_CALLBACK(on_hello_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // Create a check button
    GtkWidget* check_button = gtk_check_button_new_with_label("Check me!");
    gtk_box_pack_start(GTK_BOX(vbox), check_button, FALSE, FALSE, 0);

    // Create a radio button group
    GtkWidget* radio_button1 = gtk_radio_button_new_with_label(NULL, "Option 1");
    GtkWidget* radio_button2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_button1), "Option 2");
    GtkWidget* radio_button3 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_button2), "Option 3");
    gtk_box_pack_start(GTK_BOX(vbox), radio_button1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), radio_button2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), radio_button3, FALSE, FALSE, 0);

    // Create a combo box
    GtkWidget* combo_box = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Option 1");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Option 2");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Option 3");
    gtk_box_pack_start(GTK_BOX(vbox), combo_box, FALSE, FALSE, 0);

    // Create a text entry
    GtkWidget* entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    // Show the window and all its contents
    gtk_widget_show_all(window);

    // Start the main event loop
    gtk_main();

    return 0;
}