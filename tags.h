#include<stdlib.h>
#include<stdio.h>
#include<gtk/gtk.h>
#define MAX_TAGS 16
#define TAGS_DATA_FILE "/home/jcc/celo/data/tags.dat"

struct Tag{
    GdkRGBA color;
    char name[32];
};

struct Tag tmpTag;
int NUM_TAGS;
struct Tag *Tags[MAX_TAGS];

void
print_hex_val(struct Tag *Tag)
{
    int red, green, blue;
    sscanf ((char*)gdk_rgba_to_string (&Tag->color),\
            "rgb(%d,%d,%d)", &red, &green, &blue);
    printf("#%02X%02X%02X\n", red, green, blue);
}

int
is_tag(char *t, struct Tag* Tags[], int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        if(strcmp(t, Tags[i]->name) == 0)
        {
            printf("Tag: %s\n", t);
            return i;
        }
    }
    return -1;
}

void
save_tag(struct Tag *t)
{
    // Write Event to file
    FILE *outfile;
    // open file for writing 
    outfile = fopen (TAGS_DATA_FILE, "a+"); 
    if (outfile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        return;
    } 
      
    // write struct to file 
    fwrite (t, sizeof(struct Tag), 1, outfile); 
      
    if (fwrite != 0)  
        fprintf(stderr, "\ncontents to file written successfully !\n"); 
    else 
        printf("error writing file !\n"); 
  
    // close file 
    fclose (outfile); 

    return;

}

int
load_tags_from_file()
{
    FILE *infile; 
    struct Tag input; 
    int i;
      
    // Open person.dat for reading 
    infile = fopen (TAGS_DATA_FILE, "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
      
    i = 0;
    // read file contents till end of file 
    while(1){
        if(!fread(&input, sizeof(struct Tag), 1, infile)) 
        {
            fclose(infile);
            break;
        }
    
        if (i >= MAX_TAGS)
            break;

        memcpy(&tmpTag, &input, sizeof(struct Tag));
        Tags[i] = (struct Tag*) malloc(sizeof(struct Tag));
        memcpy(Tags[i], &tmpTag, sizeof(struct Tag));

		i ++;
    }
    fprintf (stderr, "\n%i tags loaded\n", i);
    return i;

}

//int main ()
//{
//    struct Tag Tag;
//    struct Tag* TagList[16];
//    char* str = "m248";
//    const char* file = "tags.dat";
//
//    sprintf(Tag.name, "%s", str);
//    gdk_rgba_parse(&Tag.color, (gchar*) "rgb(4,50,2)");
//
//    save_tag(&Tag, file);
//    //printf("tag saved\n");
//    load_Tags(file, TagList);
//    print_hex_val(&Tag);
//
//    printf("%s\n", TagList[0]->name);
//
//    return 0;
//}
