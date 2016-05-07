CUR_PATH = $(shell echo $(PWD))
OBJS = $(addprefix ykurcmd/objs/,ykurcmd.o commandParser.o usbcom.o)
LIBS = -lhidapi-libusb -lusb-1.0 -ludev
LOADPATHS = -L$(CUR_PATH)/../inc
PREPROCESSOR_DEFS = -DLINUX
CPP = g++

ykurcmd : $(OBJS)
	$(CPP) $(LOADPATHS) -o ykurcmd/bin/ykurcmd $(OBJS) $(LIBS)


ykurcmd/objs/ykurcmd.o : ykurcmd/ykurcmd.cpp ykurcmd/stdafx.h ykurcmd/commandParser.h
	$(CPP) $(PREPROCESSOR_DEFS) -c ykurcmd/ykurcmd.cpp -o ykurcmd/objs/ykurcmd.o

ykurcmd/objs/commandParser.o : ykurcmd/commandParser.cpp ykurcmd/stdafx.h ykurcmd/commandParser.h ykurcmd/usbcom.h 
	$(CPP) $(PREPROCESSOR_DEFS) -c ykurcmd/commandParser.cpp -o ykurcmd/objs/commandParser.o

ykurcmd/objs/usbcom.o : ykurcmd/usbcom.cpp ykurcmd/stdafx.h ykurcmd/hidapi.h ykurcmd/usbcom.h
	$(CPP) $(PREPROCESSOR_DEFS) -c ykurcmd/usbcom.cpp -o ykurcmd/objs/usbcom.o

clean :
	rm ykurcmd/bin/ykurcmd $(OBJS)

