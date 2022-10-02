/**
 * @file
 * @brief Add one line description here. Should contain a Wikipedia
 * link or another source explaining the algorithm/implementation.
 * @details
 * This is a multi-line
 * description containing links, references,
 * math equations, etc.
 * @author [Name](https://github.com/handle)
 * @see related_file.cpp, another_file.cpp
 */

#include <cassert>   /// for assert
#include<stdio.h>    // standard library
#include<string.h>   //for string functions

/**
 * @namespace <folder name>
 * @brief <namespace description>
 */
namespace name {}

/**
 * @brief Class documentation
 */

class class_name {
 private:
    int variable;   ///< short info of this variable
    char *message;  ///< short info

 public:
    // other members should be also documented as below
};

/**
 * @brief Function documentation
 * @tparam T this is a one-line info about T
 * @param param1 on-line info about param1
 * @param param2 on-line info about param2
 * @returns `true` if ...
 * @returns `false` if ...
 */;

int main(int argc, char *argv[]) 
{
    // code here

    int row;
    int i,j,k;
    int temp=(-1);
    char ch[1000];
    int count=0;
    int one=0;
    int zero=0,six=6;
    char b[1000]={'@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!','@','#','&','*','^','%','!'};
     
     int c[1000];
    row=12;
    
    printf("*** Please use online gdb or visual code and if you are going to use long words in your string...  zoom out by ctrl+(mouse scrolll down) coz it just overwrite the word codes for not having the required output area\n\n ENTER STRINGS OR LINE HERE: ");
    scanf("%[^\n]",ch);
    
    int len = strlen(ch);
    printf("\n\n");
    
    len = len+1;
    
    ch[len] =' ';
    
    int flag=1;
    
    c[one]=len;
    
    for(k=0;k<=len;k++)
    {
        if(ch[k]==' ')  
        {
            c[one]=k;
            
            one++;
        }
    }

    
    while(one--)
    {
        printf("\n\n");
         temp++;
        printf("\n---------------------------------------------------------------------------------\n");
    for(i=1;i<=row;i++)
    {
        printf("\n");
        printf("   ");       
        
        
        six=c[temp];
        for(k=zero;k<=six;k++)
    {
        if(ch[k]==' ') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("  ");
        for(j=1;j<=2*row;j++)
        {
            printf(" ");
        }
        /*--------------------------------------------------------------------------------*/}
        
        else if(ch[k]=='a'||ch[k]=='A') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("  ");
        for(j=1;j<=2*row;j++)
        {
                
                if(i==1 && j==row+i) printf("%c",b[count]);
                
                else if(i==row/2+1 || i==row/2+2)
                {
                    if(j<=row+i && j>=row-i+2) printf("%c",b[count]);
                                                     ///////////////or char A
                    else printf(" ");                  
                }
                else if((i!=1) && (j==row+i||j==row+i-1||j==row+i-2|| j==row-i+2|| j==row-i+3|| j==row-i+4)) printf("%c",b[count]);
                                                         
                else printf(" ");
        
               
        }
        
        /*--------------------------------------------------------------------------------*/}
        
        
        if(ch[k]=='b'||ch[k]=='B') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");        for(j=1;j<=3;j++)
        {
             printf("%c",b[count]);
        }   
        
        for(j=1;j<=row/2;j++)
        {
            if(i==1||i==2||i==row||i==row-1||i==row/2||i==row/2+1) printf("%c",b[count]);
            
            else printf(" ");
        }
        
        for(j=1;j<=row-(row/2+3);j++)
        {
            if(i<=(row/2)/2+1)
            {
              if(j<=i) printf("%c",b[count]);
           
              else printf(" ");
            }
            
            else if(i>((row/2)/2+1) && i<=row/2)
            {
              if(j<=row-(row/2+i-1)) printf("%c",b[count]);
           
              else printf(" ");
            }
            
            /////                   //////////////////////for char B
            
            else if(i>row/2 && i<(row/2+(row/2)/2)+1)
            {
              if(j<=i-row/2) printf("%c",b[count]);
           
              else printf(" ");
            }
            
            else if(i>=(row/2+(row/2)/2)+1)
            {
              if(j<=row-(row/2+(i-row/2)-1)) printf("%c",b[count]);
           
              else printf(" ");
            }
            
        }
        
        /*---------------------------------------------------------------------------------*/}
        
        
        if(ch[k]=='c'||ch[k]=='C') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");        for(j=1;j<=row+((row/2)-((row/2)/2));j++)
        {
            if(i>=1&&i<=2 || i<=row&&i>=row-1||j>=1&&j<=3)
            {
                printf("%c",b[count]);                           /////for char C
            }

            else printf(" ");
        }
        
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='d'||ch[k]=='D') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");        for(j=1;j<=row;j++)
        {
            if(i>=1&&i<=2 || i<=row&&i>=row-1 || j>=1&&j<=3) printf("%c",b[count]);
                                    
            else printf(" ");
        }
        for(j=1;j<=row-(row/2+3);j++)
        {
            if(i<=row/2)
            {                               ///////////////////for char D
              if(j<=i) printf("%c",b[count]);
           
              else printf(" ");
            }
            
            else if(i>row/2)
            {
              if(j<=row-(row/2+(i-(row/2))-1)) printf("%c",b[count]);
           
              else printf(" ");
            }
        }
        /*---------------------------------------------------------------------------------*/}
    
        if(ch[k]=='e'||ch[k]=='E') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   "); 

        for(j=1;j<=4;j++)
        {
             printf("%c",b[count]);
        }    
                                                   ////////////////for char E
        for(j=1;j<=row;j++)
        {
            if(i>=1 && i<=2 || i<=row && i>=row-1||i==row/2||i==row/2+1) printf("%c",b[count]);
            
            else printf(" ");
        
        }
    
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='f'||ch[k]=='F') 
        {/*---------------------------------------------------------------------------------*/
        printf("   ");        
        
        for(j=1;j<=4;j++)
        {
             printf("%c",b[count]);
        }    
                                                   ////////////////for char F
        for(j=1;j<=row;j++)
        {
            if(i>=1 && i<=2 ||i==row/2||i==row/2+1) printf("%c",b[count]);
            
            else printf(" ");
        
        }
    
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='g'||ch[k]=='G') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");      
        
        for(j=1;j<=row+(row/2);j++)
        {
            if(i>=1&&i<=2 || (j<=row+(row/2)&&j>=row+(row/2-2)) && i>=5 || i<=row&&i>=row-1 
               || j>=1&&j<=3 || (j>=8&&j<=10) && (i>=5&&i<=8) || (j>8&&(i>=5 && i<=6))) printf("%c",b[count]);

                                                       //////////for char G           
            else printf(" "); 
        }
        
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='h'||ch[k]=='H') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");       
        for(j=1;j<=3;j++)
        {
             printf("%c",b[count]);
        }    
                                                   ////////////////for char h
        for(j=1;j<=row;j++)
        {
            if(i==row/2||i==row/2+1 || j>=row-2&&j<=row) printf("%c",b[count]);
            
            else printf(" ");
        
        }
    
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='i'||ch[k]=='I') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("    ");
        
        for(j=1;j<=3;j++)
        {
            if(i>(row/2-2) || i<4)
            {
                printf("%c%c",b[count],b[count]);                           ///for char I
            }
            
            else printf("  ");
        }
    
        /*---------------------------------------------------------------------------------*/}
     
        if(ch[k]=='j'||ch[k]=='J') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");  
        
        for(j=1;j<=4;j++)
        {
            if(i>7 ) printf("%c",b[count]);
            
            else printf(" ");
        }   
                             ///////////////////////////for char J
        for(j=1;j<=row-2;j++)
        {
            if(i<=row&&i>=row-1 || j<=row-2&&j>=row-5) printf("%c",b[count]);
            
            else printf(" ");
        }
        
        
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='k'||ch[k]=='K') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");  
        
        for(j=1;j<=2;j++)
        {
           printf("%c%c",b[count],b[count]);
        }
        
        for(j=1;j<=row-5;j++)
        {
            if(i<=row/2)
            {
               if(j==row/2+(row/4)-3-i||j==row/2+(row/4)-2-i) { printf("%c%c",b[count],b[count]);  }
            
                else printf("  ");                      //for char K
            }
            
            else
            {
               if(j==i-(row/2+1) || j==i-(row/2)) { printf("%c%c",b[count],b[count]);   }
              
               else printf("  ");
            }
            
        }
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='l'||ch[k]=='L') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");        
        for(j=1;j<=3;j++)
        {
             printf("%c",b[count]);
        }    
                                                   ////////////////for char L
        for(j=1;j<=row;j++)
        {
            if( i<=row && i>=row-1) printf("%c",b[count]);
            
            else printf(" ");
        
        }
    
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='m'||ch[k]=='M') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");        
                                                 
        for(j=1;j<=3;j++)
        {
           printf("%c",b[count]);
        }
        
        for(j=1;j<=row-5;j++)
        {
            if(j<=i&&j>=i-2) printf("%c",b[count]);
            
            
            else printf(" ");
        }
                                        /////////////////////////////////for char M
        for(j=row-6;j>=1;j--)
        {
            if(j<=i&&j>=i-2) printf("%c",b[count]);
            
            
            else printf(" ");
        }
        for(j=1;j<=3;j++)
        { 
            printf("%c",b[count]);
        }
        
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='n'||ch[k]=='N') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");        
                                                 ////////////////for char M
        for(j=1;j<=3;j++)
        {
           printf("%c",b[count]);
        }
        
        for(j=1;j<=row-2;j++)
        {
            if(j<=i&&j>=i-2) printf("%c",b[count]);
            
            
            else printf(" ");
        }
        
        
        for(j=1;j<=3;j++)
        { 
            printf("%c",b[count]);
        }
        
        /*---------------------------------------------------------------------------------*/}
     
        if(ch[k]=='o'||ch[k]=='O') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");        
        for(j=1;j<=row-2;j++)
        {
            if(i==1||i==row||i==2||i==row-1||j==1||j==row-2||j==2||j==row-3)
            {
                printf("%c%c",b[count],b[count]);                           ///for char O
            }

            else printf("  ");
        }
    
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='p'||ch[k]=='P') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");        
        
        for(j=1;j<=3;j++)
        {
             printf("%c",b[count]);
        }   
        
       
        
        if(i==(row/2+1)) printf("%c%c%c%c%c%c%c  ",b[count],b[count],b[count],b[count],b[count],b[count],b[count]);
        
        if(i<row/2+2)
        {
        for(j=1;j<=row/2;j++)
        {
            
             if((i!=row/2+1)&&(i==1||i==2||i==row/2)) printf("%c",b[count]);
            
            else if((i!=row/2+1)) printf(" ");
            
        }
                                                //////////////////////for char P
        for(j=1;j<=row-(row/2+3);j++)
        {
            if(i<=(row/2)/2+1)
            {
              if(j<=i) printf("%c",b[count]);
           
              else printf(" ");
            }
            
            else if(i>((row/2)/2+1) && i<=row/2)
            {
              if(j<=row-(row/2+i-2)) printf("%c",b[count]);
           
              else printf(" ");
            }
        } }
        
        else
        { 
            for(j=0;j<=row-4;j++)
            { printf(" "); }
            
        }
     
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='q'||ch[k]=='Q') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");        
        for(j=1;j<=2*row-row/2;j++)
        {
            if(i==1||i==row||i==2||i==row-1||j==1||j<=2*row-row/2&&j>=2*row-row/2-2||j==2||j==3) printf("%c",b[count]);  
                                  
                                          ///for char Q
            else printf(" ");
        }
        
        for(j=1;j<row;j++)
        {
            if(i>=row-4&&(j>=i-7&&j<=3*(i-7)-2)) printf("%c",b[count]);
            
            else printf(" ");
        }
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='r'||ch[k]=='R') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");        
        
        for(j=1;j<=3;j++)
        {
             printf("%c",b[count]);
        }   
        
        
        for(j=1;j<=row/2;j++)
        {
            
             if(i==1||i==2||i==row/2||i==row/2) printf("%c",b[count]);
            
            else if(i<row/2) printf(" ");
        }
                                                //////////////////////for char R
        for(j=1;j<=row-(row/2+3);j++)
        {
            if(i<=(row/2)/2+1)
            {
              if(j<=i) printf("%c",b[count]);
           
              else printf(" ");
            }
            
            else if(i>((row/2)/2+1) && i<=row/2)
            {
              if(j<=row-(row/2+i-2)) printf("%c",b[count]);
           
              else printf(" ");
            }
        }

        for(j=1;j<=row/2+(row/4);j++)
        {
            if(i>=(row/2)+1 && (j==i-6 ||j==i-5 || j==i-4)) printf("%c",b[count]);

            else if(i>=(row/2)+1) printf(" ");

        }
    
        /*---------------------------------------------------------------------------------*/}

        if(ch[k]=='s'||ch[k]=='S') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");    

         for(j=1;j<=4;j++)
        {
            if(i<row/2) printf("%c",b[count]);
        }    
                                                   ////////////////for char S
        for(j=1;j<=row;j++)
        {
            if(i>=1 && i<=2 || i<=row && i>=row-1||i==row/2||i==row/2+1) printf("%c",b[count]);
            
            else printf(" ");
        
        }
        
        for(j=1;j<=4;j++)
        {
            if(i>=row/2) printf("%c",b[count]);
        }

        /*---------------------------------------------------------------------------------*/}

        if(ch[k]=='t'||ch[k]=='T') 
        {/*---------------------------------------------------------------------------------*/
        printf("   ");        
        
        for(j=1;j<=2*row;j++)
        {
            if(i<3) printf("%c",b[count]);
                                             //////////////for char T
            else if((i>=3) && ((j>=2*row/2-1 && j<=2*row/2+2) || (j>=1 && j<=5-i) || (j>=2*row-4+i && j<=2*row))) printf("%c",b[count]);
            
            else printf(" ");
        }
        
        /*---------------------------------------------------------------------------------*/}

        if(ch[k]=='u'||ch[k]=='U') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");       
        
        for(j=1;j<=2*row-(row/2);j++)
        {
            if( j>=1 && j<=3 || j<=2*row-(row/2) && j>=2*row-(row/2)-2|| i<=row&&i>=row-1)
            {
                printf("%c",b[count]);                           /////for char U
            }

            else printf(" ");
        }
        
        /*---------------------------------------------------------------------------------*/}
     
       if(ch[k]=='v'||ch[k]=='V') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");       
        
        for(j=1;j<=row;j++)
        {
            if( j>=i && j<=i+2)
            {
                printf("%c",b[count]);                           
            }

            else printf(" ");
        }
                                          /////////////////for char V
        for(j=row-1;j>=1;j--)
        {
            if( j>=i && j<=i+2)
            {
                printf("%c",b[count]);                          
            }

            else printf(" ");
        }
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='w'||ch[k]=='W') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");        
                                                 
        for(j=1;j<=3;j++)
        {
           printf("%c",b[count]);
        }
        
        for(j=row-3;j>=4;j--)
        {
            if(j<=i&&j>=i-2) printf("%c",b[count]);
            
            
            else printf(" ");
        }
                                /////////////////////////////////for char W
        for(j=4;j<=row-3;j++)
        {
            if(j<=i&&j>=i-2) printf("%c",b[count]);
            
            
            else printf(" ");
        }
                                        
        
        for(j=1;j<=3;j++)
        { 
            printf("%c",b[count]);
        }
        
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='x'||ch[k]=='X') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");        
                                                 
        for(j=1;j<=row;j++)
        {
                if(j==i||j==i+1||j==i-1||j==row-i+1||j==row-i||j==row-i+2) printf("%c%c",b[count],b[count]);
                                                          ///////////////for char X
                else printf("  ");
        }
        
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='y'||ch[k]=='Y') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");        
                                                 
        if(i<=row/2+1)
        {
        for(j=1;j<=row/2+1;j++)
        {
            if( j>=i && j<=i+2)
            {
                printf("%c",b[count]);                           
            }

            else printf(" ");
        }
                                          /////////////////for char Y
        for(j=(row+4)/2;j>=1;j--)
        {
            if( j>=i && j<=i+2)
            {
                printf("%c",b[count]);                          
            }

            else printf(" ");
        }
        }
        
        else if(i>row/2+1)
        { 
            for(j=1;j<=row+3;j++)
        {
            if( j>=row/2+1 && j<=row/2+3)
            {
                printf("%c",b[count]);                          
            }

            else printf(" ");
        }
        }
        /*---------------------------------------------------------------------------------*/}
        
        if(ch[k]=='z'||ch[k]=='Z') 
        {/*---------------------------------------------------------------------------------*/
        
        printf("   ");    

                                                  ////////////////for char Z
        for(j=1;j<=2*row-(row/4)-4;j++)
        {
            if(i>=1 && i<=2 || i<=row && i>=row-1 || j<=row+11-2*i && j>=row+8-2*i) printf("%c",b[count]);
            
            else printf(" ");
        
        }
        

        /*---------------------------------------------------------------------------------*/}
   
    }
    } 
    count++;
    zero = six + 1;
    }
     
    return 0;
}
