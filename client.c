#include <stdio.h>

#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#include "client.h"


//TODO: Add all necessary include statements.
static Display* display = NULL;
static Window root_window = NULL;
static GC gc;

static Window new_window = NULL;

//Still have to see if it's faster to draw one pixel rectangles
//or one pixel lines.
void draw_pixel(int x, int y,int color){
    XSetForeground(display, gc, color);
    XDrawLine(display, new_window, gc, x, y, x, y);
}

int display_image(char* img,int width, int height){
    if(display == NULL || &new_window == NULL){
        return -1;
    }
    
    //The following is just to test writing to the screen.
    //Somehow ended up spending 2 hours making different kinds 
    //of patterns instead of actually working on the project haha
    int high = 0;
    for(int x = 0; x < 2000; x++){
        for(int y = 0;y < 2000;y++){
            if(rand() % 10 == 4){
                draw_pixel(x,y,((x+0xFF0000*y + 1) | 0xFFFFFF));
            }
            else{
                draw_pixel(x,y,((x+0xFF0000*y + 1) & 0xFFFFFF));
            }
        }
    }
    XFlush(display);
    return 1;
}

int receive_mouse(char* ip, int port){
    //TODO: Change buffer size such that it's dynamic depending on the 
    //other person's screen size.
    #define BUFFER_SIZE 256
    #define NO_SPECIAL_PROTOCOL 0
    #define NO_FLAGS 0
    struct sockaddr_in server_address;
    char* server_name;
    char buffer[BUFFER_SIZE];
    socklen_t address_size;
    int socket_file_descriptor;
    //AF_INET is to specify that one wants
    //IPv4 as the domain.
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, NO_SPECIAL_PROTOCOL);
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htonl(port);
    server_name = (char*) gethostbyname("localhost");
    inet_pton(AF_INET, server_name, &server_address.sin_addr);
    address_size = sizeof(server_address);
    if(connect(socket_file_descriptor, (struct sockaddr *)&server_address, address_size) == -1){
        exit(21); 
    }
    while(recv(socket_file_descriptor, buffer, sizeof(buffer), NO_FLAGS) != -1){
        display_image(buffer,500,500);
    }
    return 1;
}

int main(void){
    display = XOpenDisplay(0);
    root_window = XRootWindow(display,0);
    new_window = XCreateSimpleWindow(display, root_window, 20, 20, 500, 500, 2, 2, WhitePixel(display, 0));
   
    XMapWindow(display, new_window);
    XGCValues gv;
    gv.line_width = 1;
    gc = XCreateGC(display, new_window, GCLineWidth, &gv);
    XSetForeground(display, gc, 0xFF0000);

    //Commented out for now.
    //XWarpPointer(dpy, None, root_window, 0,0,0,0,x,y);
    while(1){
        display_image(NULL,700,700);
    }
    return 1;
}
