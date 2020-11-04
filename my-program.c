#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
FILE* file;
char strLine[1024];
char symbolStack[1024];
int top=1,symbol=1,input=0;
int priority_f(char c){
    if(c=='+') return 2;
    if(c=='*') return 4;
    if(c=='(') return 0;
    if(c==')') return 6;
    if(c=='i') return 6;
    if(c=='#') return 0;
    return -1;
}

int priority_g(char c){
    if(c=='+') return 1;
    if(c=='*') return 3;
    if(c=='(') return 5;
    if(c==')') return 0;
    if(c=='i') return 5;
    if(c=='#') return 0;
    return -1;
}

int priorityCheck(char a,char b){
    int temp1=priority_f(a);
    int temp2=priority_g(b);
    if((a=='i' && b=='i')||
    (a=='i' && b=='(')||
    (a==')' && b=='i')||
    (a==')' && b=='(')||
    (a=='(' && b=='#')||
    (a=='#' && b==')')||
    (a=='#' && b=='#')||
    (temp1==-1 || temp2==-1)) return -1;
    else if(temp1<=temp2) return 0;
    else return 1;
}

void error_E(){
    printf("E\n");
}

void error_RE(){
    printf("RE\n");
}

void success(){
    printf("R\n");
}

int merge(){
    if(symbolStack[symbol]=='+' || symbolStack[symbol]=='*'){
        if(top==symbol+1 && symbolStack[symbol+1]=='N' && symbolStack[symbol-1]=='N'){
            symbol-=2;
            top-=2;
            return 1;
        }
        else{
            return 0;
        }
    }
    if(symbolStack[symbol]==')'){
        if(top==symbol && symbolStack[symbol-1]=='N' && symbolStack[symbol-2]=='('){
            symbol-=2;
            symbolStack[symbol]='N';
            top=symbol;
            symbol--;
            return 1;
        }
        else{
            return 0;
        }
    }
    if(symbolStack[symbol]=='i'){
        if(top==symbol){
            symbolStack[symbol]='N';
            symbol--;
            return 1;
        }
        else{
            return 0;
        }
    }
}

int analyse(){
    symbolStack[1]='#';
    while(1){
        int judge = priorityCheck(symbolStack[symbol],strLine[input]);
        if(judge==0){
            printf("I%c\n",strLine[input]);
            symbolStack[++top]=strLine[input++];
            symbol=top;
        }
        else if(judge==1){
            if(merge(symbol,top)==1){
                success();
            }
            else{
                error_RE();
                break;
            }
        }
        else{
            if(symbolStack[top]!='N' || top!=2 || strLine[input]!='#')
                error_E();
            break;
        }
    }
}

int main(int argc,char** argv){
    file = fopen(argv[1],"rt");
    //file = fopen("test.txt","rt");
    fgets(strLine,1024,file);
    for(int i=0;i<1024;i++){
        if(strLine[i]=='\r'){
            strLine[i]='#';
            break;
        }
    }
    symbolStack[1]='#';
    analyse();
    return 0;
} 