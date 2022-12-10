
#define MAXF 100


char *hello(){
    return "hello from function in c";
};

struct functions fnc[MAXF];

int getready(){
    fnc[0].func = hello;
    strcpy(fnc[0].varname,"var");
}


