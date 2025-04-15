#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// stb_import
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image/stb_image_write.h"

int run(const char * restrict input, const char * restrict output_dir){

    // make sure there is enough for a long path
    char output_path[512];

    //load image with stbi lib
    int width,height,channels;
    unsigned char *img = stbi_load(input, &width, &height, &channels, 0);
  
    // ERROR HANDLING, we should never reach here
    if(img == NULL){
      return -1;
    }
    // create final path with filename
    snprintf(output_path, sizeof(output_path), "%soutput.dng", output_dir);

    // File opening with error handling
    FILE *file = fopen(output_path, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    const short *DNGdata = malloc(sizeof(unsigned short) * width * height * channels + (sizeof(size_t) * 4));



}