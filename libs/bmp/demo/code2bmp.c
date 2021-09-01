#include "../bmp.h"
#include<string.h>
#include<math.h>

int main(int argc, char** argv){
    if(argc == 1){
        printf("代码转bmp文件");
        printf("%s 文件名\n", argv[0]);
    }else{
        FILE* fp = fopen(argv[1], "rb");
        if(fp == NULL){
            perror("文件打开失败");
            return -1;
        }
        char buf[BUFSIZ*32];
        fread(buf, BUFSIZ, 32, fp);
        int length = (strlen(buf) + 1);
        int image_size = ((length / 3) + (length % 3 > 0)) * 3; //图片大小
        image_size /= 3;
        int width = (int)sqrt(image_size);
        width = (width / 4 + (width % 4 > 0)) * 4;
        int height = (image_size / width + (image_size % width > 0));
        printf("width = %d, height = %d, size = %d\n", width, height, image_size);
        bitmap_file_t* bmp = bmp_create(width, height,24);
        int i;
        color_t color;
        memset(bmp->raw_data, 0x00, width * height * 3);
        for(i = 0; i < length; i += 3){
            color.blue = i < length ? buf[i] : 0;
            color.green = i+1 < length ? buf[i+1] : 0;
            color.red = i+2 < length ? buf[i+2] : 0;
            int x = (i / 3) % width;
            int y = i / 3 / width;
            bmp_set_pixel(bmp, x, height - 1 - y, &color);
        }
        fclose(fp);

        char filename[256];
        sprintf(filename, "%s.bmp", argv[1]);
        bmp_save(bmp, filename);
    }
    return 0;
}