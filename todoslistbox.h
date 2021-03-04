// Should be in list box manager
void 
populate_todos_box (int start, int end)
{
    
    int row = start;
    while (row < end) // populate the first 10 rows
    {
        lb2_entry[row] = gtk_label_new ((char*) Todos[row]->title);
        lb2_row[row] = gtk_list_box_row_new ();
        gtk_widget_set_margin_top(GTK_WIDGET(lb2_entry[row]), (gint) 6);
        gtk_widget_set_margin_bottom(GTK_WIDGET(lb2_entry[row]), (gint) 6);
        gtk_widget_set_margin_start(GTK_WIDGET(lb2_entry[row]), (gint) 4);
        gtk_label_set_line_wrap(GTK_LABEL(lb2_entry[row]), TRUE);

        gtk_label_set_justify (GTK_LABEL(lb2_entry[row]), GTK_JUSTIFY_LEFT);
        gtk_widget_set_halign (GTK_WIDGET(lb2_entry[row]), GTK_ALIGN_START);
        gtk_label_set_xalign (GTK_LABEL(lb2_entry[row]), 0.1);
        gtk_label_set_yalign (GTK_LABEL(lb2_entry[row]), 0.5);

        // Add the sub-box to the list box
        // gtk_list_box_insert(GTK_LIST_BOX(listbox1), lb_entry[row], (guint) 0);
        gtk_container_add(GTK_CONTAINER(lb2_row[row]), lb2_entry[row]);
        gtk_container_add(GTK_CONTAINER(listbox2), lb2_row[row]);

        
        row ++;
    }


}

void
initialize_todos_listbox (int NUM_TODOS)
{
    if (NUM_TODOS > 0)
    {
        gtk_list_box_set_activate_on_single_click (GTK_LIST_BOX(listbox2), FALSE);

        GtkListBoxRow *lb2_row = gtk_list_box_get_row_at_index(GTK_LIST_BOX(listbox2), (gint) 0);
        gtk_widget_set_margin_top(GTK_WIDGET(lb2_row), (gint) 20);
    }

}

void
on_listbox2_row_activated (GtkWidget *lb)
{
    int i;
    GtkListBoxRow *selected = gtk_list_box_get_selected_row (GTK_LIST_BOX(listbox2));

    i = gtk_list_box_row_get_index (selected);
    gtk_container_remove(GTK_CONTAINER(listbox2), GTK_WIDGET(selected));
    remove_todo(i);

    printf("Row %d deleted\n", i);
}
