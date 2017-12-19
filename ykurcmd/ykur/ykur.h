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

        

};





//---------------------------------
//FUNCTIONS
//---------------------------------

void ykush3_cmd_parser(int argc, char** argv);


void ykush3_list_attached(void); 



#endif


