#
# This makefile can be used to build a Win32 application under Cygwin
#

include ../../../Makefile.in.$(shell uname)

PROGNAME=trans_curve1
OUTNAME=$(PROGNAME)
PLATFORM=win32

CXXFLAGS= $(AGGCXXFLAGS) \
-I../../../include \
-I../../../font_win32_tt \
-I/usr/X11R6/include \
-L/usr/X11R6/lib \
-L../../../src \
$(PIXFMT)

LIBS = $(AGGLIBS) -lm -lgdi32

SRC=\
../../$(PROGNAME).cpp \
../../interactive_polygon.cpp \
../../../src/platform/$(PLATFORM)/agg_platform_support.cpp \
../../../src/platform/$(PLATFORM)/agg_win32_bmp.cpp \
../../../font_win32_tt/agg_font_win32_tt.cpp


OBJ= $(SRC:.cpp=.o)

$(OUTNAME):	$(OBJ)
	$(CXX) $(CXXFLAGS)  $^ -o $(OUTNAME) $(LIBS)

clean:
	rm -f $(OUTNAME)
	rm -f ../../$(PROGNAME).o
	rm -f ../../interactive_polygon.o
	rm -f ../../../src/platform/$(PLATFORM)/agg_platform_support.o
	rm -f gamma.txt
	rm -f gamma.bin

%.o:	%.cpp
	@echo \< $*.cpp \>
	$(CXX) -c $(CXXFLAGS) $*.cpp -o $@


