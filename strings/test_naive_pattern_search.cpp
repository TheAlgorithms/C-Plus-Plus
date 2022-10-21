/**
 * @file test_naive_pattern_search.cpp
 * @author zafar hussain (zafar_hussain2000@hotmail.com)
 * @brief test naive_pattern_search.cpp
 * @version 0.1
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <assert.h>

#include "naive_pattern_search.cpp"

int main() {

  assert(search("z", "const char *txt") == false);
  assert(search("", "const char *txt") == false);
  assert(search("xt", "") == false);

  assert(search("xt", "const char *txt") == 13);
  assert(search("*", "const char *txt") == 11);
  assert(search("c", "const char *txt") == 0);
  assert(search(" c", "const char *txt") == 5);
  assert(search("t ", "const char *txt") == 4);

  return 0;
}
