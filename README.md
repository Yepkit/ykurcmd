# ykurcmd


Control utility for Yepkit YKUR USB Relay board.


Description
===========

The *ykurcmd* is a console application for YKUR board control.
It can be used "as-is" or as a reference example for user implementation and integration into their own applications.

The core of the application is consolidated in two source code files, the *commandParser.cpp* and the *usbcom.cpp*.
The first contains the work-flow control and the second the communication functions.

This implementation makes use of hidapi open-source library which is portable across several operating systems.
We included a Visual Studio solution file for building in Windows. For Linux we included a Makefile for building the application.
Note that hidapi is not included in the source code and has to be obtained beforehand.


Licensing
=========

The *ykurcmd* source code is licensed under MIT license. 
Refer to [LICENSE](LICENSE.md) file.


Building
========

Before building the application get the [hidapi library](http://www.signal11.us/oss/hidapi/) and build it.
Follow the instructions in the hidapi documentation for building the library in the several systems. 

After building the hidapi library include the relevant hidapi files to *ykurcmd* project. 
Once this is done the *ykurcmd* application can be built.

The steps for Windows and Linux are detailed bellow.

Windows
-------
Copy to `ykur\ykurcmd\inc\` the following hidapi library files:
- hidapi.dll
- hidapi.exp
- hidapi.lib

also copy the *hidapi.dll* to `ykur\ykurcmd\bin` directory.

Open the `ykur\ykur.sln` with Microsoft Visual Studio and build the solution.
If the build process is successful the executable file will be created in the`ykur\ykurcmd\bin\` folder.

Allway ensure that the dynamically linked library is accessible to the executable.
We can install the hidapi.dll in the system or ensure that a copy of the file is in the same folder than the ykush.exe.


Linux
-----

To build the application, and run it, `libudev-dev, `libusb-1.0` and `libusb-1.0-dev` libraries must be installed in you system. For example, in Debian based systems do the following in a terminal.

```
$ sudo apt-get install libusb-1.0-0-dev libudev-dev
```

This installed the development files. Now install the binary library.

```
$ sudo apt-get install libusb-1.0-0
```

To build the application run:

```
$ sudo ./build.sh
```

Please note that this script downloads and builds the hidapi library, so an Internet connection is required.

There may be some dependencies that were not satisfied and cause the build process to fail. If that was the case, install the missing dependencies and re-run the `build.sh` script.

Finally install the hidapi shared libraries and the ykushcmd command by running the following script.

```
$ sudo ./install.sh
```



Using it
========

Please refer to the software User Manual which can be downloaded from the Documents and Resources section of the [YKUR product page](https://www.yepkit.com/product/300106/YKUR).

Some usage examples bellow.

Navigate to the `ykur/ykurcmd/bin` folder and run `ykurcmd -h` to print all the available command options and syntax.

Switching the on-board relay
----------------------------
To switch **ON** the on-board relay execute the command:
```
ykurcmd -u r
```

To switch the on-board relay **OFF** execute the command:
```
ykurcmd -d r
```

Switching the external relay driver ports
-----------------------------------------
To switch **ON** an external relay connected to a ykur driver port execute the command:
```
ykurcmd -u *port_number*
```
where *port_number* is 1, 2, 3 or 4 as identified in the ykur board silk screen.
As an example, if we want to switch **ON** an external port 1 the command is the following:
```
ykurcmd -u 1
```

To switch **OFF** an external relay connected to a ykur driver port execute the command:
```
ykurcmd -d *port_number*
```

Controlling a specific board when multiple YKUR boards are connected to the same host
-------------------------------------------------------------------------------------
When more than one ykur board is connected to the host, the action option in the command should be preceded by `-s
serial_number` option. The `serial_number` is the serial number of the ykur board where the action is to be executed.

To find out the serial number of a ykur board, connect it to the host and execute the command:
```
ykurcmd -l
```

This command will output the serial number of the connected board.
Note that if more than one board is connected when this command is executed the serial number of all connected boards
will be listed.

For example, assuming that two ykur boards are connected with the following serial numbers:
* Board 1 - YK00005
* Board 2 - YK00009
To switch **ON** the on-board relay of board 1 we execute the command:
```
ykurcmd -s YK00005 -u r
```
Note that on Windows the commands are executed using `ykurcmd.exe` instead of the `ykurcmd` showned above which is the
Linux version.


For more information and resources for the YKUSH board please visit the [yepkit website ykur page](https://www.yepkit.com/product/300106/YKUR).









