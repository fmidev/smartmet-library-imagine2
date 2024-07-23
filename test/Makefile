PROG = $(patsubst %.cpp,%,$(wildcard *Test.cpp))

REQUIRES = 

include $(shell echo $${PREFIX-/usr})/share/smartmet/devel/makefile.inc

# Platform independent Cairomm support
 
ifeq "$(CAIROMODE)" ""
  CAIRO_LIBS = $(shell pkg-config --libs cairomm-1.0)
  CAIRO_FLAGS = $(CAIROMODE) $(shell pkg-config --cflags cairomm-1.0)
else
  CAIRO_LIBS =
  CAIRO_FLAGS = 
endif

# Platform independent Freetype2 support

FT2_LIBS= $(shell freetype-config --libs)
FT2_FLAGS= $(shell freetype-config --cflags)

# Platform independent Cairomm support

FLAGS += -DUNIX $(CAIRO_FLAGS) $(FT2_FLAGS)

INCLUDES += \
	-I../imagine2 \
	-I/usr/include/ \
	-I/usr/include/smartmet \
	-I/usr/include/smartmet/newbase \
	-I/usr/include/smartmet/regression \
	$(FT2_CFLAGS)


LIBS +=  \
	../libsmartmet-imagine2.so \
	$(PREFIX_LDFLAGS) \
	$(REQUIRED_LIBS) \
	-lsmartmet-newbase \
	-lsmartmet-gis \
	-lsmartmet-macgyver \
	-lboost_regex \
	-lboost_filesystem \
	-lboost_iostreams \
	-lboost_thread \
	-lboost_system \
	$(FT2_LIBS) \
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
	$(CXX) $(FLAGS) -o $@ $@.cpp $(INCLUDES) $(LIBS)

