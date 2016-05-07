/****************************************************************************
 FileName:      commandParser.cpp
 Dependencies:  See INCLUDES section
 Compiler:      Visual Studio Community 2015
 Company:       Yepkit, Lda.

 Software License Agreement:

 Copyright (c) 2016 Yepkit Lda

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

*****************************************************************************
 File Description:

    Change History:
        Rev     Date            Description
        -----   -----------     -----------------------------------------
        0.0.1   2015-09-11      First Release


 ****************************************************************************
 *  Summary:
 *      Main program function
 *
 *
 *
*****************************************************************************/


// INCLUDES ---------------------------------------------------------------

#include <cstdlib>
#include <iostream>
#include <stdio.h>

#include "stdafx.h"
#include "commandParser.h"
#include "usbcom.h"

using namespace std;



enum cmdAction {
    	PORT_ON,
    	PORT_OFF,
    	LIST_DEVICES,
    	DISPLAY_SERIAL_NUMBER,
    	GET_PORT_STATUS,
	GET_RELAY_STATUS,
    	PRINT_HELP,
};

bool bySerial = false;



int commandParser(int argc, char** argv) {

  	char choice;
  	char cmd = 0x00;
	char addr = 0x00;
	enum cmdAction action = PRINT_HELP;
	char *iSerial=NULL;

  	if ( argc <= 1){
		printUsage();
		return 0;
    	}

	
  	//Parse input options and define action
	switch (argc) {
		case 2:
			if ((argv[1][0]=='-') && (argv[1][1]=='l')) {
				action = LIST_DEVICES;
			}
			break;
		case 3:
			// Single Option
			if ((argv[1][0] == '-') && (argv[1][1]=='d')) {
				action = PORT_OFF;
			} else if ((argv[1][0] == '-') && (argv[1][1]=='u')) {
				action = PORT_ON;
			} else {
				action = PRINT_HELP;
			} 	
			break;

		case 5:
			// Two Options
			if ((argv[1][0] == '-') && (argv[1][1]=='s')) {
				bySerial = true;
				iSerial = argv[2];	
			}
			if ((argv[3][0] == '-') && (argv[3][1]=='d')) {
				action = PORT_OFF;
			} else if ((argv[3][0] == '-') && (argv[3][1]=='u')) {
				action = PORT_ON;
			} else {
				action = PRINT_HELP;
			}
			break;

		default:
			printUsage();
			break;
	}



	//Get options values and execute action
	
	if ( action == PORT_OFF ) {
		if (bySerial) {
			switch(argv[4][0]) {
				case 'r':
					// Relay off
					cmd = 0x02;
					addr = 0x11;
                			commandBySerial(iSerial, cmd, addr);
					break;

            			case '1':
                			// Port 1 off
                			cmd = 0x02;
					addr = 0x01;
                			commandBySerial(iSerial, cmd, addr);
                			break;

            			case '2':
                			// Port 2 off
                			cmd = 0x02;
					addr = 0x02;
                			commandBySerial(iSerial, cmd, addr);
                			break;

            			case '3':
                			// Port 3 off
                			cmd = 0x02;
					addr = 0x03;
                			commandBySerial(iSerial, cmd, addr);
                			break;

            			case '4':
                			// Port 4 off
                			cmd = 0x02;
					addr = 0x04;
                			commandBySerial(iSerial, cmd, addr);
                			break;

            			case 'a':
                			// All ports off
                			cmd = 0x02;
					addr = 0x0a;
                			commandBySerial(iSerial, cmd, addr);
                			break;

            			default:
                			printUsage();
                			break;
        		}
		} else {
			switch(argv[2][0]) {
				case 'r':
				    // Relay off
				    cmd = 0x02;
				    addr = 0x11;
                    command(cmd, addr);
				    break;

            			case '1':
                			// Port 1 off
                			cmd = 0x02;
					addr = 0x01;
                			command(cmd, addr);
                			break;

            			case '2':
                			// Port 2 off
                			cmd = 0x02;
					addr = 0x02;
                			command(cmd, addr);
                			break;

            			case '3':
                			// Port 3 off
                			cmd = 0x02;
					addr = 0x03;
                			command(cmd, addr);
                			break;

            			case '4':
                			// Port 4 off
                			cmd = 0x02;
					addr = 0x04;
                			command(cmd, addr);
                			break;

            			case 'a':
                			// All ports off
                			cmd = 0x02;
					addr = 0x0a;
                			command(cmd, addr);
                			break;

            			default:
                			printUsage();
                			break;
        		}

		}
	}	



	if ( action == PORT_ON ) {
		if (bySerial) {
			switch(argv[4][0]) {
				case 'r':
					// Relay on
					cmd = 0x01;
					addr = 0x11;
                			commandBySerial(iSerial, cmd, addr);
					break;

            			case '1':
                			// Port 1 on
                			cmd = 0x01;
					addr = 0x01;
                			commandBySerial(iSerial, cmd, addr);
                			break;

            			case '2':
                			// Port 2 on
                			cmd = 0x01;
					addr = 0x02;
                			commandBySerial(iSerial, cmd, addr);
                			break;

            			case '3':
                			// Port 3 on
                			cmd = 0x01;
					addr = 0x03;
                			commandBySerial(iSerial, cmd, addr);
                			break;

            			case '4':
                			// Port 4 on
                			cmd = 0x01;
					addr = 0x04;
                			commandBySerial(iSerial, cmd, addr);
                			break;

            			case 'a':
                			// All ports on
                			cmd = 0x01;
					addr = 0x0a;
                			commandBySerial(iSerial, cmd, addr);
                			break;

            			default:
                			printUsage();
                			break;
        		}
		} else {
			switch(argv[2][0]) {
			    case 'r':
					// Relay on
					cmd = 0x01;
					addr = 0x11;
                    command(cmd, addr);
					break;

            		case '1':
                	// Port 1 on
                	cmd = 0x01;
					addr = 0x01;
                	command(cmd, addr);
                	break;

            		case '2':
                	// Port 2 on
                	cmd = 0x01;
					addr = 0x02;
                	command(cmd, addr);
                	break;

            		case '3':
                	// Port 3 on
                	cmd = 0x01;
					addr = 0x03;
                	command(cmd, addr);
                	break;

            		case '4':
                	// Port 4 on
                	cmd = 0x01;
					addr = 0x04;
                	command(cmd, addr);
                	break;

            		case 'a':
                	// All ports on
                	cmd = 0x01;
					addr = 0x0a;
                	command(cmd, addr);
                	break;

            		default:
                		printUsage();
                		break;
        		}

		}
	}	



	
	if ( action == LIST_DEVICES ) {
		printf("\nAttached YKUR Boards\n");
        	printf("\n---------------------\n");
        	listDevices();
	}


	if ( action == PRINT_HELP ) {
		printUsage();
	}


    return 0;
}


#ifdef LINUX
int printUsage(){

    printf("\n-------------------");
    printf("\n\tUsage:\n");
    printf("-------------------\n");
    printf("\nykurcmd -d r \t\tTurns OFF the in-board relay\n");
    printf("\nykurcmd -u r \t\tTurns ON the in-board relay\n");
    printf("\nykurcmd -s serial -d r \t\tTurns OFF the in-board relay of the board with the specified serial number\n");
    printf("\nykurcmd -s serial -u r \t\tTurns ON the in-board relay of the board with the specified serial number\n");
    printf("\nykurcmd -d port_number \t\tTurns OFF the port with the number port_number\n");
    printf("\nykurcmd -u port_number \t\tTurns ON the port with the number port_number\n");
    printf("\nykurcmd -l \t\tLists all currently attached YKUR boards\n");
    printf("\nykurcmd -s serial_number -d port_number \t\tTurns OFF the port with the number port_number for the board with the specified serial number\n");
    printf("\nykush -s serial_number -u port_number \t\tTurns ON the port with the number port_number for the board with the specified serial number\n\n\n");

    return 0;
}

#else

int printUsage(){

    printf("\n-------------------");
    printf("\n\tUsage:\n");
    printf("-------------------\n");
    printf("\nykurcmd.exe -d r \t\tTurns OFF the in-board relay\n");
    printf("\nykurcmd.exe -u r \t\tTurns ON the in-board relay\n");
    printf("\nykurcmd.exe -s serial -d r \t\tTurns OFF the in-board relay of the board with the specified serial number\n");
    printf("\nykurcmd.exe -s serial -u r \t\tTurns ON the in-board relay of the board with the specified serial number\n");
    printf("\nykurcmd.exe -d port_number \t\tTurns OFF the port with the number port_number\n");
    printf("\nykurcmd.exe -u port_number \t\tTurns ON the port with the number port_number\n");
    printf("\nykurcmd.exe -l \t\tLists all currently attached YKUR boards\n");
    printf("\nykurcmd.exe -s serial_number -d port_number \t\tTurns OFF the port with the number port_number for the board with the specified serial number\n");
    printf("\nykush.exe -s serial_number -u port_number \t\tTurns ON the port with the number port_number for the board with the specified serial number\n\n\n");

    return 0;
}

#endif



