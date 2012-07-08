#ifndef MY_IOE
#define MY_IOE

#include <cstdarg>
#define EXIT 1

void err(int ifExit,const char *msg, ...)
{
    if(msg==NULL)
	printf("error\n");
    else {
	printf("error: ");
	va_list args;
	va_start (args, msg);
	char buffer[256];
	vsprintf (buffer, msg, args);
	printf("%s\n",buffer);
	va_end (args);
    }
    if(ifExit==EXIT) exit(0);
}

inline char mygetchar()
{
    while(1){
	char t=getchar();
	if(t!=' '&&t!='\n')return t;
    }
}

#endif
