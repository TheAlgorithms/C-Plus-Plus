  /**

 * @file
 				 Reverse String
 * @brief           
 
 */

# include<iostream>


/*
 			* swapped the value 
 @param a   A refrence call to i-th character of input string
 @param b   A refrece call to j-th character of input string
 
*/
void swap(char &a , char &b)
{ 


char temp;
temp =a;
a = b;
b= temp;
return ;

}



/**
 	* Reverse the String -- "str"
 
 * @param str     string which has to reverse.
 * @return        reversed string
 
 */
std::string reverseString(std::string str)
{

 
	if(str.length()==1)		
	return str;
	
/* @demo 
  
  	# input :  string ( A Y U S H )
  				        i       j
  				   
  	* step 1 :  string ( H Y U S A )
  					       i   j
  					  
  	* step 2 :  string ( H S U Y A )
  					        ij
  					    
  	
  	return  :  string( H S U Y A ) 

 	
	
*/	

	int i=0,j=str.length()-1;
	
	for(;i<j;i++,j--)
	{ 
	 swap(str[i],str[j]);	  
	
	}
	
	 return str;
	
}


/** main function */

int main()
{  

std::string str;
std::cout<<"Enter the string : ";
std::cin>>str;


/* if string contain only NULL character */
if(str.empty())
{
std::cout<<"Enter a valid string "<<std::endl;
return 0;
}


std::cout<<"Reverse of "<<str<<" is "<<reverseString(str)<<std::endl;

 return 0;
 
}
