# CMake-CMocka demo
## why?
I needed to learn how to use CMocka, and I couldn't find any good sources on integrating it with CMake, so I decided to upload this repo.
It shows how to use Cmake and Cmocka to do unit testing on your program, use mocking, and configure tools to automatically test.
It also follows the KISS(Keep It Simple Stupid) principle by not doing anything unneccessary. if you spot a way to make this repo less code-heavy without 
losing functionality, let me know or make a PR, especially with regards to the CMakeLists.txt which i tried to keep minimal.

## what? 
The CMake file is configured to generate 2 targets, mainProgram and tester. MainProgram just runs the `get_random_char` function 5 times, passes it to 
`get_int_from_char`, and prints the output. 

Tester first illustrates a simple unit test, testing the `get_int_from_char` function, which is deterministic, and therefore very easy to unit test.
Pass data in, check the data coming out. 

It then tests `get_random_char_and_try_int`, which is difficult because it depends on `get_random_char`, a non-deterministic function, and is therefore 
hard to verify proper operation. To solve this, the 'mocking' capability of CMocka is leveraged, to generate a mock version of `get_random_char` (found in 
`test/mocks.c`) which accepts `will_return` commands from `test/test_runner.c` and uses that to generate dummy data to feed to calling functions. 

Using this, it is possible to pre-determine what data the `__wrap_get_random_char` function will return, and therefore to unit-test `get_random_char_and_try_int`.

The mechanism by which the wrapped function is swapped out for the 'real' function is explained more in `CMakeLists.txt` but in short, if the linker is passed the 
option `-Wl, --wrap=<function_name>` and an undefined reference to `<function_name>` occurs, the linker is permitted to swap out `__wrap_<function_name>` in its place.
In the testing target, the mocked functions are purposefully not compiled, to cause a linker error, and then the linker option is set to allow the 'wrapped' or 'mocked' unit
to take it's place. 

## how
### Warning
you need CMake for this, as well as CMocka. the dependence on CMake >= 3.13.0 is no longer valid, and it works down to 3.10 (tested)
and probably down to cmake 3.0 or below (untested) 

on ubuntu 
```
sudo apt install cmake libcmocka-dev gcc g++
```
will fetch the appropriate tools. 

Clone this repo, then from the command line: 
```
mkdir build
cd build
cmake ..
make
```
will run cmake to configure the build directory, and then build the mainProgram and tester binaries. 
From there, you can run 
`./mainProgram`
to see the result of the 'normal' configuration, or 
`./tester` 
to see the result of the unit-tests from CMocka.

you can also run 
`ctest`
which just wraps ./tester, so not much use, but i kept it in as it provides useful GUI options in some IDEs.



