
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
  std::ifstream file("students_1000000.txt"); // Open the file
  if (!file.is_open()) {
    std::cerr << "Unable to open file students.txt" << std::endl;
    return 1;
  }

  auto start_reading = std::chrono::high_resolution_clock::now();

  std::vector<Studentas> studentai;
  std::vector<Studentas> good_students;
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

  auto end_reading = std::chrono::high_resolution_clock::now();
  auto duration_reading = std::chrono::duration_cast<std::chrono::milliseconds>(end_reading - start_reading);

  std::cout << "Reading time: " << duration_reading.count() << " milliseconds" << std::endl;

  file.close(); 


  auto start_sorting = std::chrono::high_resolution_clock::now();
  std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
    return a.galBalas() > b.galBalas(); 
  });
  auto end_sorting = std::chrono::high_resolution_clock::now();
  auto duration_sorting = std::chrono::duration_cast<std::chrono::milliseconds>(end_sorting - start_sorting);

  std::cout << "Sorting time: " << duration_sorting.count() << " milliseconds" << std::endl;


  return 0;
}
