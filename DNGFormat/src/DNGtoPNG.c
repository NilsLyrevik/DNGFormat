#include <stdio.h>
#include <stdlib.h>

// stb_import
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image/stb_image_write.h"

int run(const char * restrict DNGfile, const char * restrict output_dir){
    // check if output_dir ends with a slash
    char output_path[512];
    if (output_dir[strlen(output_dir) - 1] != '/') {
        // add a slash
        snprintf(output_path, sizeof(output_path), "%s/", output_dir);
    } else {
        // no need to add a slash
        snprintf(output_path, sizeof(output_path), "%s", output_dir);
    }
    // create final path with filename
    snprintf(output_path, sizeof(output_path), "%soutput.png", output_dir);

    // File opening with error handling
    FILE *file = fopen(output_path, "r");
    if (file != NULL) {
        fclose(file);
        fprintf(stderr, "File already exists. Please choose a different name.\n");
        return 7; // THIS MEANS ERROR WITH OPENING FILE
    }
    // load DNGfile
    FILE *dng_file = fopen(DNGfile, "rb");
    if (dng_file == NULL) {
        perror("Error opening DNG file");
        return 1; // THIS MEANS ERROR WITH OPENING FILE
    }

    unsigned int width, height, channels;
    fseek(dng_file, 8, SEEK_SET);
    
    fread(&width, sizeof(int), 1, dng_file);
    
    fseek(dng_file, 4, SEEK_CUR);
    
    fread(&height, sizeof(int), 1, dng_file);
    
    fseek(dng_file, 4, SEEK_CUR);
    
    fread(&channels, sizeof(uint16_t), 1, dng_file);
    
    fseek(dng_file, 6, SEEK_CUR); // Skip extra bytes if necessary
    
    printf("Width: %u, Height: %u, Channels: %u\n", width, height, channels);


    
    unsigned char *img = malloc(sizeof(unsigned char) * width * height * channels);

    for (int i = 0; i < width * height * channels; i++) {
        fread(&img[i], sizeof(unsigned char), 1, dng_file);
        fseek(dng_file, 1, SEEK_CUR);
    }

    fclose(dng_file);

    // Save the image using stb_image_write
    if (stbi_write_png(output_path, width, height, channels, img, width * channels) == 0) {
        fprintf(stderr, "Error writing PNG file\n");
        free(img);
        return 1; // THIS MEANS ERROR WITH CREATING FILE
    }
    

    // Free the image memory
    free(img);
    return 0; // SUCCESS
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <DNG file> <output directory>\n", argv[0]);
        return 1;
    }

    int result = run(argv[1], argv[2]);
    if (result != 0) {
        fprintf(stderr, "Error: %d\n", result);
        return result;
    }

    return 0; // SUCCESS
}