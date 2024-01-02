#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "mediana.h"
#include <sstream>
#include <algorithm>


class Zmogus {
protected:
  std::string vardas_;
  std::string pavarde_;
  Zmogus() : vardas_(""), pavarde_("") {}

public:
  std::string vardas() const  { return vardas_; }  
  inline std::string pavarde() const  { return pavarde_; }  
};

class Studentas : public Zmogus {
private:
  double egzaminas_;
  std::vector<double> nd_;


public:
  Studentas() : egzaminas_(0) { }  // default konstruktorius
  Studentas(std::istream& is);
  double galBalas(double (*f) (std::vector<double>) = mediana) const;  // get'eriai
  std::istream& readStudent(std::istream&);
};
