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
      return -1; // THIS MEANS ERROR WITH IMAGE
    }

    // check if output_dir ends with a slash
    if (output_dir[strlen(output_dir) - 1] != '/') {
        // add a slash
        snprintf(output_path, sizeof(output_path), "%s/", output_dir);
    } else {
        // no need to add a slash
        snprintf(output_path, sizeof(output_path), "%s", output_dir);
    }

    // create final path with filename
    snprintf(output_path, sizeof(output_path), "%soutput.dng", output_dir);

    // File opening with error handling
    FILE *file = fopen(output_path, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1; // THIS MEANS ERROR WITH CREATING FILE
    }


    uint16_t *DNGdata = malloc(sizeof(unsigned short) * width * height * channels + (sizeof(size_t) * 4));
    if (DNGdata == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return 2; // THIS MEANS ERROR WITH MEMORY
    }      

    // LOGIC FOR DNG HEADER
    // ----> This header was specifically designed to not make sense when reading it.
    // NAMING CONVENTION
    DNGdata[0] = 0b1110101 << 8 | 0b1000100;
    DNGdata[1] = 0b1100010 << 8 | 0b1101101; 
    DNGdata[2] = 0b1000111 << 8 | 0b1001110; 
    DNGdata[3] = 0b1000111 << 8 | 0b1001001;
    // WIDTH
    DNGdata[4] = width >> 8;
    DNGdata[5] = width;
    DNGdata[6] = 0;
    DNGdata[7] = 0;
    //HEIGHT
    DNGdata[8] = height >> 8;
    DNGdata[9] = height;
    DNGdata[10] = 0;
    DNGdata[11] = 0;
    //CHANNELS
    DNGdata[12] = channels;
    DNGdata[13] = 0;
    DNGdata[14] = 0;
    DNGdata[15] = 0;
    // LOGIC FOR HEADER DONE
    for (int i = 16; i < width * height * channels; i++){
        DNGdata[i] = img[i] << 8 | img[i];
    }

    size_t filelen = fwrite(DNGdata, sizeof(unsigned short), width * height * channels + (sizeof(size_t) * 4), file);
  

    fclose(file);
    free(DNGdata);
    stbi_image_free(img);
    return 0; // THIS MEANS CORRECT EXECUTION
}

int main (int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_image> <output_directory>\n", argv[0]);
        return 1;
    }

    const char *input = argv[1];
    const char *output_dir = argv[2];

    int result = run(input, output_dir);
    if (result != 0) {
        fprintf(stderr, "Error occurred: %d\n", result);
        return result;
    }

    printf("DNG file created successfully.\n");
    return 0;
}