#include <stdio.h>
#include <stdlib.h>
#include <wand/MagicWand.h>


//Whenever an error occurs, we call this method
void image_exception(const MagickWand *wand){
    char *desc;
    ExceptionType severity;

    desc = MagickGetException(wand, &severity);
    fprintf(stderr, "%s %s %ld %s\n", GetMagickModule(), desc);
    desc = (char *) MagickRelinquishMemory(desc);

}

//Create a magickwand object handle
void image_init(void){

    MagickWandGenesis();

}

//Terminates a magickwand object handle
void image_term(void){

    MagickWandTerminus();

}

//releases the image from the memory 
void image_destroy(MagickWand *wand){

    if (wand)
        DestroyMagickWand(wand);
}

static MagickWand *image_new(const image_read_params_t *params){
    MagickWand *wand = NULL;

    /* Create wand */
    wand = NewMagickWand();
    if (!wand) {
        image_destroy(wand);
        return NULL;
    }

    /* Set width and height of image */
    if (MagickSetSize(wand, params->width, params->height) == MagickFalse) {
        image_exception(wand);
        image_destroy(wand);
        return NULL;
    }

    /* Set format of image */
    if (MagickSetFormat(wand, params->format) == MagickFalse) {
        image_exception(wand);
        image_destroy(wand);
        return NULL;
    }

    /* Set color depth of image */
    if (MagickSetDepth(wand, params->depth) == MagickFalse) {
        image_exception(wand);
        image_destroy(wand);
        return NULL;
    }

    return wand;
}

MagickWand *image_read_blob(const image_read_params_t *params,
                                const unsigned char *data,
                                const size_t data_size){
    MagickWand *wand;

    /* Create new wand */
    wand = iac_image_new(params);
    if (!wand)
        return NULL;

    /* Read blob into wand */
    if (MagickReadImageBlob(wand, data, data_size) == MagickFalse) {
        iac_image_exception(wand);
        iac_image_destroy(wand);
        return NULL;
    }

    return wand;
}

//Creates an MagickWand object from a picture taken by the cameras
MagickWand *image_read_file(const image_read_params_t *params,
                                const char *filename){
    MagickWand *wand;

    /* Create new wand */
    wand = image_new(params);
    if (!wand)
        return NULL;

    /* Read file into wand */
    if (MagickReadImage(wand, filename) == MagickFalse) {
        iac_image_exception(wand);
        iac_image_destroy(wand);
        return NULL;
    }

    return wand;
}

MagickWand ***image_tiles(MagickWand *wand, const unsigned int divs){
    MagickWand ***wands;
    size_t width;
    size_t height;
    unsigned int i, j;

    /* Calculate width and height of tile */
    width = MagickGetImageWidth(wand);
    width = width / divs + (width % divs ? 1 : 0);
    height = MagickGetImageHeight(wand);
    height = height / divs + (height % divs ? 1 : 0);

    /* Allocate memory for rows */
    wands = malloc(sizeof(MagickWand **) * divs);
    for (i = 0; i < divs; i++) {

        /* Allocate memory for columns */
        wands[i] = malloc(sizeof(MagickWand *) * divs);
        for (j = 0; j < divs; j++) {
            wands[i][j] = NULL;

            /* Crop image to tiles */
            wands[i][j] = CloneMagickWand(wand);
            if (MagickCropImage(wands[i][j],
                                width,
                                height,
                                (ssize_t) (j * width),
                                (ssize_t) (i * height)) == MagickFalse) {
                iac_image_exception(wands[i][j]);
                iac_image_destroy(wands[i][j]);
                /* Free previous wands */
                while (--i >= 0) {
                    while (--j >= 0)
                        if (wands[i][j])
                            DestroyMagickWand(wands[i][j]);
                    free(wands[i]);
                }
                free(wands);
                return NULL;
            }
        }
    }

    return wands;
}

void image_tiles_destroy(MagickWand ***wands, const unsigned int divs){
    unsigned int i, j;

    for (i = 0; i < divs; i++) {
        for (j = 0; j < divs; j++)
            if (wands[i][j])
                DestroyMagickWand(wands[i][j]);
        free(wands[i]);
    }
    free(wands);

}



unsigned char *image_get_blob(MagickWand *wand, size_t *data_size){
    unsigned char *blob;

    /* Set image format of blob */
    if (MagickSetImageFormat(wand, IAC_IMAGE_BLOB_FORMAT) == MagickFalse) {
        iac_image_exception(wand);
        return NULL;
    }

    /* Get image blob from wand */
    blob = MagickGetImageBlob(wand, data_size);
    if (blob == NULL) {
        iac_image_exception(wand);
        return NULL;
    }

    return blob;
}

