CUR_PATH = $(shell echo $(PWD))
OBJS = $(addprefix ykurcmd/objs/,ykurcmd.o commandParser.o usbcom.o yk_usb_device.o ykur.o)
LIBS = -lhidapi-libusb -lusb-1.0 -ludev
LOADPATHS = -L$(CUR_PATH)/ykurcmd/inc
INCLUDEPATHS= -I$(CUR_PATH)/ykurcmd/usb_device -I$(CUR_PATH)/ykurcmd/ykur -I$(CUR_PATH)/ykurcmd/inc
PREPROCESSOR_DEFS = -DLINUX
CPP = g++

ykurcmd : $(OBJS)
	$(CPP) $(LOADPATHS) -o ykurcmd/bin/ykurcmd $(OBJS) $(LIBS)


ykurcmd/objs/ykurcmd.o : ykurcmd/ykurcmd.cpp ykurcmd/stdafx.h ykurcmd/commandParser.h
	$(CPP) $(PREPROCESSOR_DEFS) $(INCLUDEPATHS) -c ykurcmd/ykurcmd.cpp -o ykurcmd/objs/ykurcmd.o

ykurcmd/objs/commandParser.o : ykurcmd/commandParser.cpp ykurcmd/stdafx.h ykurcmd/commandParser.h ykurcmd/usbcom.h 
	$(CPP) $(PREPROCESSOR_DEFS) $(INCLUDEPATHS) -c ykurcmd/commandParser.cpp -o ykurcmd/objs/commandParser.o

ykurcmd/objs/usbcom.o : ykurcmd/usbcom.cpp ykurcmd/stdafx.h ykurcmd/hidapi.h ykurcmd/usbcom.h
	$(CPP) $(PREPROCESSOR_DEFS) $(INCLUDEPATHS) -c ykurcmd/usbcom.cpp -o ykurcmd/objs/usbcom.o
	
ykurcmd/objs/yk_usb_device.o : ykurcmd/usb_device/yk_usb_device.cpp ykurcmd/usb_device/yk_usb_device.h
	$(CPP) $(PREPROCESSOR_DEFS) $(INCLUDEPATHS) -c ykurcmd/usb_device/yk_usb_device.cpp -o ykurcmd/objs/yk_usb_device.o

ykurcmd/objs/ykur.o : ykurcmd/ykur/ykur.cpp ykurcmd/usb_device/yk_usb_device.h
	$(CPP) $(PREPROCESSOR_DEFS) $(INCLUDEPATHS) -c ykurcmd/ykur/ykur.cpp -o ykurcmd/objs/ykur.o

clean :
	rm ykurcmd/bin/ykurcmd $(OBJS)

