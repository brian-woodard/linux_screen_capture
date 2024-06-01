#include <math.h>
#include <proj.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stdint.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void ScreenCapture()
{
   Display* display = XOpenDisplay(":1");
   Window root = DefaultRootWindow(display);

   XWindowAttributes attributes = {0};
   XGetWindowAttributes(display, root, &attributes);

   XImage* img = XGetImage(display, root, 0, 0 , attributes.width, attributes.height, AllPlanes, ZPixmap);

   if (img)
   {
      int bytes_per_pixel = img->bits_per_pixel / 8;

      // swap red and blue channels
      for (int i = 0; i < (attributes.width * attributes.height * bytes_per_pixel); i += bytes_per_pixel)
      {
         uint8_t tmp = img->data[i];
         img->data[i] = img->data[i+2];
         img->data[i+2] = tmp;
      }

      stbi_write_png("test.png", attributes.width, attributes.height, bytes_per_pixel, img->data, 0);
   
      XDestroyImage(img);
   }

   XCloseDisplay(display);
}

int main()
{
   ScreenCapture();
}
