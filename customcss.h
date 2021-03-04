#define CSS_FILEPATH "/home/jcc/celo/css/celo.css"
GtkCssProvider *cssProvider1;
void 
initialize_css ()
{

    cssProvider1 = gtk_css_provider_new();
    // TODO: watch resource video to use resources instead of filepath
    gtk_css_provider_load_from_path(cssProvider1, CSS_FILEPATH, NULL);

    css_set(cssProvider1, window);
    css_set(cssProvider1, listbox1);
    css_set(cssProvider1, listbox2);
    css_set(cssProvider1, cmdTitleEntry);
    css_set(cssProvider1, datePicker);
    css_set(cssProvider1, cmdAddButton);
}

// Paint a css on a widget
void
css_set (GtkCssProvider *cssProvider, GtkWidget *g_widget)
{
    GtkStyleContext *context = gtk_widget_get_style_context(g_widget);

    gtk_style_context_add_provider (context,
            GTK_STYLE_PROVIDER(cssProvider),
            GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void
css_add_class (GtkWidget *w, char *c)
{
    GtkStyleContext *context;
    context = gtk_widget_get_style_context(w);
    gtk_style_context_add_class(context, c);

}

void
css_remove_class (GtkWidget *w, char *c)
{
    GtkStyleContext *context;
    context = gtk_widget_get_style_context(w);
    gtk_style_context_remove_class(context, c);

}
