#define PORT "PORT"
#define ROOT "ROOT_FILE"

struct config{
    int port;
    char root[100];
};

struct glp{
    char key[100];
    char value[100];
    int pointer;
};


struct glp findparam(char *line){
    struct glp ones;
    int i=0;
    while(line[i] != ' ' && line[i]!='\0' && (line[i]>=32 && line[i]<=126) ){
        ones.key[i] = line[i];
        i++;
    }
    ones.key[i]='\0';
    while(line[i] == ' ' && line[i]!='\0'){
        i++;
    }
    int j=0;
    while(line[i] != ' ' && line[i]!='\0' && (line[i]>=32 && line[i]<=126)){
        ones.value[j] = line[i];
        i++;
        j++;
    }
    ones.value[j]='\0';
    ones.pointer = 0;
    return ones;
}

struct glp getlinee(char *buff,int start){
    struct glp data , ones;

    static char line[100];
    int i=0,len;
    len=strlen(buff);
    while(buff[start] != '\n' && buff[start]!= '\0' && (start<=len)){
        line[i] = buff[start];
        start++;
        i++;
    }
    
    line[i]='\0';
    ones = findparam(line);

    strcpy(data.key,ones.key);

    strcpy(data.value,ones.value);

    if(start >= len){
        data.pointer=-1;
    }else{
        data.pointer = start;
    }
    return data;
}


struct config cfg(char *root){
    FILE *fp;
    char *buff;
    int bytes,pointer=0;
    struct glp data1;
    struct config cfg;
    data1.pointer=0;
    fp = fopen(root,"r");

    fseek(fp, 0, SEEK_END);
    bytes = ftell(fp);

    fseek(fp, 0, SEEK_SET);
    buff = (char *)calloc(bytes,1);

    fread(buff,1,bytes,fp);
    fclose(fp);
    while(data1.pointer != -1){
        data1 = getlinee(buff,pointer);
        pointer = data1.pointer+1;
        if(strcmp(data1.key,"PORT") == 0){
            cfg.port=atoi(data1.value);
        }else if(strcmp(data1.key,"ROOTFILE") == 0){
            strcpy(cfg.root,data1.value);
        }
    }
    
    return cfg;
}