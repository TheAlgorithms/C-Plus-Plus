#include <iostream>
#include <cmath>
using namespace std;

int main (){
  
   const int MAX=100;
   int V[MAX],i,c, suma;
	
 
   //Leer numero
    suma=0;
    i=0;
    
   cout<<"  Numero en binario : "; //Introducir numero a numero (1,enter,0,enter...)
   cin>>V[i];
    
	 if(V[i]==1 || V[i]==0) //para romper el bucle solamenten escribir un caracter o numero distinto de 0 o 1
	 { 	
	  
	  	while (V[i]==1 || V[i]==0)
		  {
	  	
     		i++;
     		cin>>V[i];
     		
     		}
     c=i;
    	for( int n=0 ; n<c ; n++ )
		 {
     
     		suma=suma+V[n]*pow(2,i-1);   		
			i--;
			
 			}
  
  cout<<" El numero en decimal es :  "<<suma;
								
		}
	  	
		else
		cout<<" No es un numero en binario ";
		
		cin.get();
	}
   
