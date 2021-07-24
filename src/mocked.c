#include <mocked.h>
#include <stdlib.h>

//gets a random value and returns it as a character
char get_random_char(void)
{
    return(rand()%255);
}