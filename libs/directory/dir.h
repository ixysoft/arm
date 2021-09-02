#ifndef EC6D668B_CDDC_498C_B089_29CCBCB95433
#define EC6D668B_CDDC_498C_B089_29CCBCB95433
#include<dirent.h>
#include<stdio.h>

typedef struct dirnode_t dirnode_t;

struct dirnode_t{
    dirent* entry;
    dirnode_t* next;
    dirnode_t* prev;
};

typedef struct dir_t dir_t{
    dirent* head;
    dirent* tail;
    int size;
};

typedef enum{
    SORT_BY_ASC = 0x01, //正序
    SORT_BY_DESC = 0x02,//逆序
    SORT_BY_CTIME = 0x04,//按照创建时间
    SORT_BY_MTIME = 0x08,//按照修改时间
    SORT_BY_NAME = 0x10,//按照名称
    SORT_BY_SIZE = 0x20,//按照大小
    SORT_BY_TYPE = 0x40,//按照类型
}dir_sort_t;    //排序方法

// 获取dir
dir_t* dir_get(const char* dir);
// 排序dir
int dir_sort(dir_t* dir, dir_sort_t type);
// 遍历dir
dirent* dir_get_next(const char* dir);
// 释放dir
int dir_close(dir_t* dir);
#endif /* EC6D668B_CDDC_498C_B089_29CCBCB95433 */
