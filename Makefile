## Licence:	GPLv3
## Programmer:	Jan-Peter Voigt
##
## libguile_humdrum
## ================
##
## guile-module to provide functions for humdrum file handling
##


# first version running on linux
# TODO: mac version should produce *.dylib
# TODO: win version should produce *.dll

CXX=g++
INCDIRS   = -Iexternal/humlib/include 
LIBDIRS   = -Lexternal/humlib/lib
GUILE     = guile
HUMLIB    = humlib
PREFLAGS  = -O3 -fPIC -Wall -std=c++11 $(INCDIRS)
POSTFLAGS = $(LIBDIRS) -l$(GUILE) -l$(HUMLIB)

.PHONY: external

ALL: external libguile_humdrum.so

libguile_humdrum.so: libguile_humdrum.o hum2ly.o Makefile
	$(CXX) -shared libguile_humdrum.o hum2ly.o -o libguile_humdrum.so $(POSTFLAGS)

libguile_humdrum.o: libguile_humdrum.cpp hum2ly.o Makefile
	$(CXX) -c $(PREFLAGS) libguile_humdrum.cpp -o libguile_humdrum.o

hum2ly.o: hum2ly.cpp hum2ly.h Makefile
	$(CXX) -c $(PREFLAGS) hum2ly.cpp -o hum2ly.o

external:
ifeq ($(wildcard external/humlib/lib/libhumlib.a),)
	(cd external && $(MAKE))
endif

clean:
	rm -v *.o *.so
