/**
 * @file
 * @brief compress and decompress sparse matrix in both csr(row-wise) and csc(column_wise) format
 * (https://www.geeksforgeeks.org/sparse-matrix-representations-set-3-csr/)
 * @details
 * sparse matrix is a 2d array with a lot of zeroes (or NULL,empty) cells
 * compress the matrix by three 1d arrays I_val,J_val,val 
 * J_val stores column indices in csr format and row indices in csc format while val stores data in those indices
 *  IA[0] = 0
 *  IA[i] = IA[i-1] + no of non-zero elements in the (i-1) th row(in CSR) or column(in csc) of the Matrix
 * @author [Anmol](https://github.com/Anm01Chandel)
 */


#include <iostream>  // for IO operations
#include <cassert>	 // for assert
#include <algorithm> // for lower_bound (binary search)
#include <vector>    // for std::vector
#include <string>    // for std::string

/**
 * @namespace data_structures
 * @brief Algorithms with data structures
 */
namespace data_structures{

/**
 * few ways to declare
 * compressed_sparse_matix compressed(matrix)   //default csr format 
 * compressed_sparse_matix compressed(matrix,1) //1 for csc format , 0 for csr format
 * compressed_sparse_matix<T> {};				//declare first matrix later
 * compressed_sparsw_matrix.compressed_sparse_matix_csr(matrix);
 * here matrix is 2-d vector with some type of data
 * T can have int ,float ,even string and many other data types  
 */
template <typename T>
class compressed_sparse_matix {
private:
	std::vector<unsigned int> I_val;
	std::vector<unsigned int> J_val;
	std::vector<T> val;
	
	/**
	 * is_csc format used or not
	 */
	bool is_csc;

public:
	/**
	 * rows and columns of original matrix
	 */
	int rows=0,columns=0;
	
	// initialize
	compressed_sparse_matix(): rows(0), columns(0), is_csc(false) {}
	
	// compress matrix in csr format
	compressed_sparse_matix(std::vector<std::vector<T>> &matrix){
		compressed_sparse_matix_csr(matrix);
	}
	
	// compress matrix ,flag = 0 for CSR and flag =1 for CSS format 
	compressed_sparse_matix(std::vector<std::vector<T>> &matrix,bool flag){
		if(flag==0)compressed_sparse_matix_csr(matrix);
		else compressed_sparse_matix_csc(matrix);
	}
	
	// compress in csr format
	void compressed_sparse_matix_csr(std::vector<std::vector<T>> &matrix){
		rows=matrix.size();
		columns=matrix[0].size();

		val.clear();
		I_val.clear();
		J_val.clear();
		I_val.push_back(0);
		for(auto &l1:matrix){
			for(int l2=0;l2<columns;l2++){
				J_val.push_back(l2);
				val.push_back(l1[l2]);
			}
			I_val.push_back(J_val.size() );
		}
		is_csc=0;
	}
	
	// compress in csc format
	void compressed_sparse_matix_csc(std::vector<std::vector<T>> &matrix){
		rows=matrix.size();
		columns=matrix[0].size();

		val.clear();
		I_val.clear();
		J_val.clear();
		I_val.push_back(0);
		for(auto l1=0;l1<columns;l1++){
			for(auto l2=0;l2<rows;l2++){
				J_val.push_back(l2);
				val.push_back(matrix[l2][l1]);
			}
			I_val.push_back(J_val.size() );
		}
		is_csc=1;
	}

	/**
	 * @brief get value with index i ,j regardless of format used
	 * @return value or 0{NULL depending on data type used}
	 */
	T get_val(unsigned int i ,unsigned int j){
		if(is_csc) std::swap(i,j);
		if(i>=I_val.size()-1) return T{};
		auto it = std::lower_bound(J_val.begin()+I_val[i], J_val.begin()+I_val[i+1], j);
		if (it != J_val.begin()+I_val[i+1] && *it == j) {
        	int index = it - (J_val.begin());  
        	return val[index];
    	}
    	return T{};
	}

	/**
	 * @returns original matrix after decompressing the compressed data
	 */
	std::vector<std::vector<T>> decompress(){
		std::vector<std::vector<T>> matrix (rows,std::vector<T>(columns));
		for(int i=1;i<I_val.size();i++){
			for(int j=I_val[i-1];j<I_val[i];j++){
				if(is_csc ) 
					matrix[J_val[j]][i-1]=val[j];
				else matrix[i-1][J_val[j]]=val[j];
			}
		}
		return matrix;
	}
	
	/**
	 * @return the format used
	 */
	std::string compression_method(){ 
		if(is_csc) return "CSC";
		return "CSR";
	} 
	
};

} // namespace data_structures

/**
 * @brief Self-test implementation
 * @returns void
 */
static void tests() {
	using namespace data_structures;
    
    std::cout<<"test 1 starting\n";
    std::vector<std::vector<int>> matrix = { {1,2,0,0},{3,0,0,6},{0,0,0,0},{9,8,44,0} };	
	compressed_sparse_matix compressed(matrix,0);  

    assert(matrix == compressed.decompress());
    assert(compressed.rows==4&&compressed.columns==4);
    assert(compressed.get_val(0,0) == 1);
    assert(compressed.get_val(1,0) == 3);
    assert(compressed.get_val(3,3) == 0);
    assert(compressed.compression_method()=="CSR");
    std::cout<<"passed\n";
    
    std::cout<<"test 2 starting\n";
    std::vector<std::vector<float>> matrix2 =
    { {0,2,0} 
     ,{0,0,6} 
     ,{0,0,0} 
     ,{9,4,0} 
     ,{88,0,0} 
     ,{0,0,1}
     ,{8,0,0}
    };	
	compressed_sparse_matix<float> compressed2{};
	compressed2.compressed_sparse_matix_csc(matrix2);  
    
    assert(compressed2.rows==7&&compressed2.columns==3);
    assert(compressed2.compression_method()=="CSC");
    assert(matrix2==compressed2.decompress());
    assert(compressed2.get_val(6,0)==8);
    assert(compressed2.get_val(1,2)==6);
    assert(compressed2.get_val(0,0)==0);
    std::cout<<"passed\n";
        
    std::cout<<"test 3 starting\n";
    std::vector<std::vector<std::string>> matrix3 =
    { 
    	{ ""  ,""    ,"aa"    ,"" ,"z","cpp"},
    	{ "g" ,""    ,"hello!","K","l","z"  },
    	{ "gg","43_p","l"     ,"" ,"" ,""   }
   	};
	compressed_sparse_matix<std::string> compressed3{};
	compressed3.compressed_sparse_matix_csr(matrix3);  
    
    assert(compressed3.rows==3&&compressed3.columns==6); 
    assert(compressed3.compression_method()=="CSR");	
    assert(matrix3==compressed3.decompress());
    assert(compressed3.get_val(0,0)=="");
    assert(compressed3.get_val(0,5)=="cpp");
    assert(compressed3.get_val(2,2)=="l");
    assert(compressed3.get_val(2,4)=="");
    std::cout<<"passed\n";
    
    std::cout<<"test 4 starting\n";
    std::vector<std::vector<char>> matrix4 =
    { 
    	{ '\0',' ' ,'a' ,'b' ,'\0','\0'},
    	{ 'g' ,'\0','!' ,'h' ,'\0','z' },
    	{ '\0','\0','l' ,'0' ,'\0','\0'}
   	};
	compressed_sparse_matix<char> compressed4{matrix4}; //default csr format
    
    assert(compressed4.rows==3&&compressed4.columns==6); 
    assert(compressed4.compression_method()=="CSR");	
    assert(matrix4==compressed4.decompress());
    assert(compressed4.get_val(2,5)=='\0');
    assert(compressed4.get_val(1,5)=='z');


    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests(); 
    return 0;
}

