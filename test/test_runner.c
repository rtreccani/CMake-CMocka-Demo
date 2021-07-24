#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>
#include <cmocka.h>

#include <non_mocked.h>


void test_get_int_from_char_valid(void **state)
{ //testing the boundaries of the function
    assert_int_equal(get_int_from_char('0'), 0);
    assert_int_equal(get_int_from_char('1'), 1);
    assert_int_equal(get_int_from_char('8'), 8);
    assert_int_equal(get_int_from_char('9'), 9);
}


void test_get_int_from_char_invalid(void **state)
{ //these two values are adjacent to the valid ones (corner cases)
    assert_int_equal(get_int_from_char(':'), -1);
    assert_int_equal(get_int_from_char('/'), -1);
}

/*uses mocked get_random_char to inject dummy values to 
get_random_char_and_try_int to unit test it */
void test_get_random_char_and_try_int_valid(void **state)
{   
    will_return(__wrap_get_random_char, '0');
    assert_int_equal(get_random_char_and_try_int(), 0);

    will_return(__wrap_get_random_char, '1');
    assert_int_equal(get_random_char_and_try_int(), 1);

    will_return(__wrap_get_random_char, '8');
    assert_int_equal(get_random_char_and_try_int(), 8);

    will_return(__wrap_get_random_char, '9');
    assert_int_equal(get_random_char_and_try_int(), 9);
}


void test_get_random_char_and_try_int_invalid(void **state)
{
    will_return(__wrap_get_random_char, ':');
    assert_int_equal(get_random_char_and_try_int(), -1);

    will_return(__wrap_get_random_char, '/');
    assert_int_equal(get_random_char_and_try_int(), -1);
}

int main (void)
{
    const struct CMUnitTest tests [] =
    {
        cmocka_unit_test(test_get_int_from_char_valid),
        cmocka_unit_test(test_get_int_from_char_invalid),
        cmocka_unit_test(test_get_random_char_and_try_int_valid),
        cmocka_unit_test(test_get_random_char_and_try_int_invalid),
    };

    return(cmocka_run_group_tests (tests, NULL, NULL));
}