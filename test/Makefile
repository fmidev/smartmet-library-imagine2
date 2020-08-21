PROG = $(patsubst %.cpp,%,$(wildcard *Test.cpp))

MAINFLAGS = -std=c++11 -Wall -W -Wno-unused-parameter

EXTRAFLAGS = \
	-Werror \
	-pedantic \
	-Wpointer-arith \
	-Wcast-qual \
	-Wcast-align \
	-Wwrite-strings \
	-Wconversion \
	-Winline \
	-Wctor-dtor-privacy \
	-Wnon-virtual-dtor \
	-Wno-pmf-conversions \
	-Wsign-promo \
	-Wchar-subscripts \
	-Wold-style-cast \
	-Wshadow \
	-Woverloaded-virtual

DIFFICULTFLAGS = \
	-Weffc++ \
	-Wunreachable-code \
	-Wredundant-decls

# CAIROMODE = -DIMAGINE_WITH_CAIRO 
CAIROMODE =

# Platform independent Freetype2 support

FT2_LIBS= $(shell freetype-config --libs)
FT2_CFLAGS= $(shell freetype-config --cflags)

# Platform independent Cairomm support

ifeq "$(CAIROMODE)" ""
  CAIRO_LIBS = $(shell pkg-config --libs cairomm-1.0)
  CAIRO_CFLAGS = $(CAIROMODE) $(shell pkg-config --cflags cairomm-1.0)
else
  CAIRO_LIBS =
  CAIRO_CFLAGS = 
endif

CC = g++
CFLAGS = -DUNIX -O0 -g $(MAINFLAGS)

# Boost 1.69

ifneq "$(wildcard /usr/include/boost169)" ""
  INCLUDES += -I/usr/include/boost169
  LIBS += -L/usr/lib64/boost169
endif

INCLUDES += \
	-I../imagine2 \
	-I/usr/include/ \
	-I/usr/include/smartmet \
	-I/usr/include/smartmet/newbase \
	-I/usr/include/smartmet/regression \
	$(FT2_CFLAGS) \
	$(CAIRO_CFLAGS)

LIBS +=  ../libsmartmet-imagine2.so \
	-lsmartmet-newbase \
	-lsmartmet-gis \
	-lboost_regex \
	-lboost_filesystem \
        -lboost_iostreams \
        -lboost_thread \
        -lboost_system \
	$(FT2_LIBS) \
	$(CAIRO_LIBS) \
	-lpng -lz -lpthread -lrt

all: $(PROG)
clean:
	rm -f $(PROG) *~

test: $(PROG)
	@echo Running tests:
	@for prog in $(PROG); do \
	./$$prog; \
	done

$(PROG) : % : %.cpp ../libsmartmet-imagine2.so
	$(CC) $(CFLAGS) -o $@ $@.cpp $(INCLUDES) $(LIBS)

