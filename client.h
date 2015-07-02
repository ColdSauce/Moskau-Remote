#ifndef CLIENT
#define CLIENT

//An image is just a collection of bytes
typedef Image char*

int display_image(Image img);
int send_screen(char* ip, int port);

#endif
