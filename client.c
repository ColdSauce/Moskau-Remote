#define _BSD_SOURCE
#include <stdio.h>

#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>


//TODO: Add all necessary include statements.

int display_image(Image img){
    //TODO: Implement!
}

int receive_mouse(char* ip, int port){
    //TODO: Change buffer size such that it's dynamic depending on the 
    //other person's screen size.
    #define BUFFER_SIZE 256
    #define NO_SPECIAL_PROTOCOL 0
    #define NO_FLAGS 0
    struct sockaddr_in server_address;
    char* server_name;
    Image buffer[BUFFER_SIZE];
    socklen_t address_size;
    int socket_file_descriptor;
    //AF_INET is to specify that one wants
    //IPv4 as the domain.
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, NO_SPECIAL_PROTOCOL);
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htonl(port);
    server_name = gethostbyname("localhost");
    inet_pton(AF_INET, server_name, &server_address.sin_addr);
    address_size = sizeof(server_address);
    if(connect(socket_file_descriptor, (struct sockaddr *)&server_address, address_size) == -1){
        exit(21); 
    }
    while(recv(socket_file_descriptor, buffer, sizeof(buffer), NO_FLAGS) != -1){
        display_image(buffer);
    }
}

int main(void){
    Display *dpy;
    Window root_window;
    dpy = XOpenDisplay(0);
    root_window = XRootWindow(dpy,0);
    

    //Commented out for now.
    //XWarpPointer(dpy, None, root_window, 0,0,0,0,x,y);
    XFlush(dpy);
    
    return 1;
}
