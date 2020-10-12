/*
 * @file rail_fence_cipher.cpp
 * @brief Implementation of[Rail Fence Cipher](https:en.wikipedia.org/wiki/Rail_fence_cipher), encryption and decryption
 * @details The Rail Fence Cipher is a transposition cipher which
 * derives its name from the way it is encoded. In a transposition cipher,
 * the order of the alphabets is re-arranged to obtain the cipher-text.
 *
 * In the rail fence cipher, the plain-text is written downwards and diagonally on
 * successive rails of an imaginary fence. The key corresponds to the number of rails.
 * When we reach the bottom rail, we traverse upwards moving diagonally, after reaching the top rail,
 * the direction is changed again. Thus the alphabets of the message are written in a zig-zag manner.
 * After each alphabet has been written, the individual rows are combined to obtain the cipher-text.
 *
 * For example, if the message is “RailFenceCipher” and the number of rails = 3 then cipher is prepared as:
 *
 *         R _ _ _ F _ _ _ e _ _ _ h _ _
 *         _ a _ l _ e _ c _ C _ p _ e _
 *         _ _ i _ _ _ n _ _ _ i _ _ _ r
 *
 * Reading off the message in rows the encrypted text will be : "RFehalecCpeinir"
 *
 * @author [Sushmit Goyal](https:github.com/sushmit-goyal)
 */
#include <iostream>
#include <string>
#include <cassert>

/** \namespace ciphers
 * \brief Algorithms for encryption and decryption
 */
 namespace ciphers {
    /** \namespace RailFence
     * \brief Functions for [Rail Fence Cipher](https://en.wikipedia.org/wiki/Rail_fence_cipher) algorithm
     */
     namespace RailFence {
        /**
         * @brief Class for cipher functions
         */

         class Cipher{

          public:
              std::string plainText; //the plain-text string to encrypt
              std::string cipherText; //the cipher-text string to decrypt
              int key; //the key value

          public:
              /**
             * @brief Constructor that initializes the corresponding text and key
             * @param text string, key value, boolean to check if text is plain-text or cipher-text
             */

              explicit Cipher(std::string text, int key, bool toEncrypt){
                  if(toEncrypt){
                      plainText = text;
                  } else{
                      cipherText = text;
                  }
                  this->key = key;
              }

              std::string rail_fence_encrypt(std::string text, int key); //function to encrypt plain-text

              std::string rail_fence_decrypt(std::string cipher, int key); //function to decrypt cipher-text

         };

         /**
         * @brief function that encrypts plain-text string using given key.
         * @params text : string that is to be encrypted, key : key value
         * @details
         * Here key is the number of rail rows that will be used to encrpyt text. A string array which can be treated as 2-D character array is
         * initialised which has number of rows equal to key value and number of columns equal to length of text.
         * The rail matrix is filled to distinguish filled spaces from blank ones. A boolean is used to find the
         * direction for traversing. If the current row is either the first or last row, direction is reversed.
         * The matrix is filled by iterating in the text string length. At each iteration the corresponding alphabet is filled
         * in the matrix cell. The column is incremented by 1 and the row is changed accoring to the direction boolean.
         * Hence the matrix is filled in zig-zag manner. Now the cipher text is constructed by comibining characters in rows,
         * omitting the blanks.
         * @returns string result which is the encrypted text
         */

         std::string Cipher::rail_fence_encrypt(std::string text, int key){

             
            int num_rows = key;
            int num_columns = text.length();

            // create the matrix to cipher plain text
            // key = rows , length(text) = columns
            std::string rail[num_rows];
          
            // filling the rail matrix to distinguish filled
            // spaces from blank ones
            for (int i=0; i < num_rows; i++){
                for (int j = 0; j < num_columns; j++){
                    rail[i][j] = '\n';
                }
            }
          
             // to find the direction
            bool down_dir = false;
            int row = 0, col = 0;
          
            for (int i=0; i < num_columns; i++){

                // check the direction of flow
                // reverse the direction if we've just
                // filled the top or bottom rail
                if (row == 0 || row == num_rows-1){
                    down_dir = !down_dir;
                }

                // fill the corresponding alphabet
                rail[row][col++] = text[i];
          
                  // find the next row using direction flag
                if(down_dir==true){
                    row++;
                } else{
                    row--;
                }
                
            }
          

            std::string result = "";

            //now we can construct the cipher using the rail matrix
            for (int i=0; i < num_rows; i++){
                for (int j=0; j < num_columns; j++){
                    if (rail[i][j]!='\n'){
                        result+=rail[i][j];
                    }
                }
            }
            return result;
        }

        /**
         * @brief function that decrypts cipher-text string using given key.
         * @params cipher : string that is to be decrypted, key : key value
         * @details
         * The number of rails rows = key. A string array is inisialised which is the rail matrix.
         * The rail matrix is filled to distinguish filled spaces from blank ones. A boolean is used to find the
         * direction for traversing. If the current row is either the first or last row, direction is reversed.
         * A marker '*' is placed at each cell where a text character will occur. Now the cipher text is placed in
         * the matrix row wise at the spots where '*' is placed. After filling it, we traverse the matrix in zig-zag manner
         * to obtain the original text.
         * @returns string result which is the decrypted text
         */

        std::string Cipher::rail_fence_decrypt(std::string cipher, int key){

            int num_rows = key;
            int num_columns = cipher.length();

            // create the matrix to cipher plain text
            // key = rows , length(text) = columns
            std::string rail[num_rows];
          
            // filling the rail matrix to distinguish filled
            // spaces from blank ones
            for (int i=0; i < num_rows; i++){
                for (int j=0; j < num_columns; j++){
                    rail[i][j] = '\n';
                }
            }
          
            // to find the direction
            bool down_dir = false;
          
            int row = 0, col = 0;
          
              // mark the places with '*'
            for (int i=0; i < num_columns; i++)
            {

                // check the direction of flow
                if (row == 0 || row == num_rows-1){
                    down_dir = !down_dir;
                }

                  // place the marker
                rail[row][col++] = '*';
          
                  // find the next row using direction flag
                if(down_dir==true){
                    row++;
                } else{
                    row--;
                }
            }
          
              // now we can construct the fill the rail matrix
            int index = 0;
            for (int i=0; i<num_rows; i++){
                for (int j=0; j<num_columns; j++){
                    if (rail[i][j] == '*' && index<num_columns){
                        rail[i][j] = cipher[index++];
                    }
                }
            }

            // now read the matrix in zig-zag manner to construct
               // the resultant text
            std::string result = "";
          
            row = 0, col = 0;
            for (int i=0; i< num_columns; i++){

                // check the direction of flow
                if (row == 0){
                    down_dir = true;
                }
                if (row == num_rows-1){
                    down_dir = false;
                }

                // place the marker
                if (rail[row][col] != '*'){
                    result += rail[row][col++];
                }
          
                // find the next row using direction flag
                if(down_dir==true){
                    row++;
                } else{
                    row--;
                }
            }

            return result;
        }
    } //namespace RailFence
} //namespace ciphers

/**
 * Function to test the above algorithm
 * @returns none
 */
static void test() {

    //test string 1
    std::string text1 = "HelloWorld";

    //test string 2
    std::string text2 = "ILoveALgorithms";

    //create objects to encrypt strings text1 and text2
    ciphers::RailFence::Cipher obj1(text1,3,true),obj2(text2,4,true);

    //get encrypted strings by calling encryption function
    std::string cipher1 = obj1.rail_fence_encrypt(obj1.plainText,obj1.key);
    std::string cipher2 = obj2.rail_fence_encrypt(obj2.plainText,obj2.key);

    //create objects to decrypt strings cipher1 and cipher2
    ciphers::RailFence::Cipher obj3(cipher1,obj1.key,false),obj4(cipher2,obj2.key,false);

    //get the decrypted strings by calling decryption function
    std::string decrypted1 = obj3.rail_fence_decrypt(obj3.cipherText,obj3.key);
    std::string decrypted2 = obj4.rail_fence_decrypt(obj4.cipherText,obj4.key);

    //Display the original, encrypted and decrypted strings
    std::cout<<"Original text 1: "<<text1<<std::endl;
    std::cout<<"Encrypted cipher text: "<<cipher1<<std::endl;
    std::cout<<"Decrypted text: "<<decrypted1<<std::endl<<std::endl;

    std::cout<<"Original text 2: "<<text2<<std::endl;
    std::cout<<"Encrypted cipher text: "<<cipher2<<std::endl;
    std::cout<<"Decrypted text: "<<decrypted2<<std::endl;

    
}

/**
 * Main function
 */
int main() {
    test();  /// Testing
    return 0;
}
