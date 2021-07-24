#include <non_mocked.h>
#include <mocked.h>

/*accept a character. if it can be represented as a numeral 0-9, return that number
else, return -1 to indicate an error*/
int get_int_from_char(char in_char)
{
    int int_val = (int)in_char;
    if(int_val >= 48 && int_val <= 57)
    {
        return(int_val - 48);
    }
    else
    {
        return(-1);
    }
}

//this function gets a char at random and tries to turn it to an int
//it will be very hard to unit test as it relies on a random value
//hence we will mock get_random_char() to return values we want
int get_random_char_and_try_int(void)
{
    char randChar = get_random_char();
    return(get_int_from_char(randChar));
}