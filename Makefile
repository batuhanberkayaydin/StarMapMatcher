

CC = g++ 

CFLAGS +=-std=c++11 -I ./ -I /usr/local/include/opencv4/opencv2 -I /usr/local/include/opencv4
SRCS = *.cpp
PROG = 4DMatcher

OPENCV = `pkg-config opencv4 --cflags --libs`
# LDLIBS	   += -lboost_system \
# 			-lboost_filesystem \
# 			-lboost_program_options \
# 			-lboost_thread

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $(PROG) $(SRCS) $(OPENCV) 


clean:
	rm -f 4DMatcher 4DMatcher.o
	rm -rf 4DMatcher