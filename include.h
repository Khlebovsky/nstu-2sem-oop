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
    static bool validateString(string string) {
        return string.size() > 1;
    }

    static bool validateImei(string IMEI) {
        return IMEI.size() == 16;
    }
};

class Application {
protected:
    string name;
    double size;

public:
    Application(string &name, double &size) {
        this->name = name;
        this->size = size;
    }

    string getName() {
        return name;
    }

    double getSize() const {
        return size;
    }
};

typedef map<string, Application> ApplicationsMap;

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

    bool checkSystem() {
        if (OS.length() == 0) {
            cout << "Please install the system" << endl;

            return false;
        }

        return true;
    }

protected:
    void validateParams(ParamsMap &params) {
        for (const auto &[key, value]: params) {
            if (key == "manufacturer") {
                string val = get<string>(value);

                if (!DataValidator::validateString(val)) {
                    throw invalid_argument("Invalid manufacturer passed");
                } else {
                    this->manufacturer = val;
                }
            } else if (key == "model") {
                string val = get<string>(value);

                if (!DataValidator::validateString(val)) {
                    throw invalid_argument("Invalid model passed");
                } else {
                    this->model = val;
                }
            } else if (key == "CPUfrequency") {
                double val = get<double>(value);

                if (val > 0) {
                    this->CPUfrequency = val;
                } else {
                    throw invalid_argument("Invalid CPUfrequency passed");
                }
            } else if (key == "coreNumber") {
                int val = get<int>(value);

                if (val > 0) {
                    this->coreNumber = val;
                } else {
                    throw invalid_argument("Invalid coreNumber passed");
                }
            } else if (key == "RAMSize") {
                int val = get<int>(value);

                if (val > 0) {
                    this->RAMSize = val;
                } else {
                    throw invalid_argument("Invalid RAMSize passed");
                }
            } else if (key == "RAMType") {
                string val = get<string>(value);

                if (!DataValidator::validateString(val)) {
                    throw invalid_argument("Invalid RAMType passed");
                } else {
                    this->RAMType = val;
                }
            } else if (key == "MemorySize") {
                double val = get<double>(value);

                if (val > 20) {
                    this->memorySize = val;
                } else if (val > 0) {
                    throw invalid_argument("Not enough memory");
                } else {
                    throw invalid_argument("Invalid MemorySize passed");
                }
            } else if (key == "IMEI") {
                string val = get<string>(value);

                if (DataValidator::validateImei(val)) {
                    this->IMEI = val;
                } else {
                    throw invalid_argument("Invalid IMEI passed");
                }
            } else {
                throw invalid_argument("Unknown parameter passed");
            }
        }
    }

public:
    Phone(ParamsMap &params) {
        this->validateParams(params);
    }

    string getManufacturer() {
        return manufacturer;
    }

    string getModel() {
        return model;
    }

    double getCpufrequency() {
        return CPUfrequency;
    }

    int getCoreNumber() {
        return coreNumber;
    }

    string getRamType() {
        return RAMType;
    }

    int getRamSize() {
        return RAMSize;
    }

    double getMemorySize() {
        return memorySize;
    }

    void setOs(string operationSystem) {
        if (!DataValidator::validateString(operationSystem)) {
            throw invalid_argument("Invalid OS passed");
        }

        int OSSize = rand() % 10;
        OSSize = (OSSize > 0) ? OSSize : 1;
        cout << "OS size (gb) - " << OSSize << endl;

        memorySize -= OSSize;

        OS = operationSystem;
    }

    string getOs() {
        return OS;
    }

    bool checkExistApplication(string name) {
        auto iterator = applications.find(name);

        if (iterator == applications.end()) {
            return false;
        }

        return true;
    }

    // size in megabytes
    void installApplication(string name, double size) {
        if (applications.find(name) == applications.end()) {
            Application app(name, size);
            applications.insert({name, app});
        } else {
            throw logic_error("The app is already installed");
        }
    }

    void uninstallApplication(string name) {
        if (checkExistApplication(name)) {
            auto iterator = applications.find(name);
            applications.erase(iterator);
        } else {
            throw logic_error("App not found");
        }
    }

    // in megabytes
    double getApplicationsSize() {
        double sum = 0;

        for (const auto &[key, value]: applications) {
            sum += value.getSize();
        }

        return sum;
    }

    int getApplicationsNumber() {
        return applications.size();
    }

    // removes all phone apps
    void hardReset() {
        applications.clear();
    }

    string getImei() {
        return IMEI;
    }
};