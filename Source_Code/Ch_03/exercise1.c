*/
    将文件保存为reboot.c，使用gcc reboot.c命令进行编译。然后运行sudo ./a.out，
    此时可以看到系统进行了重启。不使用root权限无法重启。
*/

#include <unistd.h>
#include <sys/reboot.h>

int main(int argc, char *argv[]){
    reboot(RB_AUTOBOOT);
    return 0;
}

