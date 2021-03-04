// Comes after all the imports
// TODO: add ifndef statements...
//
//
#define TODOS_DATA_FILE "/home/jcc/celo/data/todos.dat"
#ifndef MAX_TITLE_SIZE
    #define MAX_TITLE_SIZE 256
#endif


// Keeping track of Todos
struct Todo
{
    char title[MAX_TITLE_SIZE];
    gboolean complete;
};

struct Todo tmpTodo;
struct Todo *Todos[1000];

int NUM_TODOS;
int row;


int
load_todos_from_file ()
{
    int row = 0;
    struct Todo input; 
    FILE *infile; 
      
    infile = fopen (TODOS_DATA_FILE, "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening todo file\n"); 
        exit (1); 
    } 
      
    // read file contents till end of file 
    while(1){
        if(!fread(&input, sizeof(struct Todo), 1, infile)) 
        {
            fclose(infile);
            break;
        }
    
        // Add if running out of memory
        memcpy(&tmpTodo, &input, sizeof(struct Todo));
        Todos[row] = (struct Todo*) malloc(sizeof(struct Todo));
        memcpy(Todos[row], &tmpTodo, sizeof(struct Todo));

		row ++;
        if (row >= 1000)
        {
            printf("Too many rows\n");
            row--;
            break;
        }
    }

    NUM_TODOS = row;
    return NUM_TODOS;
}

void print_todos ()
{
    int i;
    printf("Printing Todos:\n");
    for (i = 0; i < NUM_TODOS; i++)
    {
        printf ("%s\n", Todos[i]->title);
    }
    printf("Done\n");
}

// Appends to data file
void 
save_todo (struct Todo *t)
{
    // Write Todo to file
    FILE *outfile;
    // open file for writing 
    outfile = fopen (TODOS_DATA_FILE, "a+"); 
    if (outfile == NULL) 
    { 
        //fprintf(stderr, "\nError opening file\n"); 
        printf ("\nError opening file\n"); 
        return;
    } 
      
    // write struct to file 
    fwrite (t, sizeof(struct Todo), 1, outfile); 
      
    if (fwrite != 0)  
        printf("Entry saved.\n%s\n", t->title);
    else 
        printf("error writing file !\n"); 
  
    // close file 
    fclose (outfile); 
    return;

}

// Overwrites data file
void 
save_all_todos()
{
    // Write Todo to file
    FILE *outfile;
    // open file for writing 
    outfile = fopen (TODOS_DATA_FILE, "w"); 
    if (outfile == NULL) 
    { 
        //fprintf(stderr, "\nError opening file\n"); 
        printf ("\nError opening file\n"); 
        return;
    } 
    printf("Saving Todos...\n");
    for (int i = 0; i<NUM_TODOS; i++)
    {
        // write struct to file 
        fwrite (Todos[i], sizeof(struct Todo), 1, outfile); 
          
        if (fwrite == 0)
            printf("error writing file !\n"); 
    }
    printf("Done.\n");
    // close file 
    fclose (outfile); 
    return;

}


void
remove_todo (int row)
{
    // removes event at index i and saves the new file
    while (row<NUM_TODOS-1)
    {
        Todos[row] = Todos[row+1];
        row++;
    }
    Todos[row] = NULL;
    NUM_TODOS = row;
    printf("NUM_TODOS: %d\n", NUM_TODOS);

    // TODO: fix destroy() function
    save_all_todos();
}

void
add_todo_to_list (struct Todo *Todo)
{

    memcpy(&tmpTodo, Todo, sizeof(struct Todo));
    Todos[NUM_TODOS] = (struct Todo*) malloc(sizeof(struct Event));
    memcpy(Todos[NUM_TODOS], &tmpTodo, sizeof(struct Event));

    printf("Todo added to list %s\n", Todos[NUM_TODOS]->title);
    NUM_TODOS ++;
    save_todo (Todo);

}
