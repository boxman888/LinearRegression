CXX = g++
CXXFLAGS = -std=c++11 -Wall -fpic -O2 -I [path/to/eigen]
SRCS = regression.cpp HousingData.cpp
HEADERS = HousingData.h
OBJS = regression.o HousingData.o

all: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o regression

${OBJS}: ${SRCS}
	${CXX} -c $(@:.o=.cpp)

clear:
	rm -f *.o regression
