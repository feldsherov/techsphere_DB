all: bitset page filesystem

page:
	g++ page.test.cpp ../page.cpp -std=c++11 -o page.test

bitset:
	g++ bitset.test.cpp ../bitset.cpp -std=c++11 -o bitset.test

filesystem:
	g++ filesystem.test.cpp ../filesystem.cpp ../bitset.cpp ../page.cpp -lboost_system-mt -lboost_filesystem-mt -std=c++11 -o filesystem.test
