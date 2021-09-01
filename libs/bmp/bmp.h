#ifndef BD40F492_E7DE_4CF3_B368_D05CE967D6CD
#define BD40F492_E7DE_4CF3_B368_D05CE967D6CD
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

//byte per pixel
#define BPP(bmp) ((bmp)->bpp * 4 / 32)
#define bmp_row_size(bmp) ((((bmp)->width * BPP(bmp) / 4) + ((bmp)->width * BPP(bmp) % 4 > 0)) * 4)
#define bmp_pixel(bmp,x,y) ((bmp)->raw_data + (bmp->height > 0 ? (bmp->height - 1 - (y)) : (y)) * bmp_row_size(bmp) + (x) * BPP(bmp))

typedef struct bitmap_file_t bitmap_file_t;
typedef struct color_t color_t;

#pragma pack(1)
struct bitmap_file_t{
    //bitmap file header
    char magic[2];  //BM
    int32_t size;  //文件大小
    uint16_t res1;  //预留1
    uint16_t res2;  //预留2
    uint32_t start; //图片信息起始位置
    //bitmap information header
    int32_t dib_header_size;   //DIB_header的大小,一般为40byte(0x28)
    int32_t width; //宽度
    int32_t height;//高度,整数表示图片上线颠倒,负数表示图片正向
    int16_t color_plane;   //色彩平面数量,必须为1
    int16_t bpp;   //bit per pixel
    int32_t compress_type; //压缩方式,通常不压缩,及BI_RGB,对应0
    int32_t image_size;    //图像的大小,字节为单位
    int32_t hratio;  //横向分辨率
    int32_t vratio;  //纵向分辨率
    int32_t pallet_colors; //调色板中的颜色数,通常为0
    int32_t important_colors;  //重要颜色数,通常为0,表示都很重要
    void* raw_data;         //bmp数据
};
#pragma pack()

struct color_t{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
};

// 暂时只支持不带压缩的图片,只支持24,32为的bmp
//载入bmp图像
bitmap_file_t* bmp_load(const char* filename);
//显示bmp图片信息
void bmp_info_show(bitmap_file_t* bmp);
//获取指定位置的颜色
uint32_t bmp_get_pixel(bitmap_file_t* bmp, int x, int y);
//设定指定位置的颜色
uint32_t bmp_set_pixel(bitmap_file_t* bmp, int x, int y, void* color);
//将bitmap_file_t保存为一个bmp文件
int bmp_save(bitmap_file_t* bmp, const char* filename);
//初始化一个指定大小的图片
bitmap_file_t* bmp_create(int width, int height, int bpp);
//释放位图
void bmp_free(bitmap_file_t* bmp);
#endif /* BD40F492_E7DE_4CF3_B368_D05CE967D6CD */
