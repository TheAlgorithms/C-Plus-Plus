/* Copyright 2019 by Contributors */
#include <cmath>
#include <iostream>
 
void sub_sequences(char *in, int i, char *out, int j) {
  /* base case for printing the sequence */
  if (in[i] == 0) {
    out[j] = '\0';
    std::cout << out << std::endl;
    return;
  }
  /* starting to form subsequences from the end */
  sub_sequences(in, i + 1, out, j);
  /* forming different sequences by adding rest of the elemets */
  out[j] = in[i];
  sub_sequences(in, i + 1, out, j + 1);
}
 
int main() {
  char in[] = "abcd";
  char out[100];
  sub_sequences(in, 0, out, 0);
}
