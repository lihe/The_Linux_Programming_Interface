#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

struct copyConfigStruct{
    int inputFd;
    int outputFd;
    char *inputPath;
    char *outputPath;
}copyConfig;

int main(int argc, char *argv[]){
    if (argc < 3){
        printf("\n");
        _exit(0);
    }

    copyConfig.inputPath = argv[1];
    copyConfig.outputPath  = argv[2];
    copyConfig.inputFd = open(copyConfig.inputPath, O_RDONLY);
    if (copyConfig.inputFd == -1){
        printf("输入文件打开失败\n");
        _exit(0);
    }
    copyConfig.outputFd = open(copyConfig.outputPath, O_RDWR|O_TRUNC|O_CREAT, 0777);
    if (copyConfig.outputFd == -1){
        printf("输出文件打开失败\n");
        _exit(0);
    }
    char buff;
    while (read(copyConfig.inputFd, &buff, 1) > 0){
        if (buff == 0){
            if (lseek(copyConfig.outputFd, 1, SEEK_CUR) == -1){
                printf("跳过空洞失败\n");
                _exit(0);
            }
        }
        else if (write(copyConfig.outputFd, &buff, 1) == -1) {
            printf("写入文件失败\n");
            _exit(0);
        }
    }

    close(copyConfig.inputFd);
    close(copyConfig.outputFd);
}