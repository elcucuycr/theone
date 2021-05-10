#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdbool.h>
#include"analysis_order.h"


BuiltinCmd blt[10];//新建存放10个指令的数组
int bltNum;

int addBuiltinCmd(const BuiltinCmd * cmd) {
    memcpy(blt + bltNum, cmd, sizeof(BuiltinCmd));
    bltNum ++;
    return 0;
}

int findCmdShortOpt(const BuiltinCmd * cmd, const char shortOpt) {
    int i;
    for(i = 0; i < cmd->optNum; i++)
        if(shortOpt == cmd->opt[i].shortOpt) return i;
    return -1;
}

int addCmdFlag(BuiltinCmd * cmd, const char shortOpt, const char * longOpt, const char * desc, const int paramNum) {
    if(findCmdShortOpt(cmd, shortOpt) >= 0)
        return 1;

    CmdFlags * flag = cmd->opt + cmd->optNum;
    flag->shortOpt = shortOpt;
    strcpy(flag->longOpt, longOpt);
    strcpy(flag->desc, desc);
    flag->paramNum = paramNum;
    flag->var = NULL;

    cmd->optNum ++;
    return 0;
}

void main(){
    memset(blt, 0, sizeof(blt));
    /* 在自己的库里面添加几个指令，用来给后面命令行解析功能做测试 */
	//rm指令
    BuiltinCmd x1;
    strcpy(x1.name, "rm");
    strcpy(x1.desc, "This command is for remove.");
    x1.hasAction = false;
    x1.optNum = 0;
    memset(x1.opt, 0, sizeof(x1.opt));
    addCmdFlag(&x1, 'x', "exclude", "jump files", 1);
    addCmdFlag(&x1, 'd', "dir", "auto delete", 0);
    addCmdFlag(&x1, 'f', "force", "force to delete the file", 0);
    addCmdFlag(&x1, 'i', "interactive", "comfile before delete", 0);
    addCmdFlag(&x1, 'q', "quiet", "do not print the file that was delete", 0);
    addCmdFlag(&x1, 'r', "recursive", "Recursively deletes all files and folders in a directory", 0);
    addBuiltinCmd(&x1);
	//tree指令
    BuiltinCmd y;
    strcpy(y.name, "tree");
    strcpy(y.desc, "This command is for seting file tree.");
    y.hasAction = false;
    y.optNum = 0;
    memset(y.opt, 0, sizeof(y.opt));
    addCmdFlag(&y, 'L', "level", "set tree level", 1);
    addCmdFlag(&y, 'h', "human-readable", "amount or size of readable file", 1);
    addBuiltinCmd(&y);
	//ls指令
    BuiltinCmd x;
    strcpy(x.name, "ls");
    strcpy(x.desc, "This command is for xxx.");
    x.hasAction = false;
    x.optNum = 0;
    memset(x.opt, 0, sizeof(x.opt));
    addCmdFlag(&x, 'a', "all", "show hidden files", 0);
    addCmdFlag(&x, 'l', "list", "print in a list", 0);
    addCmdFlag(&x, 'h', "human-readable", "Prints the file size in a readable format", 0);
    addCmdFlag(&x, 'd', "directory", "Print only the directory, ignoring the normal files", 0);
    addCmdFlag(&x, 'r', "reverse", "Descending arrangement", 0);
    addCmdFlag(&x, 's', "sort-by", "Sort by given value",-1);
    addBuiltinCmd(&x);
	//至此库里面有了3条指令
	analysis_order(blt,bltNum);
}
