/*! \file */
#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

/*!
 * Actions identifiable by the frontend command parser.
 */
enum cmdAction {
    
    PORT_ON,
    PORT_OFF,
    LIST_DEVICES,
    DISPLAY_SERIAL_NUMBER,
    GET_PORT_STATUS,
    GET_RELAY_STATUS,
    PRINT_HELP,
    GET_FIRMWARE_VERSION,
    CONF_SET_PORT_DEFAULT,
    YKEMB_INTERFACE,
    CONFIG_COMMAND,
    PRINT_SOFTWARE_VERSION,
    
};


/*! First level USB command parser. */
int commandParser(int argc, char** argv);

int printUsage();

#define SOFTWARE_VERSION    "Rev.1.2.0"

#endif // COMMANDPARSER_H
