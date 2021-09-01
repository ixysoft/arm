#include "../bmp.h"
#include<string.h>
#include<math.h>

int main(int argc, char** argv){
    if(argc == 1){
        printf("%s 文件名\n", argv[0]);
    }else{
        FILE* fp = fopen(argv[1], "rb");
        if(fp == NULL){
            perror("文件打开失败");
            return -1;
        }
        char buf[BUFSIZ];
        fread(buf, BUFSIZ, 1, fp);
        int length = (strlen(buf) + 1);
        int image_size = ((length / 3) + (length % 3 > 0)) * 3; //图片大小
        int width = (int)sqrt(image_size);
        int height = (image_size / width + (image_size % width > 0)) * width;
        bitmap_file_t* bmp = bmp_create(width, height,24);
        int i;
        color_t color;
        for(i = 0; i < length; i += 3){
            color.red = i < length ? buf[i] : 0;
            color.green = i+1 < length ? buf[i+1] : 0;
            color.blue = i+2 < length ? buf[i+2] : 0;
            int x = (i / 3) % width;
            int y = i / 3 / width;
            bmp_set_pixel(bmp, x, y, &color);
        }
        fclose(fp);

        bmp_save(bmp, "code.bmp");
    }
    return 0;
}