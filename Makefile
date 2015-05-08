all:
	g++ mydb.cpp filesystem.cpp bitset.cpp page.cpp database.cpp -L/usr/local/lib -lboost_system-mt -lboost_filesystem-mt -std=c++11 -O0 -g -ggdb -shared -fPIC -o fdb.so

my_test:
	g++ main.cpp mydb.cpp filesystem.cpp bitset.cpp page.cpp database.cpp -L/usr/local/lib -lboost_system-mt -lboost_filesystem-mt -std=c++11 -g -o ./files/my_test

