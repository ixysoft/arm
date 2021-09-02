#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<linux/fb.h>
#include<sys/ioctl.h>
#include<strings.h>

int main(){
    int fd;


    // 打开FB
    fd = open("/dev/fb0", O_RDWR);
    if(-1 == fd){
        perror("open freambuffer");
        return -1;
    }

    struct fb_fix_screeninfo fix_info;

    if(ioctl(fd, FBIOGET_FSCREENINFO, &fix_info) == -1){
        perror("get screen info");
        close(fd);
        return -2;
    }

    //打印fix信息(固定信息)
    printf("id = %s\n", fix_info.id);   //厂商id信息
    printf("line length = %d\n", fix_info.line_length); //这里获取一行像素所需要的空间,该空间出厂时固定

    //可变信息
    struct fb_var_screeninfo var_info;

    bzero(&var_info, sizeof(var_info));

    if(ioctl(fd, FBIOGET_VSCREENINFO, &var_info) == -1){
        perror("get var screen\n");
        close(fd);
        return -3;
    }
    printf("xres = %d, yres = %d\n", var_info.xres, var_info.yres);
    printf("bits_per_pixel = %d\n", var_info.bits_per_pixel);
    printf("red: offset = %d, length = %d\n", var_info.red.offset, var_info.red.length);
    printf("green: offset = %d, length = %d\n", var_info.green.offset, var_info.green.length);
    printf("blue: offset = %d, length = %d\n", var_info.blue.offset, var_info.blue.length);
    printf("alpha: offset = %d, length = %d\n", var_info.transp.offset, var_info.transp.length);

    close(fd);
    return 0;
}
