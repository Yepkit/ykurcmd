


#include "ykur.h"




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
void Ykur::get_firmware_version(char *serial, char *major, char *minor, char *patch) {
    
    //Create command msg
    hid_report_out[0] = 0;
    
    hid_report_out[1] = 0x20;
    hid_report_out[2] = 0x01;

    //send HID report to board 
    sendHidReport(serial, hid_report_out, hid_report_in, 65);

    //handle board response HID report
    *major = hid_report_in[2];
    *minor = hid_report_in[3];
    *patch = hid_report_in[4];

    return;
}





