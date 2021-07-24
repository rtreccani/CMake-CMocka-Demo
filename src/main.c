#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <non_mocked.h>
#include <mocked.h>


/*this is the entry point when the program is ran in its normal configuration*/
void main(){
    printf("entrypoint for the executable\n");
    srand(time(0)); //set the randomness seed based on the time (for some element of randomness)
    for(int i = 0; i < 5; i++){ //get random chars, try to cast to int, print the result, do 5 times
        printf("%d \n", get_int_from_char(get_random_char()));
    }
}