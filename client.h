#ifndef CLIENT
#define CLIENT

//An image is just a collection of bytes
typedef char* Image;

void draw_pixel(int x, int y, int color);
int display_image(Image img, int width, int height);

int send_screen(char* ip, int port);

#endif
