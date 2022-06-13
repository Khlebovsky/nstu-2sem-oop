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
    double getAverageApplicationSize() {
        return applicationSize * 1000 / applicationNumber;
    }

    bool checkSystem() {
        if (OS.length() == 0) {
            cout << "Please install the system" << endl;

            return false;
        }

        return true;
    }

protected:
    void validateParams(ParamsMap params) {
        for (const auto &[key, value]: params) {
            if (key == "manufacturer") {
                string val = get<string>(value);

                if (!DataValidator::validateString(val)) {
                    throw "Invalid manufacturer passed";
                } else {
                    this->manufacturer = val;
                }
            } else if (key == "model") {
                string val = get<string>(value);

                if (!DataValidator::validateString(val)) {
                    throw "Invalid model passed";
                } else {
                    this->model = val;
                }
            } else if (key == "CPUfrequency") {
                double val = get<double>(value);

                if (val > 0) {
                    this->CPUfrequency = val;
                } else {
                    throw "Invalid CPUfrequency passed";
                }
            } else if (key == "coreNumber") {
                int val = get<int>(value);

                if (val > 0) {
                    this->coreNumber = val;
                } else {
                    throw "Invalid coreNumber passed";
                }
            } else if (key == "RAMSize") {
                int val = get<int>(value);

                if (val > 0) {
                    this->RAMSize = val;
                } else {
                    throw "Invalid RAMSize passed";
                }
            } else if (key == "RAMType") {
                string val = get<string>(value);

                if (!DataValidator::validateString(val)) {
                    throw "Invalid RAMType passed";
                } else {
                    this->RAMType = val;
                }
            } else if (key == "MemorySize") {
                double val = get<double>(value);

                if (val > 20) {
                    this->memorySize = val;
                } else if (val > 0) {
                    throw "Not enough memory";
                } else {
                    throw "Invalid MemorySize passed";
                }
            } else if (key == "IMEI") {
                string val = get<string>(value);

                if (DataValidator::validateImei(val)) {
                    this->IMEI = val;
                } else {
                    throw "Invalid IMEI passed";
                }
            } else {
                throw "Unknown parameter passed";
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
            throw "Invalid OS passed";
        }

        int OSSize = rand() % 10;
        OSSize = (OSSize > 0) ? OSSize : 1;
        cout << "OS size - " << OSSize << endl;

        memorySize -= OSSize;

        OS = operationSystem;
    }

    string getOs() {
        return OS;
    }

    int getApplicationNumber() {
        return applicationNumber;
    }

    void setApplicationNumber(int number) {
        if (number < 0) {
            throw "Invalid number passed";
        } else if (number == 0) {
            this->hardReset();

            return;
        }

        applicationNumber = number;
    }

    double getApplicationSize() {
        return applicationSize;
    }

    // in megabytes
    void setApplicationSize(double size) {
        if (size < 0) {
            throw "Invalid size passed";
        } else if (size == 0) {
            this->hardReset();

            return;
        }

        applicationSize = size / 1000;
    }

    int getAverageApplicationNumber() {
        return floor((memorySize - applicationSize) * 1000 / this->getAverageApplicationSize());
    }

    // removes all phone apps
    void hardReset() {
        applicationSize = 0;
        applicationNumber = 0;
    }

    string getImei() {
        return IMEI;
    }
};