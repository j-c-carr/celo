char test[1024] = "<span> testing </span>";
gchar *
CalendarFunc (GtkCalendar *calendar, guint year, guint month, guint day, gpointer user_data)
{
    if(month == 2)
    {
        if ( year == 2021 )
        {
            if (day == 9)
                return 0;

        }
    }
 
    return NULL;

}
void
print_free(void *p1)
{
    if(p1 != NULL)
        g_free(p1);
}
void initialize_calendar ()
{
    gtk_calendar_set_detail_func (GTK_CALENDAR(calendar1), CalendarFunc, NULL, print_free);
    //gtk_calendar_set_display_options (GTK_CALENDAR(calendar1), GTK_CALENDAR_SHOW_DETAILS);
    
}
