#include "../bmp.h"

int main(){
    //创建一张指定大小的图片
    bitmap_file_t* bmp = bmp_create(640,480,24);
    for(int row = 0; row < 480; row++){
        for(int col = 0; col < 640; col++){
            uint32_t color = 0x0000FF00;
            bmp_set_pixel(bmp, col, row, &color);
        }
    }
    //保存bmp
    bmp_save(bmp,"640x480.bmp");

    return 0;
}