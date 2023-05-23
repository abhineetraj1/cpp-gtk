#include <gtk/gtk.h>

// Game state variables
enum Player { PLAYER_NONE, PLAYER_X, PLAYER_O };
enum Player current_player = PLAYER_X;
enum Player board[3][3] = { { PLAYER_NONE, PLAYER_NONE, PLAYER_NONE },{ PLAYER_NONE, PLAYER_NONE, PLAYER_NONE },{ PLAYER_NONE, PLAYER_NONE, PLAYER_NONE } };
// Function to check if a player has won
enum Player check_winner() {
    // Check rows
    for (int row = 0; row < 3; row++) {
        if (board[row][0] != PLAYER_NONE &&
            board[row][0] == board[row][1] &&
            board[row][0] == board[row][2]) {
            return board[row][0];
        }
    }
    // Check columns
    for (int col = 0; col < 3; col++) {
        if (board[0][col] != PLAYER_NONE &&
            board[0][col] == board[1][col] &&
            board[0][col] == board[2][col]) {
            return board[0][col];
        }
    }
    // Check diagonals
    if (board[0][0] != PLAYER_NONE &&
        board[0][0] == board[1][1] &&
        board[0][0] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] != PLAYER_NONE &&
        board[0][2] == board[1][1] &&
        board[0][2] == board[2][0]) {
        return board[0][2];
    }
    // No winner
    return PLAYER_NONE;
}

// Function to handle button clicks
void button_clicked(GtkButton *button, gpointer user_data) {
    int row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "row"));
    int col = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "col"));
    if (board[row][col] != PLAYER_NONE) {
        // The cell is already occupied
        return;
    }
    // Update the game state
    board[row][col] = current_player;
    // Set the button label
    const char *player_label = (current_player == PLAYER_X) ? "X" : "O";
    gtk_button_set_label(button, player_label);
    // Check if there is a winner
    enum Player winner = check_winner();
    if (winner != PLAYER_NONE) {
        // Disable all buttons
        GtkWidget *grid = GTK_WIDGET(gtk_widget_get_parent(GTK_WIDGET(button)));
        GList *buttons = gtk_container_get_children(GTK_CONTAINER(grid));
        while (buttons != NULL) {
            GtkWidget *btn = buttons->data;
            gtk_widget_set_sensitive(btn, FALSE);
            buttons = buttons->next;
        }
        // Show a message box with the winner
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"%s wins!", (winner == PLAYER_X) ? "Player X" : "Player O");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        // Reset the game state
        current_player = PLAYER_X;
        memset(board, PLAYER_NONE, sizeof(board));
        buttons = gtk_container_get_children(GTK_CONTAINER(grid));
        while (buttons != NULL) {
            GtkWidget *btn = buttons->data;
            gtk_button_set_label(GTK_BUTTON(btn), "");
            gtk_widget_set_sensitive(btn, TRUE);
            buttons = buttons->next;
        }
    } else {
        // Switch to the next player
        current_player = (current_player == PLAYER_X) ? PLAYER_O : PLAYER_X;
    }
}

// Function to create the game window
void create_game_window() {
    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Tic Tac Toe");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Create the grid
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(window), grid);
    // Create the buttons
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            GtkWidget *button = gtk_button_new();
            gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
            // Store the row and column as button data
            g_object_set_data(G_OBJECT(button), "row", GINT_TO_POINTER(row));
            g_object_set_data(G_OBJECT(button), "col", GINT_TO_POINTER(col));
            // Connect the clicked signal
            g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), NULL);
        }
    }
    // Show all widgets
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    create_game_window();
    gtk_main();
    return 0;
}