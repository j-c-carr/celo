/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+
#+     Jonathan Colaco Carr
#+     jonathan.colacocarr@mail.mcgill.ca
#+
#+ This program is free software; you can redistribute it and/or modify
#+ it under the terms of the GNU General Public License as published by
#+ the Free Software Foundation; either version 2 of the License, or
#+ (at your option) any later version.
#+
#+ This program is distributed in the hope that it will be useful,
#+ but WITHOUT ANY WARRANTY; without even the implied warranty of
#+ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#+ GNU General Public License for more details.
#+
#+ You should have received a copy of the GNU General Public License
#+ along with this program; if not, write to the Free Software
#+ Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#+
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <gdk/gdkkeysyms.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <sys/mman.h>

// Put after the others.. for now
#include "tags.h"
#include "events.h"
#include "todos.h"
#include "welcome.h"



// Make them global
GtkWidget	*cmdTitleEntry;
GtkWidget	*cmdAddButton;
GtkWidget	*cmdColor;

GtkWidget	*datePicker;
GtkWidget	*welcome;
GtkWidget   *calendar1;

GtkWidget	*window;
GtkWidget   *listbox1; 
GtkWidget   *listbox2; 
GtkWidget   *lb2_entry[50];
GtkWidget   *lb2_row[50];

GtkWidget   *lb_title[1000]; // change these to calloc on file open
GtkWidget   *lb_date[1000];
GtkWidget   *lb_box[1000];
GtkLabel   *lb_entry[1000];
GtkListBoxRow   *lb_row[1000];

GtkBuilder	*builder; 

#define MAX_TITLE_SIZE 256
#define TODO_SIZE 256

GtkLabel tmpLabel;
GtkListBoxRow tmpRow;


void		on_destroy (); 
void        css_set (GtkCssProvider *cssProvider, GtkWidget *g_widget);

char* MONTH[12] = {"Jan.", "Feb.", "Mar.", "Apr.", "May", "Jun.", "Jul.",\
                    "Aug", "Sep.", "Nov.", "Dec."};

char	tmp[1024]; // general use

int	row;

// Load the view files AFTER the data files
#include "eventslistbox.h"
#include "todoslistbox.h"
#include "commandbar.h"
#include "customcss.h"
#include "calendar.h"

// Loaded last
#include "keypress.h"

int main(int argc, char *argv[]) 
{

	gtk_init(&argc, &argv); // init Gtk

//---------------------------------------------------------------------
// establish contact with xml code used to adjust widget settings
//---------------------------------------------------------------------
 
	builder = gtk_builder_new_from_file ("celo-dev.glade");
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);
    g_signal_connect (window, "key_press_event", G_CALLBACK(on_key_press), NULL);


    // Grid
	listbox1 = GTK_WIDGET(gtk_builder_get_object(builder, "listbox1"));
	listbox2 = GTK_WIDGET(gtk_builder_get_object(builder, "listbox2"));

	calendar1 = GTK_WIDGET(gtk_builder_get_object(builder, "calendar1"));
	welcome = GTK_WIDGET(gtk_builder_get_object(builder, "welcome"));
	cmdTitleEntry = GTK_WIDGET(gtk_builder_get_object(builder, "cmdTitleEntry"));
	cmdAddButton = GTK_WIDGET(gtk_builder_get_object(builder, "cmdAddButton"));
	cmdColor = GTK_WIDGET(gtk_builder_get_object(builder, "cmdColor"));
	datePicker = GTK_WIDGET(gtk_builder_get_object(builder, "datePicker"));


//-----------------------------------
//
    printf("Loading events... ");
    printf ("%d\n", load_events_from_file ());
    print_events ();
    printf("Done.\n");

    printf("Loading Todos... ");
    printf ("%d\n", load_todos_from_file ());
    sort_events ();
    printf("Done.\n");

    printf("Loading tags...");
    printf("%d\n", load_tags_from_file ());
    printf("Done.\n");

//-----------------------------------
//
    printf("Connecting calendar\n");
    initialize_calendar ();
    printf("Done\n");

//-----------------------------------
//
    printf("Initializing listbox1...\n");
    initialize_events_listbox (NUM_EVENTS);
    printf("Done.\n");

    printf("Initializing listbox2...\n");
    populate_todos_box(0, NUM_TODOS);
    printf("Done.\n");

//-----------------------------------
//
    printf("Connecting css\n");
    initialize_css ();
    printf("Done\n");

//-----------------------------------
//
    //gtk_calendar_select_month (GTK_CALENDAR(datePicker), 
    //        (guint) tm.tm_mon, (guint) tm.tm_year + 1900);
    //gtk_calendar_select_day (GTK_CALENDAR(datePicker), 
    //        (guint) tm.tm_mday);
    // variables to store date and time components

//-----------------------------------
//

//-----------------------------------
//  Start of UI 
//-----------------------------------

	gtk_widget_show_all (window);

    // Should be visible by default but for 
    // some reason I have to do it manually
    gtk_widget_grab_focus(cmdColor);
    gtk_widget_set_visible (cmdColor, FALSE);
	gtk_label_set_text (GTK_LABEL(welcome), (const gchar* ) say_hello());

    gtk_builder_connect_signals(builder, NULL);
	gtk_main ();

	return EXIT_SUCCESS;
}

//......................................................................................



void	
on_destroy() 
{ 
		gtk_main_quit();
}
