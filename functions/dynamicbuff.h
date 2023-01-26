
struct functions{
    char *(*func)();
    char varname[100];
};


char *getdynamic(char *buff , struct functions *fnc,int maxvars){
    int i=0,j=0,k=0,m=0,len,length=0;
    len = strlen(buff);
    static char rbuff[10000];
    char varname[100];
    char varvalue[255];
    while(i < len){
        if(buff[i]=='{' && buff[i+1]=='{'){
            k=0;
            i=i+2;
            while(buff[i]!='}'){
                varname[k]=buff[i];
                k++;
                i++;
            }
            i=i+1;
            varname[k] = '\0';
            k=0;
            while(k <= maxvars){
                if(strcmp(fnc[k].varname,varname)==0){
                    strcpy(varvalue,fnc[k].func());
                    length = strlen(varvalue);
                    m=0;
                    while(m < length){
                        rbuff[j]=varvalue[m];
                        m++;
                        j++;
                    }
                    
                    j--;
                    
                }
                k++;
            }
            
        }else{
            rbuff[j]=buff[i];
        }
        i++;
        j++;
    }
    rbuff[j]='\0';
    return rbuff;

}