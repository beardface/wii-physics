#include <stdio.h>

#ifndef __WIN32__
#include <unistd.h>
#else
#include <direct.h>
#endif

#include <string.h>
#include <fcntl.h>

#include "png.h"

#include "screenshot.h"

bool TakeScreenshot(int width, int height, char* fname)
{
    FILE *fp;
    png_structp png_ptr;
    png_infop info_ptr;
    png_color_8 sig_bit;
    int imgwidth;
    int imgheight;

    if((fp=fopen(fname, "wb"))==NULL){
        return false;
    }

    png_ptr=png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr){
        fclose(fp);
        unlink(fname);
        return false;
    }
    info_ptr=png_create_info_struct(png_ptr);
    if(!info_ptr){
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        fclose(fp);
        unlink(fname);
        return false;
    }

    if(setjmp(png_jmpbuf(png_ptr))){
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        unlink(fname);
        return false;
    }

    imgwidth=width;
    imgheight=height;

    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr, imgwidth, imgheight, 8, PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    /* 5 bits per color */
    sig_bit.red=5;
    sig_bit.green=5;
    sig_bit.blue=5;
    png_set_sBIT(png_ptr, info_ptr, &sig_bit);
    png_set_shift(png_ptr, &sig_bit);

    png_write_info(png_ptr, info_ptr);

    png_set_packing(png_ptr);

    png_byte *row_pointer=new png_byte [png_get_rowbytes(png_ptr, info_ptr)];
/*    uint16 *screen=GFX.Screen;
    for(int y=0; y<height; y++, screen+=GFX.RealPPL){
        png_byte *rowpix = row_pointer;
        for(int x=0; x<width; x++){
            uint32 r, g, b;
            DECOMPOSE_PIXEL(screen[x], r, g, b);
            *(rowpix++) = r;
            *(rowpix++) = g;
            *(rowpix++) = b;
            if(imgwidth!=width){
                *(rowpix++) = r;
                *(rowpix++) = g;
                *(rowpix++) = b;
            }
        }
        png_write_row(png_ptr, row_pointer);
        if(imgheight!=height)
            png_write_row(png_ptr, row_pointer);
    }

    delete [] row_pointer;
*/
    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    fclose(fp);

    return true;
}

