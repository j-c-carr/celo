enum command_types { EVENT, TODO };
enum command_types current_command_type = EVENT;
// Should be in command bar manager

void
on_cmdTitleEntry_changed (GtkEntry *e) 
{
	char tmp[32];
    int i;

    // First word
	sscanf (gtk_entry_get_text(e), "%s", tmp);

    // First word
    if (tmp == NULL)
        return;

    // returns index of tag
    i = is_tag (tmp, Tags, NUM_TAGS);
    if (i >= 0) 
    {
        printf("Tag found.\n");
        gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(cmdColor), &Tags[i]->color);
        gtk_color_button_set_rgba(GTK_COLOR_BUTTON(cmdColor), &Tags[i]->color);
    }
}

void 
clear_cmd_input()
{
    // Clears the color, date, date label, and entry
    gtk_editable_delete_text (GTK_EDITABLE(cmdTitleEntry), 0, -1);
    gtk_calendar_clear_marks (GTK_CALENDAR(datePicker));
    // gtk_widget_set_visible (datePicker, FALSE);
}

void
new_todo_from_command_bar ()
{
    printf("Creating a new todo from the command bar...\n");
    struct Todo Todo;

	sprintf (Todo.title, "%s", gtk_entry_get_text (GTK_ENTRY (cmdTitleEntry)));
    Todo.complete = FALSE;

    add_todo_to_list(&Todo);
}
void
new_event_from_command_bar ()
{
    printf("Creating new event from command bar...\n");
    struct Event Event;
    struct tm tm;
    int red,blue,green;
    char hex[8];

    // TODO: check for empty string
    gtk_color_button_get_rgba (GTK_COLOR_BUTTON(cmdColor), &Event.color);

    gtk_calendar_get_date 
        (GTK_CALENDAR(datePicker), &Event.year, &Event.month, &Event.day);

	sprintf (Event.title, "%s", gtk_entry_get_text (GTK_ENTRY (cmdTitleEntry)));

    Event.complete = FALSE;

    add_event_to_list (&Event);
    // You can always dream...
    //add_event_to_listbox1_test ();
    printf("Done\n");

}

// Add user data/
void 
on_cmdAddButton_clicked(GtkButton *b)
{

    new_event_from_command_bar ();

    clear_cmd_input ();

}

// Should be in command bar manager
void 
on_cmdTitleEntry_activate (GtkEntry *e)
{
    switch (current_command_type)
    {
        // todo
        case TODO:
            new_todo_from_command_bar ();
            clear_cmd_input ();
            break;

        // event
        default:
            new_event_from_command_bar ();
            clear_cmd_input ();
    }
}
