#include<gtk/gtk.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
// #include <conio.h>
#include <sys/stat.h>

static void create_directory (GtkWidget *widget, gint response_id, gpointer data)
{
    GtkEntry* entry = data;
    const gchar *entrydata;
    char *basepath = g_get_home_dir();
    entrydata = gtk_entry_get_text(entry);
    printf("\nentrydata: %s", entrydata);
    printf("\ng_get_home_dir(): %s",g_get_home_dir());
    strcat(basepath,"/");
    strcat(basepath,entrydata);
    int check = mkdir(basepath,0777);
    printf("\ncheck: %d",check);
    if(check>=0){
        printf("\nnew Direcory %s created!\n",entrydata);
    } else {
        printf("\nfailed to create a new directory\n");
    }

    gtk_widget_destroy (widget); // This will close the dialog
}

static void call_create_directory (GtkWidget *widget, gpointer data)
{
    GtkWidget *window = data;
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *button;
    static GtkEntry *textbox;

    dialog = gtk_dialog_new_with_buttons ("Create a new Directory", window, GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_OK, NULL);
    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (content_area), grid);

    label = gtk_label_new("Directory path: ");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    textbox = gtk_entry_new();
    gtk_entry_set_text(textbox, "");
    gtk_grid_attach(GTK_GRID(grid), textbox, 1, 0, 1, 1);

    gtk_widget_show_all (dialog);
    g_signal_connect (GTK_DIALOG (dialog), "response", G_CALLBACK (create_directory), textbox);
}

static void create_file (GtkWidget *widget, gint response_id, gpointer data)
{
    FILE *fp;
    GtkEntry* entry = data;
    const gchar *entrydata;
    char *basepath = g_get_home_dir();
    entrydata = gtk_entry_get_text(entry);
    printf("\nentry() : %s", gtk_entry_get_text(entry));
    printf("\nentrydata: %s", entrydata);
    printf("\nentry: %s",entry);
    printf("\ng_get_home_dir(): %s",g_get_home_dir());
    strcat(basepath,"/");
    strcat(basepath,entrydata);
    printf("\ncreateFile: %s",basepath);
    fp  = fopen (basepath, "w");

    gtk_widget_destroy (widget); // This will close the dialog
}

static void call_create_file (GtkWidget *widget, gpointer data)
{
    GtkWidget *window = data;
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *button;
    static GtkEntry *textbox;

    dialog = gtk_dialog_new_with_buttons ("Create a new File", window, GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_OK, NULL);
    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (content_area), grid);

    label = gtk_label_new("File path: ");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    textbox = gtk_entry_new();
    gtk_entry_set_placeholder_text(textbox, "enter filename");
    gtk_entry_set_text(textbox, "");
    gtk_grid_attach(GTK_GRID(grid), textbox, 1, 0, 1, 1);

    gtk_widget_show_all (dialog);
    g_signal_connect (GTK_DIALOG (dialog), "response", G_CALLBACK (create_file), textbox);
}

static void view_folders(GtkWidget* button, gpointer window)
{
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Browse Files & Folders", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_widget_show_all(dialog);
//  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),"/");
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    printf("\n before GTK_FILE_CHOOSER call");
    printf("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    printf("\n after GTK_FILE_CHOOSER call");
    //gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(dialog), g_get_home_dir());
    if(resp == GTK_RESPONSE_OK){
        printf("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
        //gtk_file_chooser_get_create_folders (
        g_print("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
        g_print("%s\n", gtk_file_chooser_get_create_folders(GTK_FILE_CHOOSER(dialog)));
    }
    else
        g_print("You pressed Cancel\n");
    gtk_widget_destroy(dialog);
}


static void activate (GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *entry;
    GtkWidget *grid;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "File Explorer Application");
    gtk_container_set_border_width (GTK_CONTAINER (window), 100);

    grid = gtk_grid_new ();
    gtk_container_add (GTK_CONTAINER (window), grid);

    button1 = gtk_button_new_with_label ("Create new directory");
    g_signal_connect (button1, "clicked", G_CALLBACK (call_create_directory), window);
    gtk_grid_attach (GTK_GRID (grid), button1, 0, 1, 1, 1);

    button2 = gtk_button_new_with_label ("Create new file");
    g_signal_connect (button2, "clicked", G_CALLBACK (call_create_file), window);
    gtk_grid_attach (GTK_GRID (grid), button2, 1, 1, 1, 1);

    button3 = gtk_button_new_with_label ("View Directories and Files");
    g_signal_connect (button3, "clicked", G_CALLBACK (view_folders), window);
    gtk_grid_attach (GTK_GRID (grid), button3, 0, 0, 1, 1);

    gtk_widget_show_all (window);
}

int main (int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("os.project", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}