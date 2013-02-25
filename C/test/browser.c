// compile with (under vim)
// !gcc -std=c99 -Ofast `pkg-config --cflags --libs gtk+-3.0 webkitgtk-3.0` % -o %:r
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>

static void on_exit (GtkWidget *widget, gpointer data) {
    printf("on Exit!\n");
    exit(0);
};

int main (int argc, char *argv[]) {
    char *url = "http://www.google.com";
    gtk_init(&argc, &argv);

    GtkWidget *web_view = webkit_web_view_new();
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_exit), NULL);
    gtk_window_set_default_size(GTK_WINDOW (window), 680, 480);

    gtk_container_add (GTK_CONTAINER (window), web_view);

    gtk_widget_show_all(window);

    webkit_web_view_open(WEBKIT_WEB_VIEW(web_view), url);

    gtk_main();

    return 0;
}
