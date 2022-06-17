#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include <cmath>
#include <variant>

using namespace std;

typedef map<string, variant<int, double, string>> ParamsMap;

class Application {
protected:
    string name;
    double size;

public:
    Application(string &name, double &size);

    string getName();

    double getSize() const;
};

typedef map<string, Application> ApplicationsMap;

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

    string OS;
    string IMEI;

    ApplicationsMap applications;

    bool checkSystem();

protected:
    void validateParams(ParamsMap &params);

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

    int getApplicationsNumber();

    bool checkExistApplication(string name);

    // size in megabytes
    void installApplication(string name, double size);

    void uninstallApplication(string name);

    double getApplicationsSize();

    // removes all phone apps
    void hardReset();

    string getImei();
};