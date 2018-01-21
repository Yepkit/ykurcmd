
#include "ykur.h"
#include <string2val.h>
#include <string.h>
#include <stdio.h>



enum ykurAction {

    YKEMB_BYTE_WRITE,
    YKEMB_BYTE_READ,
    PRINT_HELP,
    SET_PORT_DEFAULT,
    GET_PORT_DEFAULT,
 
};






void ykur_config_command_parser(int argc, char** argv) {
    
    //----------------------------------------------------
    //Set port default state
    //ykurcmd [-s <serial_number>] -cwpd <port> <state>
    //----------------------------------------------------
    //Get port default
    //ykurcmd [-s <serial_number>] -crpd <port>
    //----------------------------------------------------

    Ykur *ykur = new Ykur();
    
    char* serial;
    bool bySerial=false;
    enum ykurAction action = PRINT_HELP; 
    unsigned char i2c_addr=0x50;
    char port;
    char state;
    
    
    
    if(argc < 3) {
        ykur->print_help(argv);
        return;
    }
    
    //Check if addressed by serial number
    serial = NULL;
    if(argv[1][0]=='-'){
        if(argv[1][1]=='s'){
            serial = argv[2];
            bySerial=true;
            
            if((argv[3][1]=='c')&&(argv[3][2]=='w')&&(argv[3][3]=='p')&&(argv[3][4]=='d')) {
                //Write parameter
                action = SET_PORT_DEFAULT;
                port = argv[4][0];
                state = argv[5][0];
                
            } else if((argv[3][1]=='c')&&(argv[3][2]=='r')&&(argv[3][3]=='p')&&(argv[3][4]=='d')) {
                //Read parameter
                action = GET_PORT_DEFAULT;
                port = argv[4][0];
                
            } else {
                action = PRINT_HELP;
            }
            
            
        } else if(argv[1][1]=='c') {
            if((argv[1][2]=='w')&&(argv[1][3]=='p')&&(argv[1][4]=='d')) {
                //Write parameter
                action = SET_PORT_DEFAULT;
                port = argv[2][0];
                state = argv[3][0];
                
            } else if((argv[1][2]=='r')&&(argv[1][3]=='p')&&(argv[1][4]=='d')) {
                //Read parameter
                action = GET_PORT_DEFAULT;
                port = argv[2][0];
                
            } else {
                action = PRINT_HELP;
            }
            
        } else {
            action = PRINT_HELP;
        }
            
    } else {
        action = PRINT_HELP;
    }
    
    switch(action) {
        case PRINT_HELP:
            ykur->print_help(argv);
            break;
            
        case SET_PORT_DEFAULT:
            ykur->set_port_default(serial, port, state);
            break;
        
        case GET_PORT_DEFAULT:
            //printf("\n%d\n", ykur->get_port_default(serial, port));
            break;
        
        default:
            ykur->print_help(argv);
            break;
            
    }
    
    
}






void ykemb_interface_command_parser(int argc, char** argv) {
    
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
        ykur->print_help(argv);
        return;
    }


    //Check if addressed by serial number
    serial = NULL;
    if(argv[1][0]=='-'){
        if(argv[1][1]=='s'){
            serial = argv[2];
            bySerial=true;
        }
    } else if(argv[1][0]=='y'){
        if(strlen(argv[1])==5) {
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
       printf("\nByte read: 0x%X\n", byte);
    } else {
        ykur->print_help(argv);
    }


    return;
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
    
    unsigned char pdef1=0;
    
    //1. Get current PDEF1 register
    read_byte_ykemb(serial, 0x50, 0x00, 0x01, &pdef1);
    
    //2. Define updated PDEF1 register
    switch(port){
        case 'r':
            if(state=='1'){
                pdef1 = pdef1 | 0x01;
            } else {
                pdef1 = pdef1 & 0xFE;
            }
            break;
        
        case '1':
            if(state=='1'){
                pdef1 = pdef1 | 0x02;
            } else {
                pdef1 = pdef1 & 0xFD;
            }
            break;    
        
        case '2':
            if(state=='1'){
                pdef1 = pdef1 | 0x04;
            } else {
                pdef1 = pdef1 & 0xFB;
            }
            break; 
            
        case '3':
            if(state=='1'){
                pdef1 = pdef1 | 0x08;
            } else {
                pdef1 = pdef1 & 0xF7;
            }
            break;
        
        case '4':
            if(state=='1'){
                pdef1 = pdef1 | 0x10;
            } else {
                pdef1 = pdef1 & 0xEF;
            }
            break;    
            
        default:
            break;
    }
    
    //3. Write new PDEF1 to YKEMB
    write_byte_ykemb(serial, 0x50, 0x00, 0x01, pdef1);
    
}





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
char Ykur::get_port_default(char *serial, char port) {
    
    unsigned char pdef1=0;
    
    //1. Get current PDEF1 register
    read_byte_ykemb(serial, 0x50, 0x00, 0x01, &pdef1);
    
    //2. Define updated PDEF1 register
    switch(port){
        case 'r':
            if(pdef1 & 0x01){
                printf("\nRelay is default On\n");
                return 1;
            } else {
                printf("\nRelay is default Off\n");
                return 0;
            }
            break;
        
        case '1':
            if(pdef1 & 0x02){
                printf("\nPort 1 is default On\n");
                return 1;
            } else {
                printf("\nPort 1 is default Off\n");
                return 0;
            }
            break;    
        
        case '2':
            if(pdef1 & 0x04){
                printf("\nPort 2 is default On\n");
                return 1;
            } else {
                printf("\nPort 2 is default Off\n");
                return 0;
            }
            break; 
            
        case '3':
            if(pdef1 & 0x08){
                printf("\nPort 3 is default On\n");
                return 1;
            } else {
                printf("\nPort 3 is default Off\n");
                return 0;
            }
            break;
        
        case '4':
            if(pdef1 & 0x10){
                printf("\nPort 4 is default On\n");
                return 1;
            } else {
                printf("\nPort 4 is default Off\n");
                return 0;
            }
            break;    
            
        default:
            return -1;
            break;
    }
    
    return -1;
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

   
    /*
    //DEBUG PRINT---------------------
    printf("\n\n!!! DEBUG PRINT !!!\n");
    printf("\nReceived USB message:");
    int i;
    unsigned char *p=hid_report_out;
    for(i=0; i<10; i++){
        printf("\nbyte[%d]=0x%X", i, *p++);
    }
    printf("\n\n!!! END OF DEBUG PRINT !!!\n");
    //---------------------------------
     */
    
    //
    //2. Transmit HID report
    //
    //send HID report to board 
    sendHidReport(serial, hid_report_out, hid_report_in, 65);

    /*
    //DEBUG PRINT---------------------
    printf("\n\n!!! DEBUG PRINT !!!\n");
    printf("\nReceived USB message:");
    //int i;
    //unsigned char *p=hid_report_in;
    p=hid_report_in;
    for(i=0; i<6; i++){
        printf("\nbyte[%d]=0x%X", i, *p++);
    }
    printf("\n\n!!! END OF DEBUG PRINT !!!\n");
    //---------------------------------
    */
    
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
    
    /*
    //DEBUG PRINT---------------------
    printf("\n\n!!! DEBUG PRINT !!!\n");
    printf("\nReceived USB message:");
    int i;
    unsigned char *p=hid_report_in;
    for(i=0; i<65; i++){
        printf("\nbyte[%d]=0x%X", i, *p++);
    }
    printf("\n\n!!! END OF DEBUG PRINT !!!\n");
    //---------------------------------
    */
    
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




void Ykur::print_help(char** argv) {
    
    printf("\n\n%s Help\n\n", argv[0]);
    printf("\n1. Port Switching Commands\n");
    printf("---------------------------\n");
    
    printf("\nWrite Port Default Parameter\n");
    printf("\nykurcmd [-s <serial_number>] -cwpd <port> <state>\n");
    
    printf("\nRead Port Default Parameter\n");
    printf("\nykurcmd [-s <serial_number>] -crpd <port>\n");
    
    printf("\n\nFor detailed explanation of all the commans and options please refer to the ykushcmd User Manual, available for download in the product page at yepkit.com");
    
    
    
}



