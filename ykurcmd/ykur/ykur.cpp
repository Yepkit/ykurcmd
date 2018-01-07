
#include "ykur.h"
#include <string2val.h>
#include <string.h>



enum ykurAction {

    YKEMB_BYTE_WRITE,
    YKEMB_BYTE_READ,
    PRINT_HELP,
 
};





int ykemb_interface_command_parser(int argc, char** argv) {
    
    unsigned char i2c_ykemb_addr[3];
    unsigned char ykemb_mem_addrH[2];
    unsigned char ykemb_mem_addrL[2];
    unsigned char mem_addrH, mem_addrL;
    unsigned char ykemb_byte[2];
    unsigned char byte;
    char* serial;
    bool bySerial=false;
    enum ykurAction action = PRINT_HELP; 
    unsigned char i2c_addr=0x50;

    Ykur *ykur = new Ykur();

    if(argc < 6) {
        //ykur->print_help();
        return 0;
    }


    //Check if addressed by serial number
    serial = NULL;
    if(argv[1][0]=='-'){
        if(argv[1][1]=='s'){
            serial = argv[2];
            bySerial=true;
        }
    } else if(argv[1][0]=='y'){
        if(strlen(argv[1])!=5) {
           if((argv[1][1]=='k')&&(argv[1][2]=='e')&&(argv[1][3]=='m')&&(argv[1][4]=='b')){
                if(argv[2][0]=='-'){
                    if(strlen(argv[2])==2){
                        if(argv[2][1]=='w'){
                            action = YKEMB_BYTE_WRITE;
                        } else if (argv[2][1]=='r'){
                            action = YKEMB_BYTE_READ;
                        }
                    }
                }
           } 
        }     
    }


    if(bySerial){   //When serial number is specified

        //get I2C ykemb device address
        i2c_ykemb_addr[0]=char2int(argv[5][0]);
        i2c_ykemb_addr[1]=char2int(argv[5][1]);
        i2c_ykemb_addr[2]=char2int(argv[5][2]); 
        //convert to single byte
        i2c_addr = i2c_addr + i2c_ykemb_addr[0]*4 + i2c_ykemb_addr[1]*2 + i2c_ykemb_addr[2];



        //get memory address
        ykemb_mem_addrH[0]=argv[6][2];
        ykemb_mem_addrH[1]=argv[6][3];
        ykemb_mem_addrL[0]=argv[7][2];
        ykemb_mem_addrL[1]=argv[7][3];   

        //convert mem_addr from string to hexadecimal
        hex2bin(ykemb_mem_addrH, &mem_addrH, 2);
        hex2bin(ykemb_mem_addrL, &mem_addrL, 2);

        //get byte to be stored
        if(action == YKEMB_BYTE_WRITE){
            ykemb_byte[0]=argv[8][2];
            ykemb_byte[1]=argv[8][3];
            
            //convert byte from ascii to binary
            hex2bin(ykemb_byte, &byte, 2);
        }
        
    } else {    //When serial number is not specified

        //get I2C ykemb device address
        i2c_ykemb_addr[0]=char2int(argv[3][0]);
        i2c_ykemb_addr[1]=char2int(argv[3][1]);
        i2c_ykemb_addr[2]=char2int(argv[3][2]); 
        
        //get memory address
        ykemb_mem_addrH[0]=argv[4][2];
        ykemb_mem_addrH[1]=argv[4][3];
        ykemb_mem_addrL[0]=argv[5][2];
        ykemb_mem_addrL[1]=argv[5][3];

        //convert mem_addr from string to hexadecimal
        hex2bin(ykemb_mem_addrH, &mem_addrH, 2);
        hex2bin(ykemb_mem_addrL, &mem_addrL, 2);

        //get byte to be stored
        if(action == YKEMB_BYTE_WRITE){
            ykemb_byte[0]=argv[6][2];
            ykemb_byte[1]=argv[6][3];
            
            //convert byte from ascii to binary
            hex2bin(ykemb_byte, &byte, 2);
        }

    }
    
            
    if(action==YKEMB_BYTE_WRITE){
       ykur->write_byte_ykemb(serial, i2c_addr, mem_addrH, mem_addrL, byte); 
    } else if(action==YKEMB_BYTE_READ){
       ykur->read_byte_ykemb(serial, i2c_addr, mem_addrH, mem_addrL, &byte); 
    } else {
        //print help
        //ToDo
    }


    return 0;
}  





//---------------------------------------------------------------------
//
//              Ykur Class Implementation
//
//---------------------------------------------------------------------





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
void Ykur::set_port_default(char *serial, char port, char state) {
    unsigned char st=0;

    //Create command msg
    hid_report_out[0] = 0;


    if(state=='1') {
        st=1;
    }

    switch(port) {
        case 'r':
            hid_report_out[1] = 0x10;        
            hid_report_out[2] = 0x01;        
            hid_report_out[3] = 0x00;        
            hid_report_out[4] = st;        
            break;

        case '1':
            hid_report_out[1] = 0x10;        
            hid_report_out[2] = 0x01;        
            hid_report_out[3] = 0x01;        
            hid_report_out[4] = st;        
            break;

        case '2':
            hid_report_out[1] = 0x10;        
            hid_report_out[2] = 0x01;        
            hid_report_out[3] = 0x02;        
            hid_report_out[4] = st;        
            break;

        case '3':
            hid_report_out[1] = 0x10;        
            hid_report_out[2] = 0x01;        
            hid_report_out[3] = 0x03;        
            hid_report_out[4] = st;        
            break;

        case '4':
            hid_report_out[1] = 0x10;        
            hid_report_out[2] = 0x01;        
            hid_report_out[3] = 0x04;        
            hid_report_out[4] = st;        
            break;


        default:
            return;
            break;
    }
    
    //send HID report to board 
    sendHidReport(serial, hid_report_out, hid_report_in, 65);

}



/***********************************************************************
 * Method: write_byte_ykemb
 *
 * Description:
 *
 *
 *
 ************************************************************************/
char Ykur::write_byte_ykemb(char* serial, unsigned char i2c_addr, unsigned char mem_addr_msb, unsigned char mem_addr_lsb, unsigned char byte) {
    
    //
    //1. Prepare HID report
    //
    //Create command msg
    hid_report_out[0] = 0;          //HID report id
    hid_report_out[1] = 0x10;
    hid_report_out[2] = 0x01;       //action = write
    hid_report_out[3] = i2c_addr;
    hid_report_out[4] = mem_addr_msb;
    hid_report_out[5] = mem_addr_lsb;
    hid_report_out[6] = byte;

   

    //
    //2. Transmit HID report
    //
    //send HID report to board 
    sendHidReport(serial, hid_report_out, hid_report_in, 65);


    //
    //3. Process device response HID report
    switch(hid_report_in[0]) {

        case 0x10:
            //command processed by YKUR
            if(hid_report_in[1]){
                //Command execution on YKUR returned an error
                return 2;
            }
            return 0; //success
            break;

        default:
            return 1;   //error
            break;
    }

    return 1; //error
}




/***********************************************************************
 * Method: read_byte_ykemb
 *
 * Description:
 *
 *
 *
 ************************************************************************/
char Ykur::read_byte_ykemb(char* serial, unsigned char i2c_addr, unsigned char mem_addr_msb, unsigned char mem_addr_lsb, unsigned char* byte_buffer) {

    //
    //1. Prepare HID report
    //
    //Create command msg
    hid_report_out[0] = 0;          //HID report id
    hid_report_out[1] = 0x10;
    hid_report_out[2] = 0x02;       //action = read
    hid_report_out[3] = i2c_addr;
    hid_report_out[4] = mem_addr_msb;
    hid_report_out[5] = mem_addr_lsb;

   

    //
    //2. Transmit HID report
    //
    //send HID report to board 
    sendHidReport(serial, hid_report_out, hid_report_in, 65);


    //
    //3. Process device response HID report
    switch(hid_report_in[0]) {

        case 0x10:
            //command processed by YKUR
            if(hid_report_in[1]){
                //Command execution on YKUR returned an error
                return 2;
            }
            *byte_buffer = hid_report_in[2];
            return 0; //success
            break;

        default:
            return 1;   //error
            break;
    }

    return 1; //error

}






