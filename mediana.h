#ifndef MEDIANA_H
#define MEDIANA_H

#include <algorithm>
#include <vector>

double mediana(std::vector<double> vec) {
  std::sort(vec.begin(), vec.end());
  int n = vec.size();
  if (n % 2 == 0) {
    return (vec[n / 2 - 1] + vec[n / 2]) / 2;
  } else {
    return vec[n / 2];
  }
}

#endif
