#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "string.h"
#include "motor_control.h" 


extern volatile int forward;

// CGI handler which is run when a request for /robot.cgi is detected
const char * cgi_robot_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    // Check if a request for robot control has been made (/robot.cgi?robot=x)
    if (strcmp(pcParam[0], "robot") == 0) {
        // Look at the argument to check if the robot is to be turned on (x=1) or off (x=0)
        if (strcmp(pcValue[0], "0") == 0) {
            // Turn off the robot 
            forward = 0;
        } else if (strcmp(pcValue[0], "1") == 0) {
            // Turn on the robot 
            forward = 1; 
        }
    }
    
    // Send the index page back to the user
    return "/index.shtml";
}

// tCGI Struct
// Fill this with all of the CGI requests and their respective handlers
static const tCGI cgi_handlers[] = {
    {
        // HTML request for "/robot.cgi" triggers cgi_handler
        "/robot.cgi", cgi_robot_handler
    },
};


void cgi_init(void)
{  
    http_set_cgi_handlers(cgi_handlers, 1);
}
