edit : main_test.o create_test_data.o table.o 
	g++ -o edit main_test.o create_test_data.o table.o
main_test.o : main_test.cpp create_test_data.h table.h
	g++ -c main_test.cpp
create_test_date.o : create_test_date.cpp create_test_date.h
	g++ -c create_test_date.cpp
table.o : table.cpp table.h ulity.h
	g++ -c table.cpp
.PHONY : clean
clean:
	-rm main_test.o create_test_data.o table.o