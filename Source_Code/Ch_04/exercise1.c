#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

struct teeConfigStruct{
    int a;
    char *outputPath;
    int outputFd;
} teeConfig;

void getArgs(int argc, char *argv[]){
    int opt;
    if ((opt = getopt(argc, argv, "a")) != -1){
        teeConfig.a = 0;
        switch (opt){
        case 'a':
            printf("追加模式\n");
            teeConfig.a = 1;
            break;
        
        default:
            printf("参数错误\n");
            _exit(0);
            break;
        }
    }

    if (argc - optind < 1){
        printf("参数太少\n");
        _exit(0);
    }

    teeConfig.outputPath = argv[optind];
    printf("路径输出 %s\n", teeConfig.outputPath);
}

int main(int argc, char *argv[]){
    getArgs(argc, argv);
    int outputFileFlag;
    if (teeConfig.a == 1){
        outputFileFlag = O_RDWR | O_CREAT | O_APPEND;
    }
    else{
        outputFileFlag = O_RDWR | O_CREAT | O_TRUNC;
    }
    teeConfig.outputFd = open(teeConfig.outputPath, outputFileFlag, 0777);
    if (teeConfig.outputFd == -1){
        printf("无法打开输出文件\n");
        _exit(0);
    }

    char buff;

    while (read(STDERR_FILENO, &buff, 1) > 0){
        printf("%c", buff);
        if (write(teeConfig.outputFd, &buff, 1) == -1){
            printf("无法写入\n");
            _exit(0);
        }
    }

    if (close(teeConfig.outputFd) == -1){
        printf("无法关闭文件\n");
    }
}