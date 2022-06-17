#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include <cmath>
#include <variant>

using namespace std;

typedef map<string, variant<int, double, string>> ParamsMap;

class DataValidator {
public:
    static bool validateString(string string);

    static bool validateImei(string IMEI);
};

class Phone {
private:
    string manufacturer;
    string model;

    double CPUfrequency;
    int coreNumber;

    int RAMSize; //gb
    string RAMType;

    double memorySize; // gb

    int applicationNumber = 0;
    double applicationSize = 0; //mb

    string OS;
    string IMEI;

    // in megabytes
    double getAverageApplicationSize();

    bool checkSystem();

protected:
    void validateParams(ParamsMap params);

public:
    Phone(ParamsMap &params);

    string getManufacturer();

    string getModel();

    double getCpufrequency();

    int getCoreNumber();

    string getRamType();

    int getRamSize();

    double getMemorySize();

    void setOs(string operationSystem);

    string getOs();

    int getApplicationNumber();

    void setApplicationNumber(int number);

    double getApplicationSize();

    // in megabytes
    void setApplicationSize(double size);

    int getAverageApplicationNumber();

    // removes all phone apps
    void hardReset();

    string getImei();
};