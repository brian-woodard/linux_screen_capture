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

uint8_t* ImageFromDisplay(int& Width, int& Height, int& BytesPerPixel)
{
   uint8_t* image_data = nullptr;
   uint64_t image_size = 0;

   Display* display = XOpenDisplay(":1");
   Window root = DefaultRootWindow(display);

   XWindowAttributes attributes = {0};
   XGetWindowAttributes(display, root, &attributes);

   if (Width > attributes.width)
      Width = attributes.width;

   if (Height > attributes.height)
      Height = attributes.height;

   printf(">>> get image %dx%d\n", Width, Height);
   XImage* img = XGetImage(display, root, 0, 0 , Width, Height, AllPlanes, ZPixmap);
   printf(">>> got image\n");

   if (img)
   {
      BytesPerPixel = img->bits_per_pixel / 8;

      image_size = Width * Height * BytesPerPixel;
      image_data = new uint8_t[image_size];

      printf(">>> copy image: %d bytes\n", image_size);
      memcpy(image_data, img->data, image_size);
   
      printf(">>> destroy image\n");
      XDestroyImage(img);
   }

   XCloseDisplay(display);

   return image_data;
}

int main()
{
   int      width = 4096;
   int      height = 4096;
   int      bytes_per_pixel = 0;

   uint8_t* img = ImageFromDisplay(width, height, bytes_per_pixel);

   printf(">>> write to png\n");
   stbi_write_png("test.png", width, height, bytes_per_pixel, img, 0);
}
