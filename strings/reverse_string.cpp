  /**

 * @file
 				 	Reverse String
 * 	  
 * @brief   finding the reverse of any string using two pointer approach      
 
 */

# include<iostream>
# include<vector>
# include<string>


/*
 			* swapped the value 
 @param a   A refrence call to i-th character of input string
 @param b   A refrece call to j-th character of input string
 
*/
void swap(char &a , char &b)
{ 


char temp = '\0';
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
	
/*  
  
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

std::vector<std::string> vec_str = {"AYUSH" , "BISHT", "KMONO", "BEST", "CPP","PYTHON",""};



// str will iterate through the vector "vec_str"

for(std::string str : vec_str)
{

std::cout<<"Reverse of "<<str<<" is "<<reverseString(str)<<std::endl;


}

 return 0;
 
}
