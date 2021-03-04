// NUM_EVENTS is global?
char hex[8];
int red, blue, green;
char **labels;
char tmp1[1024];
//
gint
listbox1_compar(GtkListBoxRow *row1, GtkListBoxRow *row2, gpointer user_data)
{
    // Pretty slow but doesn't update often
    int i;
    int j1;
    int j2;
    
    GtkWidget* w1;
    GtkWidget* w2;
    w1 = gtk_bin_get_child (GTK_BIN(row1));
    w2 = gtk_bin_get_child (GTK_BIN(row2));

    // w1 and w2 are pointers to GtkLabels
    for (i = 0; i<NUM_EVENTS; i++)
    {
        if (strcmp((char*) gtk_label_get_text (GTK_LABEL(w1)), Events[i]->title) == 0)
            j1 = i;
        else if (strcmp((char*) gtk_label_get_text (GTK_LABEL(w2)), Events[i]->title) == 0)
            j2 = i;
    }

    if(j2 == 0 && j1 == 0)
        printf("No box addresses found\n");
    
    // Compare the Events at each address
    return  event_compar(&Events[j1], &Events[j2]);
}

void
format_label_str (struct Event *Event)
{
    char tmpDateStr[32];
    char tmpLabelStr[1024];
    //char *fmtStr;

    printf("Getting hex value\n");
    // Get the HEX value
    sscanf ((char*)gdk_rgba_to_string (&Event->color),\
            "rgb(%d,%d,%d)", &red, &green, &blue);
    sprintf(hex, "#%02X%02X%02X", red, green, blue);

    // Todo: fix tab alignment instead of adding a 0
    if (Event->day < 10)
        sprintf (tmpDateStr, "%s  0%d", MONTH[Event->month], Event->day);
    else
        sprintf (tmpDateStr, "%s %d", MONTH[Event->month], Event->day);

    printf("Copying into label string\n");
    sprintf(tmpLabelStr, "<span foreground=\"%s\">%s\t %s</span>",
            hex, tmpDateStr, Event->title);

    printf("%s\n", tmpLabelStr);
    strcpy(tmp1, tmpLabelStr);
}

// Should be in list box manager
void populate_list_box (int start, int end)
{
    
    int row = start;
    printf("Populating box...\n");
    while(row < end) 
    {

        lb_entry[row] =  (GtkLabel *) gtk_label_new (NULL);
        lb_row[row] = (GtkListBoxRow *) gtk_list_box_row_new ();
        gtk_widget_set_margin_top(GTK_WIDGET(lb_entry[row]), (gint) 20);
        gtk_widget_set_margin_bottom(GTK_WIDGET(lb_entry[row]), (gint) 20);
        gtk_widget_set_margin_start(GTK_WIDGET(lb_entry[row]), (gint) 10);

        //format_event_label (Events[row], row);
        //labels[row] = (char *) malloc(1024*sizeof(char));
        //memcpy(labels[row], &tmpLabelStr, 1024*sizeof(char));
        //strcpy(labels[row], tmpLabelStr);
        //printf("Event label: %s\n", labels[row]);
        //printf("Size of labels[row]: %d\n", sizeof(labels[row]));
        printf("Label: %s\n", labels[row]);
        
        gtk_label_set_markup (GTK_LABEL(lb_entry[row]), (gchar *) labels[row]);
        gtk_label_set_justify (GTK_LABEL(lb_entry[row]), GTK_JUSTIFY_LEFT);
        gtk_widget_set_halign (GTK_WIDGET(lb_entry[row]), GTK_ALIGN_START);
        gtk_label_set_xalign (GTK_LABEL(lb_entry[row]), 0.1);
        gtk_label_set_yalign (GTK_LABEL(lb_entry[row]), 0.5);

        // Add the sub-box to the list box
        gtk_container_add(GTK_CONTAINER(lb_row[row]), GTK_WIDGET(lb_entry[row]));
        gtk_container_add(GTK_CONTAINER(listbox1), GTK_WIDGET(lb_row[row]));

        // Add reminder-box class to label
        GtkListBoxRow *lb_row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(listbox1), (gint) row);
        
        row ++;
    }
    printf("Done\n");

}

void
add_event_to_listbox1(int i, struct Event* Event)
{

    printf("Adding event to listbox...\n");
    GtkWidget* l = gtk_label_new (NULL);
    GtkWidget* r = gtk_list_box_row_new ();

    printf("Adding children to parent containers");
    gtk_label_set_text (GTK_LABEL(l), (gchar*) Event->title);
    gtk_container_add (GTK_CONTAINER(r), l);

    printf("Size of row+child_label: %d\n", sizeof(*r));
    printf("Size of GtkLabel: %d\tSize of GtkWidget\n", sizeof(*l), sizeof(GtkWidget));
    // Copy the label into the entry
    memcpy(&tmpLabel, l, sizeof(GtkWidget));
    memcpy(&tmpRow, r, sizeof(GtkWidget));

    lb_entry[i] = malloc(sizeof(GtkLabel));
    lb_row[i] = malloc(sizeof(GtkListBoxRow));

    memcpy(lb_entry[i], &tmpLabel, sizeof(GtkWidget));
    memcpy(lb_row[i], &tmpRow, sizeof(GtkWidget));

    printf("Label copied to lb_entry successfully\n");
    gtk_container_add(GTK_CONTAINER(lb_row[row]), GTK_WIDGET(lb_entry[row]));

    printf("Last Step\n");
    // Add the sub-box to the list box
    gtk_container_add (GTK_CONTAINER(listbox1), GTK_WIDGET(lb_row[i]));
    printf("Done\n");

}

void
on_listbox1_row_activated (GtkWidget *lb)
{
    int i;
    GtkListBoxRow *selected = gtk_list_box_get_selected_row (GTK_LIST_BOX(listbox1));

    i = gtk_list_box_row_get_index (selected);
    gtk_container_remove(GTK_CONTAINER(listbox1), GTK_WIDGET(selected));
    // gtk_container_foreach(GTK_CONTAINER(listbox1), remove_child, NULL);
    remove_event(i);

    printf("Row %d deleted\n", i);
}

void 
initialize_events_listbox (int NUM_EVENTS)
{

    labels = malloc(NUM_EVENTS * sizeof(char *));

    for(int i = 0; i<NUM_EVENTS; i++)
    {
        labels[i] = malloc(sizeof(tmp));
        //format_label_str(Events[i]);
        format_label_str(Events[i]);
        strcpy(labels[i], tmp1);
        printf("label string: %s\n", tmp1);
    }
    if (NUM_EVENTS > 0)
    {

        populate_list_box (0, NUM_EVENTS);
        printf("Initializing sort function\n");
        gtk_list_box_set_sort_func(GTK_LIST_BOX(listbox1), listbox1_compar, NULL, NULL);
        gtk_list_box_set_activate_on_single_click (GTK_LIST_BOX(listbox1), FALSE);

        GtkListBoxRow *lb_row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(listbox1), (gint) 0);
        gtk_widget_set_margin_top(GTK_WIDGET(lb_row), (gint) 20);
        printf("Done\n");

    }
}

void
add_event_to_listbox1_test ()
{
//    GtkWidget *l = gtk_label_new (NULL);
//    GtkWidget *r = gtk_list_box_row_new ();
//
    int i = NUM_EVENTS;
    printf("\n\n-----------------------Adding event to listbox--------------\n");
//
//    printf("Copying dummy widgets to tmp spaces...\n");
//    memcpy (&tmpLabel, l, sizeof(GtkWidget));
//    memcpy (&tmpRow, r, sizeof(GtkWidget));
//    printf("Done\n");
//
//    printf("Copying tmp space into lb lists...");
//    lb_entry[i] = (GtkWidget *) malloc(sizeof(GtkLabel));
//    lb_row[i] = (GtkWidget *) malloc(sizeof(GtkWidget));
//
//    memcpy(lb_entry[i], &tmpLabel, sizeof(GtkLabel));
//    memcpy(lb_row[i], &tmpRow, sizeof(GtkWidget));
//    printf("Done\n");
//
//    printf("Size of last entry: %d\n", sizeof(*lb_entry[i]));
//
//    printf("Adding markup...\n");
//    gtk_label_set_markup (GTK_LABEL(lb_entry[i]), (gchar*) "helloooo");
//    printf("Done\n");
//
//    printf("Last Step\n");
//    printf("Adding GtkLabel to GtkRow..\n");
//    gtk_container_add(GTK_CONTAINER(lb_row[i]), lb_entry[i]);
//    printf("Done\n");
//
//    printf("Adding GtkListBoxRow to GtkListBox...\n");
    GtkLabel *l = (GtkLabel *) gtk_label_new ("hello");
    GtkListBoxRow *r = (GtkListBoxRow *) gtk_list_box_row_new ();
    gtk_container_add(GTK_CONTAINER(r), GTK_WIDGET(l));

    lb_entry[i] = (GtkLabel *) malloc(sizeof(GtkLabel));
    memcpy (&tmpLabel, l, sizeof(GtkLabel));
    memcpy (lb_entry[i], &tmpLabel, sizeof(GtkLabel));
    printf("Message from tmpLabel: %s\n", (char *) gtk_label_get_text(GTK_LABEL(&tmpLabel)));
    printf("Message from lb_entry: %s\n", (char *) gtk_label_get_text(GTK_LABEL(lb_entry[i])));

    printf("---------------Adding label to listbox-------------\n");
    lb_row[i] = (GtkListBoxRow *) malloc(sizeof(GtkListBoxRow));
    memcpy (&tmpRow, r, sizeof(GtkListBoxRow));
    memcpy (lb_row[i], &tmpRow, sizeof(GtkListBoxRow));
    // w1 = gtk_bin_get_child (GTK_BIN(row1));
    printf("Message from child of r: %s\n", (char *) gtk_label_get_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(r)))));
    printf("Message from child of lb_row: %s\n", (char *) gtk_label_get_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(lb_row[i])))));

    printf("Adding row to list box");
    gtk_container_add(GTK_CONTAINER(listbox1), GTK_WIDGET(lb_row[i]));
    printf("Done\n");

}
