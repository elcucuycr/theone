#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdbool.h>
#include"analysis_order.h"


int search(char *name,char *compare,BuiltinCmd * blt1,int bltNum1) {//在cmdParser函数中起到寻找和比对库中命令的功能
    int i;
    for(i = 0; i < bltNum1; i++)
    {
        if(strcmp(name,blt1[i].name) == 0)
        {
            int j;
            for(j=0;j<blt1[i].optNum;j++)
            {
                if(strcmp((blt1[i].opt)[j].longOpt,compare)==0)
                {
                    printf("-%c --%s",(blt1[i].opt)[j].shortOpt,(blt1[i].opt)[j].longOpt);
                    if((blt1[i].opt)[j].paramNum==0)
                    return 0;
                }
                else if((blt1[i].opt)[j].shortOpt==*compare)
                {
                    printf("-%c --%s",(blt1[i].opt)[j].shortOpt,(blt1[i].opt)[j].longOpt);
                    if((blt1[i].opt)[j].paramNum==0)
                    return 0;
                }
            }
        }
    }
    return 1;
}

int cmdParser(int argc,char * argv[],BuiltinCmd * blt1,int bltNum1) {//完成解析功能的函数
    int para[20];
    int paranum=0;
    if(argc == 0) return 0;
        int i;
        printf("commond:\n");
        for(i=1;i<argc;i++)
        {
            if(argv[i][0]=='-')
            {
                if(argv[i][1]=='-')
                {
                    if(search(argv[0],argv[i]+2,blt1,bltNum1))
                    {
                        
                        printf("  %s",argv[i+1]);
                        i++;
                    }
                    printf("\n");
                }
                else
                {
                    if(search(argv[0],argv[i]+1,blt1,bltNum1))
                    {
                        printf("  %s",argv[i+1]);
                        i++;
                    }
                    printf("\n");
                }
            }
            else
            {
                para[paranum]=i;
                paranum++;
            }
        }
        int k;
        printf("parameter:\n");
        for(k=0;k<paranum;k++)
        {
            printf(" [%d] %s\n",k,argv[para[k]]);
        }
    return 0;
}



void analysis_order(BuiltinCmd * p,int num){
	char str[100];
    memset(str, 0, sizeof(str));
	while(EOF != scanf("%[^\n]", &str)) {
		int argc = 0;
	    char * argv[100] = {0};
		getchar();
		// 分割输入的字符串，去除注释和开头结尾多余的空字符, 生成 cmdParser 的输入
		char * posA = (char *) str;
		while(*posA && *posA == ' ') posA++;

		char * posB = posA;
		while(*posB) {
			if(*posB == '#') {
				*posB = 0; // '#' means comment
				break;
			} else if(*posB == '\t') {
				*posB = ' '; // convert '\t' to ' '
			}
			posB ++;
		}
		while(*(posB - 1) && *(posB - 1) == ' ') *(--posB) = 0;
		if(*posA) {
			posB = posA++;
			while(*posA) {
				if(*posA == ' ') {
					argv[argc] = (char *)malloc(posA - posB + 1);
					strncpy(argv[argc], posB, posA - posB);
					argv[argc][posA - posB] = 0;
					argc ++;
					posB = posA + 1;
				}
            posA ++;
        }
        if(posA > posB) {
            argv[argc] = (char *)malloc(posA - posB + 1);
            strncpy(argv[argc], posB, posA - posB);
            argv[argc][posA - posB] = 0;
            argc ++;
        }
    }
	cmdParser(argc, (char **) argv,p,num);
	while(argc--) if(argv[argc]) free(argv[argc]);
	printf("解析结束\n\n");  
    } 
}
