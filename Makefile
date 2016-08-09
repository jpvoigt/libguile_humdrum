# first version running on linux
# mac version should produce *.dylib
# win version should produce *.dll

CXX=g++
CXXFLAGS=
LDFLAGS=-shared -fPIC

ALL: libguile_humdrum.so
	

libguile_humdrum.so: libguile_humdrum.cpp
	g++ libguile_humdrum.cpp -o libguile_humdrum.so $(CXXFLAGS) $(LDFLAGS)
