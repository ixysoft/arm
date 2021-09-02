#include<dirent.h>
#include<stdio.h>

int main(){
    DIR *dir = opendir(".");
    struct dirent* entry;
    while(entry = readdir(dir)){
        printf("%s%s\n", entry->d_name, entry->d_type == DT_DIR ? "/" : "");
    }
    closedir(dir);
    return 0;
}