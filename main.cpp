#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <cmath>

using namespace std;

double getNumber(const string &stringToSplit, int skipAmount);

long convertDate(double date);

double convert(double number);

int main() {
    list<long> listFirstLine,
            listSecondLine;
    std::ifstream input;
    input.open("/home/oleg/CLionProjects/untitled/Lotos.txt");
    if (!input.is_open()) {
        std::cout << "Cant open file";
    } else {
        string line;
        while (getline(input, line)) {
            if (line[0] == '1') {
                listFirstLine.push_front(convertDate(getNumber(line, 5)));
            }
            if (line[0] == '2') {
                listSecondLine.push_front(convert(getNumber(line, 1)));
            }
        }
    }
    std::cout << fixed << listFirstLine.back() << std::endl;
    std::cout << fixed << listSecondLine.back() << std::endl;
    input.close();
    return 0;
}

double getNumber(const string &stringToSplit, int skipAmount) {
    std::vector<std::string> result;
    std::istringstream iss(stringToSplit);
    for (std::string s; iss >> s;) {
        result.push_back(s);
    }
    for (int i = 0; i < skipAmount; i++) {
        result.pop_back();
    }
    return stod(result.back());

}

double convert(double number) {
    const long double Tz = 86164,
            mu = 398600.44;
    return pow((pow((Tz / number), 2) * mu) / (4 * pow(M_PI, 2)), (1 / 3.));
}

long convertDate(double date) {
    double intPart, frac = modf(date, &intPart);
    long dateHours = 0;
    dateHours += (((int) (intPart - ((int) date % 1000))) / 1000 + 2000) * 365 * 24;
    dateHours += ((int) date % 1000) * 24;
    dateHours += (int) frac * 24;
    return dateHours;
}