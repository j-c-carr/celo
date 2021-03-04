#ifndef time
#define time
    #include<time.h>
    #include<stdlib.h>
#endif
// Good morning
char goodMorning[9][32] = {
    "Bon matin", "Buenos dias", "Guten Morgen",
    "buongiorno", "bom dia", "sobh bekheir", "suprabhat",
    "sabah al-khair", "sawubona"
};

static char* 
say_hello() 
{
    // Say hello
    time_t t;
    srand((unsigned) *time(&t));
    int r = rand() % 9;

    return goodMorning[r];
}

