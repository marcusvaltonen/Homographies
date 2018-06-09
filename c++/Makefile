CXX=g++
RM=rm -f
CPPFLAGS=-g -I/usr/local/include/eigen3 -I.
LDFLAGS=-g
LDLIBS=
DEPS=solver_homography_planar.h get_homography_25pt.h

SRCS=solver_homography_planar.cpp get_homography_25pt.cpp test_get_homography_25pt.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: test

%.o: %.ccp $(DEPS)
	$(CXX) -c -o $@ $< $(CPPFLAGS)

test: $(OBJS)
	$(CXX) $(LDFLAGS) -o test $(OBJS) $(LDLIBS)

clean:
	$(RM) $(OBJS)
	$(RM) test
