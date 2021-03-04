// Comes after all the imports
// TODO: add ifndef statements...
//
//
#define EVENTS_DATA_FILE "/home/jcc/celo/data/events.dat"
#ifndef MAX_TITLE_SIZE
    #define MAX_TITLE_SIZE 256
#endif


// Keeping track of Events
struct Event
{
    char title[MAX_TITLE_SIZE];
    int day, month, year;
    gboolean complete;
    GdkRGBA color;
};

struct Event tmpEvent;
struct Event *Events[1000];
int NUM_EVENTS;
int row;


int
event_compar (const void *p1, 
        const void* p2)
{
    // Could be better without making structs 
    // But need to fix double pointer issue
    struct Event* e1 = *(struct Event **) p1;
    struct Event* e2 = *(struct Event **) p2;

    // <0 means that e1 goes before e2
    if (e1->year < e2->year) 
        {return -1;}
    else if (e1->year > e2->year)
        {return 1;}
    else
    {
        if (e1->month < e2->month) 
            {return -1;}
        else if (e1->month > e2->month)
            {return 1;}
        else 
        {
            if (e1->day < e2->day) 
                {return -1;}
            else if (e1->day > e2->day)
                {return 1;}
        }
    }
    return 0;
}

int
load_events_from_file ()
{
    int row = 0;
    struct Event input; 
    FILE *infile; 
      
    infile = fopen (EVENTS_DATA_FILE, "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
      
    // read file contents till end of file 
    while(1){
        if(!fread(&input, sizeof(struct Event), 1, infile)) 
        {
            fclose(infile);
            break;
        }
    
        // Add if running out of memory
        memcpy(&tmpEvent, &input, sizeof(struct Event));
        Events[row] = (struct Event*) malloc(sizeof(struct Event));
        memcpy(Events[row], &tmpEvent, sizeof(struct Event));

		row ++;
        if (row >= 1000)
        {
            printf("Too many rows\n");
            row--;
            break;
        }
    }

    NUM_EVENTS = row;
    return NUM_EVENTS;
}

void
sort_events ()
{
    if (NUM_EVENTS > 0)
        qsort((void*) Events, NUM_EVENTS - 1, sizeof(struct Event*), event_compar);
}

void print_events()
{
    int i;
    for (i = 0; i < NUM_EVENTS; i++)
    {
        printf ("\n%s\n", Events[i]->title);
    }
}

// Appends to data file
void 
save_event (struct Event *e)
{
    // Write Event to file
    FILE *outfile;
    // open file for writing 
    outfile = fopen (EVENTS_DATA_FILE, "a+"); 
    if (outfile == NULL) 
    { 
        //fprintf(stderr, "\nError opening file\n"); 
        printf ("\nError opening file\n"); 
        return;
    } 
      
    // write struct to file 
    fwrite (e, sizeof(struct Event), 1, outfile); 
    printf("Event %s saved", e->title);
  
    // close file 
    fclose (outfile); 
    return;

}

// Overwrites data file
void 
save_all_events()
{
    // Write Event to file
    FILE *outfile;
    // open file for writing 
    outfile = fopen (EVENTS_DATA_FILE, "w"); 
    if (outfile == NULL) 
    { 
        //fprintf(stderr, "\nError opening file\n"); 
        printf ("\nError opening file\n"); 
        return;
    } 
    for (int i = 0; i<NUM_EVENTS; i++)
    {
        // write struct to file 
        fwrite (Events[i], sizeof(struct Event), 1, outfile); 
      
    }
    // close file 
    fclose (outfile); 
    return;

}

void
add_event_to_list (struct Event *Event)
{
    memcpy(&tmpEvent, Event, sizeof(struct Event));
    Events[NUM_EVENTS] = (struct Event*) malloc(sizeof(struct Event));
    memcpy(Events[NUM_EVENTS], &tmpEvent, sizeof(struct Event));

    printf("Event added to list %s\n", Events[NUM_EVENTS]->title);
    NUM_EVENTS ++;
    sort_events ();
    save_event (Event);

}

void
remove_event (int row)
{
    // removes event at index i and saves the new file
    while (row<NUM_EVENTS-1)
    {
        Events[row] = Events[row+1];
        row++;
    }
    Events[row] = NULL;
    NUM_EVENTS = row;
    printf("NUM_EVENTS: %d\n", NUM_EVENTS);

    // TODO: fix destroy() function
    save_all_events();
}
