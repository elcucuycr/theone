#define MAX_BUILTIN_FUNC_NUM (128)
#define MAX_BUILTIN_NAME_LENGTH (128)
#define MAX_BUILTIN_OPT_LENGTH (64)

#define MAX_LONGOPT_NAME_LENGTH (128)
#define MAX_BUILTIN_DESC_LENGTH (1024)

typedef struct CmdFlags {
    char shortOpt; // 短命令, '\0' 表示无
    char longOpt[MAX_LONGOPT_NAME_LENGTH]; // 长命令, 空字符串表示无
    char desc[MAX_BUILTIN_DESC_LENGTH]; // 对此设置的描述
    int paramNum; // 0: 不带参数, 正数: 定长参数, 负数: 不定长参数
    char ** var; // 指向存储值的指针
} CmdFlags;

typedef int BUILTIN_FUNC_TYPE(int *, char **, const int, const char **);

typedef struct BuiltinCmd {
    char name[MAX_BUILTIN_NAME_LENGTH]; // 命令名称
    char desc[MAX_BUILTIN_DESC_LENGTH]; // 对此命令的描述
    bool hasAction; // 是否有 action
    int optNum; // 设置的个数
    CmdFlags opt[MAX_BUILTIN_OPT_LENGTH]; // 设置数组
    BUILTIN_FUNC_TYPE * func; // 回调函数
} BuiltinCmd;

void analysis_order(BuiltinCmd * ,int );
