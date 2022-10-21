// # Part of Cosmos by OpenGenus Foundation

#include <cstddef>
#include <cstring>
#include <cstdio>

int search(const char *pattern, const char *text) {
  /**
   * @brief Searches for the given pattern in the provided text,
   *
   *
   * @param pat Pattern to search for
   * @param txt Text to search in
   *
   * @returns [int] position if pattern exists, else [bool] false
   */

  const size_t M = strlen(pattern); // length of pattern
  const size_t N = strlen(text);    // length of txt

  if (M == 0 || N == 0){
    printf("empty pattern or text provided\n");
    return false;} // empty pattern or text provided

  for (size_t i = 0; i < (N - M + 1); i++) { // loop along the text

    for (size_t j = 0; j < M; j++) { // loop through the pattern

      if (text[i + j] != pattern[j]) { // compare elements of pattern and text
        break;                         // break out of loop, if mismatch
      }
      if (j == M - 1) { // loop through the pattern passes, here we have a match
        return i;       // return  matched text index
      }
    }
  }

  return false; // return false, as match not found
}

// int main(int argc, const char **argv) {

//   search("xt", "const char *txt");

//   return 0;
// }