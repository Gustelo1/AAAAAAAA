#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "mediana.h"
#include <sstream>
#include <algorithm>



class Studentas {
private:
  std::string vardas_;
  std::string pavarde_;
  double egzaminas_;
  std::vector<double> nd_;

public:
  Studentas() : egzaminas_(0) { }  // default konstruktorius
  Studentas(std::istream& is);
  inline std::string vardas() const { return vardas_; }    // get'eriai, inline
  inline std::string pavarde() const { return pavarde_; }  // get'eriai, inline
  double galBalas(double (*f) (std::vector<double>) = mediana) const;  // get'eriai
  std::istream& readStudent(std::istream&);
};
