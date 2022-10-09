// infix to postfix converter


#include <iostream>
#include <string.h>

using namespace std ;

int i =0, j[20] , p = 0, q=0 ,z=0, stind=-1,outind=0;
char a[20] , postfix[20],stack[20];
int main() {
    printf("enter the expression that u want to postfix\n") ;
    scanf("%s",&a) ;
    while(a[i]!='\0') {
        if(((a[i]>='a')&&(a[i]<='z'))||((a[i]>='A')&&(a[i]<='Z'))) {
            postfix[outind] = a[i] ;
            outind++ ;
        }
        else if((a[i]=='+')||(a[i]=='-')||(a[i]=='*')||(a[i]=='/')||(a[i]=='(')||(a[i]==')')) {
            if(stind==-1) {
                stind++ ;
                stack[stind] = a[i] ;
            }
            else {
                if(a[i]=='(') {
                    stind++ ;
                    stack[stind] = a[i] ;
                    j[p] = stind ;
                    p++ ;
                }
                else if(a[i]==')') {
                    if(p!=0) {
                    for(q=stind;q>=(j[p-1]+1);q--) {
                        postfix[outind] = stack[q] ;
                        outind++ ;
                        stind-- ;
                    }
                    }
                    else {
                        for(q=stind;q>=(j[p]+1);q--) {
                        postfix[outind] = stack[q] ;
                        outind++ ;
                        stind-- ;
                    }
                    }
                    stind-- ;
                    if(p!=1) {
                        p=p-2;
                    }
                    
                } 
                else{
                    if(a[i]=='+') {
                        for(q=stind;q>=j[p-1]+1;q--) {
                            if((stack[q]=='*')||(stack[q]=='/')) {
                                postfix[outind] = stack[q] ;
                                outind++ ;
                                stind-- ;
                            }
                            else{
                                stind++ ;
                                stack[stind] = a[i] ;
                                break ;
                            }
                        }
                        stind++ ;
                        stack[stind] = a[i] ;
                    }
                    else if(a[i]=='-') {
                        for(q=stind;q>=j[p-1]+1;q--) {
                            if((stack[q]=='*')||(stack[q]=='/')||(stack[q]=='+')) {
                                postfix[outind] = stack[q] ;
                                outind++ ;
                                stind-- ;
                            }
                            else{
                                stind++ ;
                                stack[stind] = a[i] ;
                                break ;
                            }
                        }
                        stind++ ;
                        stack[stind] = a[i] ;
                    }
                    else {
                        stind++ ;
                        stack[stind] = a[i] ;
                    }
                }       
            }
        }
        printf("%s    %c    %s      ",a,a[i],postfix) ;
        for(z=0;z<=stind;z++) {
            printf("%c",stack[stind]) ;
        }
        printf("\n") ;
        i++ ;
    }
      if((stind==0)&&(stack[stind]!='(')) {
            postfix[outind] = stack[0] ;
            outind++ ;
            stind-- ;
           printf("%s    %c    %s      ",a,a[i],postfix) ;
        for(z=0;z<=stind;z++) {
            printf("%c",stack[stind]) ;
        }
        }
        else {
            for(i=stind;i>=0;i--) {
                postfix[outind] = stack[i] ;
                outind++ ;
                stind-- ;
            } 
            printf("%s    %c    %s      ",a,a[i],postfix) ;
        for(z=0;z<=stind;z++) {
            printf("%c",stack[stind]) ;
        }
        }
}        
