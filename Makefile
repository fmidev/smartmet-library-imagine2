SUBNAME = imagine2
LIB = smartmet-$(SUBNAME)
SPEC = smartmet-library-$(SUBNAME)
INCDIR = smartmet/$(SUBNAME)

REQUIRES = gdal fmt

include $(shell echo $${PREFIX-/usr})/share/smartmet/devel/makefile.inc

# Compiler options

DEFINES = -DUNIX -D_REENTRANT -DFMI_COMPRESSION -DBOOST -DBOOST_IOSTREAMS_NO_LIB

EXTRA_INCLUDES := $(shell pkg-config --cflags freetype2 cairomm-1.0)
EXTRA_LIBS := $(shell pkg-config --libs freetype2 cairomm-1.0)

INCLUDES += \
	-isystem $(includedir)/smartmet \
	-isystem $(includedir)/smartmet/newbase \
	$(EXTRA_INCLUDES)

LIBS += -L$(libdir) \
	-lsmartmet-newbase \
	-lsmartmet-macgyver \
	-lboost_regex \
	-lboost_thread \
	$(REQUIRED_LIBS) \
	$(EXTRA_LIBS) \
	-ljpeg -lpng -lz

# What to install

LIBFILE = lib$(LIB).so

# Compilation directories

vpath %.cpp $(SUBNAME)
vpath %.h $(SUBNAME)

# The files to be compiled

SRCS = $(wildcard $(SUBNAME)/*.cpp)
HDRS = $(wildcard $(SUBNAME)/*.h)
OBJS = $(patsubst %.cpp, obj/%.o, $(notdir $(SRCS)))

INCLUDES := -Iinclude $(INCLUDES)

.PHONY: test rpm

# The rules

all: objdir $(LIBFILE)
debug: all
release: all
profile: all

$(LIBFILE): $(OBJS)
	$(CXX) $(LDFLAGS) -shared -rdynamic -o $(LIBFILE) $(OBJS) $(LIBS)
	@echo Checking $(LIBFILE) for unresolved references
	@if ldd -r $(LIBFILE) 2>&1 | c++filt | grep ^undefined\ symbol |\
			grep -Pv ':\ __(?:(?:a|t|ub)san_|sanitizer_)'; \
	then \
		rm -v $(LIBFILE); \
		exit 1; \
	fi

clean:
	rm -f $(LIBFILE) *~ $(SUBNAME)/*~
	rm -rf $(objdir)

format:
	clang-format -i -style=file $(SUBNAME)/*.h $(SUBNAME)/*.cpp test/*.cpp

install:
	@mkdir -p $(includedir)/$(INCDIR)
	@list='$(HDRS)'; \
	for hdr in $$list; do \
	  HDR=$$(basename $$hdr); \
	  echo $(INSTALL_DATA) $$hdr $(includedir)/$(INCDIR)/$$HDR; \
	  $(INSTALL_DATA) $$hdr $(includedir)/$(INCDIR)/$$HDR; \
	done
	@mkdir -p $(libdir)
	$(INSTALL_PROG) $(LIBFILE) $(libdir)/$(LIBFILE)

test:
	$(MAKE) -C test $@

objdir:
	@mkdir -p $(objdir)

rpm: clean
	if [ -e $(SPEC).spec ]; \
	then \
	  tar -czvf $(SPEC).tar.gz --exclude test --exclude-vcs --transform "s,^,$(SPEC)/," * ; \
	  rpmbuild -tb $(SPEC).tar.gz ; \
	  rm -f $(SPEC).tar.gz ; \
	else \
	  echo $(SPEC).spec file missing; \
	fi;

.SUFFIXES: $(SUFFIXES) .cpp

obj/%.o : %.cpp
	@mkdir -p $(objdir)
	$(CXX) $(CFLAGS) $(INCLUDES) -c -MD -MF $(patsubst obj/%.o, obj/%.d, $@) -MT $@ -o $@ $<

ifneq ($(wildcard obj/*.d),)
-include $(wildcard obj/*.d)
endif
