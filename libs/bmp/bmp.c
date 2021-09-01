#include "bmp.h"

//载入bmp图像
bitmap_file_t* bmp_load(const char* filename){
    if(filename == NULL) return NULL;
    bitmap_file_t* bmp = (bitmap_file_t*)malloc(sizeof(bitmap_file_t));
    FILE* bmp_file = fopen(filename, "rb");
    if(bmp_file == NULL){
        perror("文件打开失败");
        return NULL;
    }
    fread(bmp, sizeof(bitmap_file_t) - sizeof(void*), 1, bmp_file);
    bmp->raw_data = malloc(bmp->size - bmp->start);
    fread(bmp->raw_data, bmp->size - bmp->start, 1, bmp_file);
    fclose(bmp_file);

    return bmp;
}

//显示bmp图片信息
void bmp_info_show(bitmap_file_t* bmp){
    if(bmp == NULL){
        printf("不合法的图片\n");
        return;
    }
    printf("BMP文件信息\n");
    printf("Magic:\t\t%c%c\n",bmp->magic[0],bmp->magic[1]);
    printf("文件大小:\t%d\n", bmp->size);
    printf("数据开始位置:\t%d\n", bmp->start);

    //bitmap information header
    printf("\n位图信息\n");
    printf("DIB header大小:\t%d(0x%02x)\n", bmp->dib_header_size, bmp->dib_header_size);
    printf("宽度:\t\t%d\n", bmp->width);
    printf("高度:\t\t%d\n", bmp->height);
    printf("色彩平面数量:\t%d\n", bmp->color_plane);
    printf("像素深度:\t%d\n", bmp->bpp);
    printf("压缩方式:\t%d\n", bmp->compress_type);
    printf("图片大小:\t%d\n", bmp->image_size);
    printf("横向分辨率:\t%d\n", bmp->hratio);
    printf("纵向分辨率:\t%d\n", bmp->vratio);
    printf("调色板颜色数:\t%d\n", bmp->pallet_colors);
    printf("重要颜色数:\t%d\n", bmp->important_colors);
}

//获取指定位置的颜色
uint32_t bmp_get_pixel(bitmap_file_t* bmp, int x, int y){
    if(bmp == NULL || x >= bmp->width || x < 0 || y >= bmp->height || y < 0) return 0;
    uint8_t* pixel = bmp_pixel(bmp,x,y);

    uint32_t color = 0;
    for(int i = 0; i < BPP(bmp); i++){
        color |= ((uint32_t)pixel[i]) << (i<<3);
    }

    return color;
}

//设定指定位置的颜色
uint32_t bmp_set_pixel(bitmap_file_t* bmp, int x, int y, void* color){
    if(bmp == NULL || x >= bmp->width || x < 0 || y >= bmp->height || y < 0) return 1;   //失败
    color_t* col = color;   //将color转为color_t类型
    uint8_t* pixel = bmp_pixel(bmp,x,y);

    pixel[0] = col->blue;
    pixel++;
    pixel[0] = col->green;
    pixel++;
    pixel[0] = col->red;
    if(BPP(bmp) == 4){
        pixel++;
        pixel[0] = col->alpha;
    }

    return 0;
}

//将bitmap_file_t保存为一个bmp文件
int bmp_save(bitmap_file_t* bmp, const char* filename){
    if(bmp == NULL || filename == NULL) return 1;
    FILE* bmp_file = fopen(filename, "wb");
    fwrite(bmp, bmp->start, 1, bmp_file);   //写入基础信息
    fwrite(bmp->raw_data, bmp->size - bmp->start, 1, bmp_file); //写入图形信息
    fclose(bmp_file);
    return 0;
}


//初始化一个指定大小,指定位深的图片
bitmap_file_t* bmp_create(int width, int height, int bpp){
    bitmap_file_t* bmp = (bitmap_file_t*)malloc(sizeof(bitmap_file_t));
    bmp->magic[0] = 'B';
    bmp->magic[1] = 'M';
    bmp->size = width * bpp / 8;
    bmp->size = (bmp->size / 4 + (bmp->size % 4 > 0)) * 4 * height + 54;
    bmp->start = sizeof(bitmap_file_t) - sizeof(void*);
    bmp->dib_header_size = 0x28;
    bmp->width = width;
    bmp->height = height;
    bmp->color_plane = 1;
    bmp->bpp = bpp;
    bmp->image_size = bmp->size - bmp->start;
    bmp->compress_type = 0;
    bmp->hratio = 0;
    bmp->vratio = 0;
    bmp->pallet_colors = 0;
    bmp->important_colors = 0;
    bmp->raw_data = malloc(bmp->size - bmp->start);
    memset(bmp->raw_data, 0xFF, bmp->size - bmp->start);

    return bmp;
}

void bmp_free(bitmap_file_t* bmp){
    if(bmp == NULL) return;
    if(bmp->raw_data != NULL)
        free(bmp->raw_data);
    bmp->raw_data = NULL;
    free(bmp);
}