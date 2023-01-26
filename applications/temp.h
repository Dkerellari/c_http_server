
#define MAXF 100


char *hello(){
    return "C_HTTP_SERVER PROJECT";
};
char *text(){
    return "Buliding for fun!<br>Lets Biuld this together!";
};
char *author(){
    return "Author : Desmiraldo Kerellari";
};

struct functions fnc[MAXF];

int getready(){
    fnc[0].func = hello;
    strcpy(fnc[0].varname,"var");
    fnc[1].func = text;
    strcpy(fnc[1].varname,"text");
    fnc[3].func = author;
    strcpy(fnc[3].varname,"author");
}


