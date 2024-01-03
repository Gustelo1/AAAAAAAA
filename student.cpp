#include "mediana.h"
#include "Studentas.h"


Studentas::Studentas(std::istream& is) : egzaminas_(0) {
  readStudent(is);
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
  // Open the file
  std::ifstream file("students_1000000.txt");
  if (!file.is_open()) {
    std::cerr << "Unable to open file students.txt" << std::endl;
    return 1;
  }


  std::vector<Studentas> studentai;
  std::vector<Studentas> good_students;

  auto startReading = std::chrono::high_resolution_clock::now();
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    Studentas s(iss);
    if (s.galBalas() > 5) {
      good_students.push_back(s);
    } else {
      studentai.push_back(s);
    }
  }
  auto endReading = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> readingTime = endReading - startReading;

 
  file.close();

  std::cout << "Reading time: " << readingTime.count() << " seconds" << std::endl;
  return 0;
}
