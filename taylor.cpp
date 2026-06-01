#include <iostream>
#include <string>
#include <cmath>
#include <random>

/* hey so it turns out you can type entire blocks of text like this 
 * using the slash and asterisk. pretty cool just wanted to 
 * give it a shot */

// Update (06/21/2023): decided to come back and add documentation

float function(float x, float a) {
  float y = sqrt(1. + pow(x,a));
  return y;
}

int main() {
  float h = 0.001;
  float x = 0.;
  float a = 2.;
  float derivative = (function(x + h,a) - function(x,a))/h;
  std::cout << derivative << std::endl;
  return 0;
}
