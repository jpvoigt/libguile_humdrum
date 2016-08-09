# first version running on linux
# mac version should produce *.dylib
# win version should produce *.dll

CXX=g++
INCDIRS   = -Iexternal/humlib/include 
LIBDIRS   = -Lexternal/humlib/lib
GUILE     = guile
HUMLIB    = humlib
PREFLAGS  = -O3 -Wall -std=c++11 $(INCDIRS)
POSTFLAGS = $(LIBDIRS) -shared -fPIC -l$(GUILE) -l$(HUMLIB)

.PHONY: external

ALL: external libguile_humdrum.so
	

libguile_humdrum.so: libguile_humdrum.cpp hum2ly.o
	$(CXX) $(PREFLAGS) libguile_humdrum.cpp hum2ly.o -o libguile_humdrum.so $(POSTFLAGS)

hum2ly.o: hum2ly.cpp hum2ly.h
	$(CXX) -c $(PREFLAGS) hum2ly.cpp -o hum2ly.o $(POSTFLAGS)

external:
ifeq ($(wildcard external/humlib/lib/libhumlib.a),)
	(cd external && $(MAKE))
endif
