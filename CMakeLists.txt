cmake_minimum_required(VERSION 3.13) #3.13 introduces target_link_options
project(CMocka-Demo)
find_package(CMocka) #you need to have CMocka installed to at least 3.13 in a path where this can find it 
include(CTest) #enables testing via ctest or some GUI options

 #in the production version, you add both the mocked and unmocked C files
add_executable(mainProgram src/main.c src/mocked.c src/non_mocked.c)
target_include_directories(mainProgram PRIVATE includes/)

#in the test version, you don't include the mocked unit C file. this would ordinarily cause an 
#undefined reference linker error. but using the ld --wrap option, if an undefined reference occurs,
#it will re-search the token with __wrap prepended, therefore finding the mocked version of the function
#instead
add_executable(tester test/test_runner.c src/non_mocked.c src/mocked.c test/mocks.c)
set_target_properties(tester PROPERTIES LINK_FLAGS "-Wl,--wrap=get_random_char")
target_include_directories(tester PRIVATE includes/)
target_link_libraries(tester cmocka)
add_test(mainProgram tester) #i think this just makes tester formally a test of the mainProgram