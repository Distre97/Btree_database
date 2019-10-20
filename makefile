edit : main_test.o create_test_data.o
	g++ -o edit main_test.o create_test_data.o

main_test.o : main_test.cpp create_test_data.h
	g++ -c main_test.cpp
create_test_date.o : create_test_date.cpp create_test_date.h
	g++ -c create_test_date.cpp
clean:
	rm edit main_test.o create_test_data.o