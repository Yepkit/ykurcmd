/*! \file */
/*
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
*/


// INCLUDES ---------------------------------------------------------------

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "platformdefs.h"
#include "stdafx.h"
#include "commandParser.h"
#include "usbcom.h"
#include <ykur.h>

using namespace std;




bool bySerial = false;



int commandParser(int argc, char** argv) {

    char choice;
    char cmd = 0x00;
    char addr = 0x00;
    enum cmdAction action = PRINT_HELP;
    char *iSerial=NULL;
    Ykur *ykur = new Ykur();

    if ( argc <= 1){
        ykur->print_help(argv);
            return 0;
    }


    //Parse input options and define action
    switch (argc) {
        /*! If single command: 
         */
        case 2:
            if ((argv[1][0]=='-') && (argv[1][1]=='l')) {
                action = LIST_DEVICES; //! * List attached YKUR devices command.
            } else if ((argv[1][0]=='-') && (argv[1][1]=='v')) {
                action = GET_FIRMWARE_VERSION;  //! * Get YKUR firmware version for attached board command (no serial provided).
            } else if ((argv[1][0] == '-') && (argv[1][1]=='-')) {
                if((argv[1][2] == 'v') && (argv[1][3]=='e') && (argv[1][4]=='r') && (argv[1][5]=='s') && (argv[1][6]=='i')) {
                    action = PRINT_SOFTWARE_VERSION;    //! * Display ykurcmd version command.
                }
            }
            break;

        case 3:
            /*! If one option command without serial: 
             */
            if ((argv[1][0] == '-') && (argv[1][1]=='d')) {
                action = PORT_OFF;  //! * Switch port off.
            } else if ((argv[1][0] == '-') && (argv[1][1]=='u')) {
                action = PORT_ON;   //! * Switch port on.
            } else if ((argv[1][0] == '-') && (argv[1][1]=='g')) {
                action = GET_PORT_STATUS;   //! * Get port or relay status.
            } else {
                action = PRINT_HELP;
            } 	
            break;

        case 4:
            /*! If one option command with serial: 
             */
            if ((argv[1][0]=='-')&&(argv[1][1]=='s')) {
                bySerial = true;
                iSerial = argv[2];  
                if((argv[3][0]=='-')&&(argv[3][1]=='v')) {
                    action = GET_FIRMWARE_VERSION;  //! * Get YKUR firmware version command.
                } else {
                    action = PRINT_HELP;
                }
            } 
            break;

        case 5:
            /*! If one option command: 
             */
            if ((argv[1][0] == '-') && (argv[1][1]=='s')) {
                    bySerial = true;
                    iSerial = argv[2];	
            }
            if ((argv[3][0] == '-') && (argv[3][1]=='d')) {
                    action = PORT_OFF;
            } else if ((argv[3][0] == '-') && (argv[3][1]=='u')) {
                    action = PORT_ON;      
            } else if ((argv[3][0] == '-') && (argv[3][1]=='g')) {
                    action = GET_PORT_STATUS; 
            } else {
                    action = PRINT_HELP;
            }
            break;


        default:
            ykur->print_help(argv);
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
                                ykur->print_help(argv);
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
                                ykur->print_help(argv);
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
                                ykur->print_help(argv);
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
                        ykur->print_help(argv);
                            break;
                    }

            }
    }	


    switch(action) {
        case PRINT_SOFTWARE_VERSION:
            printf("\n\nSoftware ykurcmd version: %s\n\n", SOFTWARE_VERSION);
            break;
           
        case GET_PORT_STATUS:
            char port_status;
            
            
            if(bySerial) {
                port_status = ykur->get_port_status(argv[2], argv[4][0]);
                if(port_status == 1) {
                    printf("\nPort %c is ON\n\n", argv[4][0]);
                } else if (port_status == 0) {
                    printf("\nPort %c is OFF\n\n", argv[4][0]);
                } else {
                    printf("\nUnable to get status.\n\n");
                    
                    printf("Troubleshooting\n");
                    printf("---------------\n");
                    printf("This can happen due to the following reasons:\n");
                    printf("1. The YKUR board is not properly attached to the Host (e.g., PC);\n");
                    printf("2. The YKUR board firmware version does not support the get status command.\n");
     
                    printf("\nGet Port Status command is only supported by boards with\n");
                    printf("Firmware version greater than Rev.1.2.0.\n\n");
                    printf("To check the board firmware version run the following command:\n");  
                    printf("\n%s [-s <serial_number>] -v\n\n", argv[0]);
                }
            } else {
                port_status = ykur->get_port_status(NULL, argv[2][0]);
                if(port_status == 1) {
                    printf("\nPort %c is ON\n\n", argv[2][0]);
                } else if (port_status == 0) {
                    printf("\nPort %c is OFF\n\n", argv[2][0]);
                } else {
                    printf("\nUnable to get status.\n\n");
                    
                    printf("Troubleshooting\n");
                    printf("---------------\n");
                    printf("This can happen due to the following reasons:\n");
                    printf("1. The YKUR board is not properly attached to the Host (e.g., PC);\n");
                    printf("2. The YKUR board firmware version does not support the get status command.\n");
     
                    printf("\nGet Port Status command is only supported by boards with\n");
                    printf("Firmware version greater than Rev.1.2.0.\n\n");
                    printf("To check the board firmware version run the following command:\n");  
                    printf("\n%s [-s <serial_number>] -v\n\n", argv[0]);
                }
            }
            
            
            
            
            break;
          
        default:
            
            break;
    }

	
    if ( action == LIST_DEVICES ) {
            printf("\nAttached YKUR Boards\n");
            printf("\n---------------------\n");
            listDevices();
    }



    if ( action == GET_FIRMWARE_VERSION ) {
        //Ykur *ykur = new Ykur();
        char major, minor, patch;

        if (bySerial) {
            ykur->get_firmware_version(iSerial, &major, &minor, &patch);
            printf("\nFirmware Version: Rev.%d.%d.%d\n\n",major, minor, patch);
        } else {
            ykur->get_firmware_version(NULL, &major, &minor, &patch);
            printf("\nFirmware Version: Rev.%d.%d.%d\n\n", major, minor, patch);
        }
    }



    if (action == CONFIG_COMMAND) {
        ykur_config_command_parser(argc, argv);
    }




    if(action == YKEMB_INTERFACE){
        ykemb_interface_command_parser(argc, argv);
    }



    if ( action == PRINT_HELP ) {
            ykur->print_help(argv);
    }


    return 0;
}




