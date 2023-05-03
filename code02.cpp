// Creating calculator in cpp

#include <gtk/gtk.h>

// Callback function for the number buttons
void on_number_button_clicked(GtkButton* button, gpointer data) {
    // Get the label from the button
    const gchar* label = gtk_button_get_label(button);

    // Get the text from the entry
    GtkWidget* entry = GTK_WIDGET(data);
    const gchar* text = gtk_entry_get_text(GTK_ENTRY(entry));

    // Append the label to the text
    gchar* new_text = g_strdup_printf("%s%s", text, label);

    // Set the new text in the entry
    gtk_entry_set_text(GTK_ENTRY(entry), new_text);
}

// Callback function for the operator buttons
void on_operator_button_clicked(GtkButton* button, gpointer data) {
    // Get the label from the button
    const gchar* label = gtk_button_get_label(button);

    // Set the label as the operator in the data
    gpointer* operator_data = static_cast<gpointer*>(data);
    *operator_data = const_cast<gchar*>(label);

    // Get the text from the entry
    GtkWidget* entry = GTK_WIDGET(gpointer(*(operator_data + 1)));
    const gchar* text = gtk_entry_get_text(GTK_ENTRY(entry));

    // Save the current value in the data
    gpointer* value_data = static_cast<gpointer*>(data) + 2;
    *value_data = static_cast<gpointer>(g_ascii_strtod(text, NULL));

    // Clear the entry
    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

// Callback function for the equals button
void on_equals_button_clicked(GtkButton* button, gpointer data) {
    // Get the operator from the data
    gpointer* operator_data = static_cast<gpointer*>(data);
    const gchar* op = static_cast<const gchar*>(*operator_data);

    // Get the current value from the data
    gpointer* value_data = operator_data + 2;
    gdouble value = static_cast<gdouble>(*value_data);

    // Get the text from the entry
    GtkWidget* entry = GTK_WIDGET(gpointer(*(operator_data + 1)));
    const gchar* text = gtk_entry_get_text(GTK_ENTRY(entry));

    // Calculate the result
    gdouble result = 0.0;
    if (g_strcmp0(op, "+") == 0) {
        result = value + g_ascii_strtod(text, NULL);
    } else if (g_strcmp0(op, "-") == 0) {
        result = value - g_ascii_strtod(text, NULL);
    } else if (g_strcmp0(op, "*") == 0) {
        result = value * g_ascii_strtod(text, NULL);
    } else if (g_strcmp0(op, "/") == 0) {
        result = value / g_ascii_strtod(text, NULL);
    }

    // Set the result in the entry
    gchar* result_text = g_strdup_printf("%g", result);
    gtk_entry_set_text(GTK_ENTRY(entry), result_text);
}

int main(int argc, char** argv) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new window
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    // Create a vertical box container to hold widgets
    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create an entry for the input/output
    GtkWidget* entry = gtk_entry_new();
gtk_entry_set_alignment(GTK_ENTRY(entry), 1.0);
gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 0);

// Create a grid for the buttons
GtkWidget* grid = gtk_grid_new();
gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

// Create the number buttons
GtkWidget* button_1 = gtk_button_new_with_label("1");
gtk_grid_attach(GTK_GRID(grid), button_1, 0, 0, 1, 1);
g_signal_connect(button_1, "clicked", G_CALLBACK(on_number_button_clicked), entry);

GtkWidget* button_2 = gtk_button_new_with_label("2");
gtk_grid_attach(GTK_GRID(grid), button_2, 1, 0, 1, 1);
g_signal_connect(button_2, "clicked", G_CALLBACK(on_number_button_clicked), entry);

GtkWidget* button_3 = gtk_button_new_with_label("3");
gtk_grid_attach(GTK_GRID(grid), button_3, 2, 0, 1, 1);
g_signal_connect(button_3, "clicked", G_CALLBACK(on_number_button_clicked), entry);

GtkWidget* button_4 = gtk_button_new_with_label("4");
gtk_grid_attach(GTK_GRID(grid), button_4, 0, 1, 1, 1);
g_signal_connect(button_4, "clicked", G_CALLBACK(on_number_button_clicked), entry);

GtkWidget* button_5 = gtk_button_new_with_label("5");
gtk_grid_attach(GTK_GRID(grid), button_5, 1, 1, 1, 1);
g_signal_connect(button_5, "clicked", G_CALLBACK(on_number_button_clicked), entry);

GtkWidget* button_6 = gtk_button_new_with_label("6");
gtk_grid_attach(GTK_GRID(grid), button_6, 2, 1, 1, 1);
g_signal_connect(button_6, "clicked", G_CALLBACK(on_number_button_clicked), entry);

GtkWidget* button_7 = gtk_button_new_with_label("7");
gtk_grid_attach(GTK_GRID(grid), button_7, 0, 2, 1, 1);
g_signal_connect(button_7, "clicked", G_CALLBACK(on_number_button_clicked), entry);

GtkWidget* button_8 = gtk_button_new_with_label("8");
gtk_grid_attach(GTK_GRID(grid), button_8, 1, 2, 1, 1);
g_signal_connect(button_8, "clicked", G_CALLBACK(on_number_button_clicked), entry);

GtkWidget* button_9 = gtk_button_new_with_label("9");
gtk_grid_attach(GTK_GRID(grid), button_9, 2, 2, 1, 1);
g_signal_connect(button_9, "clicked", G_CALLBACK(on_number_button_clicked), entry);

GtkWidget* button_0 = gtk_button_new_with_label("0");
gtk_grid_attach(GTK_GRID(grid), button_0, 1, 3, 1, 1);
g_signal_connect(button_0, "clicked", G_CALLBACK(on_number_button_clicked), entry);

// Create the operator buttons
gchar* plus = "+";
gchar* minus = "-";
gchar* times = "*";
gchar* divide = "/";

gpointer operator_data[] = { static_cast<gpointer>(plus), static_cast<gpointer>(entry), static_cast<gpointer>(0) };

GtkWidget* button_plus = gtk_button_new_with_label(plus);
gtk_grid_attach(GTK_GRID(grid), button_plus, 3, 0, 1, 1);
g_signal_connect(button_plus, "clicked", G_CALLBACK(on_operator_button_clicked), operator_data);

operator_data[0] = static_cast<gpointer>(minus);

GtkWidget* button_minus = gtk_button_new_with_label(minus);
gtk_grid_attach(GTK_GRID(grid), button_minus, 3, 1, 1, 1);
g_signal_connect(button_minus, "clicked", G_CALLBACK(on_operator_button_clicked), operator_data);

operator_data[0] = static_cast<gpointer>(times);

GtkWidget* button_times = gtk_button_new_with_label(times);
gtk_grid_attach(GTK_GRID(grid), button_times, 3, 2, 1, 1);
g_signal_connect(button_times, "clicked", G_CALLBACK(on_operator_button_clicked), operator_data);

operator_data[0] = static_cast<gpointer>(divide);

GtkWidget* button_divide = gtk_button_new_with_label(divide);
gtk_grid_attach(GTK_GRID(grid), button_divide, 3, 3, 1, 1);
g_signal_connect(button_divide, "clicked", G_CALLBACK(on_operator_button_clicked), operator_data);

// Create the clear and equals buttons
GtkWidget* button_clear = gtk_button_new_with_label("C");
gtk_grid_attach(GTK_GRID(grid), button_clear, 0, 3, 1, 1);
g_signal_connect(button_clear, "clicked", G_CALLBACK(on_clear_button_clicked), entry);

GtkWidget* button_equals = gtk_button_new_with_label("=");
gtk_grid_attach(GTK_GRID(grid), button_equals, 2, 3, 1, 1);
g_signal_connect(button_equals, "clicked", G_CALLBACK(on_equals_button_clicked), entry);

// Show all widgets
gtk_widget_show_all(window);

// Run the main loop
gtk_main();

return 0;
}