#include <stdio.h>
#include <stdlib.h>

// stb_import
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image/stb_image_write.h"

int run(const char *input, const char *o_dir){

    //load image with stbi lib
    int width,height,channels;
    unsigned char *img = stbi_load(input, &width, &height, &channels, 0);
  
    // ERROR HANDLING, we should never reach here
    if(img == NULL){
      return -1;
    }



}