/*******************************************************************************
Copyright 2017 Yepkit Lda (www.yepkit.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/


#ifndef _YKUR_H_
#define _YKUR_H_


#include <yk_usb_device.h>





//------------------------------------
//CLASSES
//------------------------------------

class Ykur : public UsbDevice  
{
    public:

        /**********************************************************
         *
         * Constructor
         *
         **********************************************************/
        Ykur()
            : UsbDevice(0x04D8, 0xF1CB)
        {     
        }



        
        /***********************************************************************
         * Method: get_firmware_version
         *
         * Description:
         *
         *  Gets the firmware version loaded in a YKUR board.
         *
         * Inputs:
         *
         *  serial      - Pointer to the serial number string
         *
         *  major       - Pointer to a char to where the version Major value
         *              should be written
         *
         *  minor       - Pointer to a char to where the version Minor value
         *              should be written
         *
         *  patch       - Pointer to a char to where the version Patch value 
         *              should be written
         *
         ************************************************************************/
        void get_firmware_version(char *serial, char *major, char *minor, char *patch);

         
        
        /***********************************************************************
         * Method: set_port_default
         *
         * Description:
         *
         *  Sets the default state of a YKUR port.
         *
         * Inputs:
         *
         *  serial      - Pointer to the serial number string
         *
         *  port        - Target port number in ASCII
         *
         *  state       - Port state. 0 -> Off; 1 -> On; (values in ASCII)
         *
         *
         ************************************************************************/
        void set_port_default(char *serial, char port, char state);
        
        
        /***********************************************************************
         * Method: get_port_default
         *
         * Description:
         *
         *  Sets the default state of a YKUR port.
         *
         * Inputs:
         *
         *  serial      - Pointer to the serial number string
         *
         *  port        - Target port number in ASCII
         *
         *
         * Return value:
         * 
         *  Returns the 1 or 0 representing the default state.
         *
         ************************************************************************/
        char get_port_default(char *serial, char port);
        

        
        
        /***********************************************************************
         * Method: write_byte_ykemb
         *
         * Description:
         *
         *
         *
         ************************************************************************/
        char write_byte_ykemb(char* serial, unsigned char i2c_addr, unsigned char mem_addr_msb, unsigned char mem_addr_lsb, unsigned char byte);

        
        
        /***********************************************************************
         * Method: read_byte_ykemb
         *
         * Description:
         *
         *
         *
         ************************************************************************/
        char read_byte_ykemb(char* serial, unsigned char i2c_addr, unsigned char mem_addr_msb, unsigned char mem_addr_lsb, unsigned char* byte_buffer);


        /***********************************************************************
         * Method: get_port_status
         *
         * Description:
         *  
         *  Fetch and return the switching state of a YKUR port.
         *  
         * Input:
         * 
         *  serial      - Pointer to string with the board serial number.
         *                Null if no serial is used.
         *
         *  port        - Port number in ASCII.
         *                  "r" - Relay
         *                  "1" - Port 1
         *                  "2" - Port 2
         *                  "3" - Port 3
         *                  "4" - Port 4
         *
         * Return values:
         * 
         *  -1      Error
         *  0       Port OFF
         *  1       Port ON
         * 
         ************************************************************************/
        char get_port_status(char *serial, char port);
        
        
        
        void print_help(char** argv);
};





//---------------------------------
//FUNCTIONS
//---------------------------------

void ykemb_interface_command_parser(int argc, char** argv); 

void ykur_config_command_parser(int argc, char** argv);



#endif


