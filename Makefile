build: 
	g++ -g main.cpp -o main.exe -std=c++20

# set G_TEST_INCLUDE to include directory of googletest framework
# set G_MOCK_INCLUDE to include directory of googlemock framework
# set G_LIB to include directory of built googletest/googlemock framework libraries
test:
	cd tests && g++ -g launch_tests.cpp -o launch_tests.exe -std=c++20 -I ${G_TEST_INCLUDE} -I ${G_MOCK_INCLUDE} -L ${G_LIB} -lgtest -lgmock && launch_tests.exe