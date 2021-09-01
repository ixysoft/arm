#include "../bmp.h"

int main(){
    bitmap_file_t* bmp = bmp_load("640x480.bmp");
    bmp_info_show(bmp);

    color_t color;
    uint32_t c = bmp_get_pixel(bmp,0,0);
    memcpy(&color,&c,sizeof(color_t));
    printf("red = %d, green = %d, blue = %d, alpha = %d\n", color.red, color.green, color.blue, color.alpha);
    bmp_free(bmp);
    return 0;
}