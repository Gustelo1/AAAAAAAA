#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "mediana.h"
#include <sstream>
#include <algorithm>
#include <chrono>

class Studentas {
private:
  std::string vardas_;
  std::string pavarde_;
  double egzaminas_;
  std::vector<double> nd_;

public:
  Studentas() : egzaminas_(0) { }  // default konstruktorius
  Studentas(const Studentas& other);
  ~Studentas();
  Studentas& operator=(const Studentas& other);
  Studentas(std::istream& is);  // New constructor
  inline std::string vardas() const { return vardas_; }    // get'eriai, inline
  inline std::string pavarde() const { return pavarde_; }  // get'eriai, inline
  double galBalas(double (*f) (std::vector<double>) = mediana) const;  // get'eriai
  std::istream& readStudent(std::istream&);
};

// Implementation of the new constructor
Studentas::Studentas(std::istream& is) : egzaminas_(0) {
  readStudent(is);
}


Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_), egzaminas_(other.egzaminas_), nd_(other.nd_) {}

Studentas::~Studentas() {}



Studentas& Studentas::operator=(const Studentas& other) {
  if (this != &other) {
    vardas_ = other.vardas_;
    pavarde_ = other.pavarde_;
    egzaminas_ = other.egzaminas_;
    nd_ = other.nd_;
  }
  return *this;
}

double Studentas::galBalas(double (*f) (std::vector<double>)) const {
  std::vector<double> visi;
  visi.reserve(nd_.size() + 1);
  visi.insert(visi.end(), nd_.begin(), nd_.end());
  visi.push_back(egzaminas_);
  return (*f)(visi);
}



std::istream& Studentas::readStudent(std::istream& is) {
  std::string line;
  std::getline(is, line);
  std::istringstream iss(line);
  iss >> vardas_ >> pavarde_;
  double nd;
  while (iss >> nd) {
    nd_.push_back(nd);
  }
  iss.clear();
  iss >> egzaminas_;
  return is;
}

int main() {
    std::ifstream file("students_1000000.txt"); // Open the file
    if (!file.is_open()) {
        std::cerr << "Unable to open file students.txt" << std::endl;
        return 1;
    }


    auto startReading = std::chrono::high_resolution_clock::now();
    std::vector<Studentas> studentai;
    std::vector<Studentas> good_students;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        auto startReadingLine = std::chrono::high_resolution_clock::now();
        Studentas s(iss);
        auto endReadingLine = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> readingLineTime = endReadingLine - startReadingLine;

        if (s.galBalas() > 5) {
            good_students.push_back(s);
        } else {
            studentai.push_back(s);
        }
    }
    auto endReading = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> readingTime = endReading - startReading;

  
    std::cout << "Reading and comparisons time: " << readingTime.count() << " seconds" << std::endl;

    file.close(); 
    return 0;
}
