// src: https://stackoverflow.com/questions/10134956/in-simple-gtk-key-press-event-example-gdk-shift-mask-seems-to-be-ignored
gboolean
on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    if (event->state & GDK_CONTROL_MASK)
    {
        switch (event->keyval)
        {
            case GDK_KEY_t:
                // If command is focused, display the fctns for a reminder
                if (gtk_widget_is_focus (cmdTitleEntry))
                {
                    css_add_class(cmdTitleEntry, "cmdEntryTodoMode");
                    css_add_class(cmdAddButton, "cmdEntryTodoMode");
                    current_command_type = TODO;
                }
                return TRUE;

            case GDK_KEY_e:
                // If command is focused, display the fctns for a reminder
                if (gtk_widget_is_focus (cmdTitleEntry))
                {
                    css_remove_class(cmdTitleEntry, "cmdEntryTodoMode");
                    css_remove_class(cmdAddButton, "cmdEntryTodoMode");
                    current_command_type = EVENT;
                }
                return TRUE;

            default:
                return FALSE;
        }
    }
  switch (event->keyval)
  {

    case GDK_KEY_Escape:
        printf ("Escape pressed\n");
        gtk_widget_grab_focus(cmdColor);

        // Can't put in out of focus event 
        // Because of the color picker
        //gtk_widget_set_visible (datePicker, FALSE);
        // gtk_widget_set_visible (cmdDetailsContainer, FALSE);

        clear_cmd_input ();

        return TRUE;


    default:
      return FALSE;
  }

  return FALSE;
}
