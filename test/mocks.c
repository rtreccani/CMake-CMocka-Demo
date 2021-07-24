#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>
#include <cmocka.h>

/* the original get_random_char relies on randomness
this makes it really hard to unit-test. to counteract this
we will mock the function here to return dummy values as 
specified by will_return*/

char __wrap_get_random_char(void){
    return((char)mock());
}