#ifndef INTERFACE_H
#define INTERFACE_H

//const char* option[] = { "main","user","amd" };

void main_interface();
void user_interface();
void cmd_interface();

void pmain();
void puser();
void pcmd();
const char* opt();

#define test_interface divice

#define make_interface(t,ype)\
void t##ype##_interface(){\
    printf("%s\n",divice);\
    int i=0;\
    cin>>i;\
if(i==1)\
{\
    main_interface();\
}\
else if (i == 2)\
{\
    user_interface();\
}\
else {\
    cmd_interface();\
}\
}

#endif
