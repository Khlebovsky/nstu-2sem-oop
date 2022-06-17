#include "include.h"

// Implementation of the DataValidator class
bool DataValidator::validateString(string string) {
    return string.size() > 1;
}

bool DataValidator::validateImei(string IMEI) {
    return IMEI.size() == 16;
}

// Phone class implementation
double Phone::getAverageApplicationSize() {
    return this->applicationSize * 1000 / this->applicationNumber;
}

bool Phone::checkSystem() {
    if (OS.length() == 0) {
        cout << "Please install the system" << endl;

        return false;
    }

    return true;
}

void Phone::validateParams(ParamsMap params) {
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

Phone::Phone(ParamsMap &params) {
    this->validateParams(params);
}

string Phone::getManufacturer() {
    return this->manufacturer;
}

string Phone::getModel() {
    return this->model;
}

double Phone::getCpufrequency() {
    return this->CPUfrequency;
}

int Phone::getCoreNumber() {
    return this->coreNumber;
}

string Phone::getRamType() {
    return this->RAMType;
}

int Phone::getRamSize() {
    return this->RAMSize;
}

double Phone::getMemorySize() {
    return this->memorySize;
}

void Phone::setOs(string operationSystem) {
    if (!DataValidator::validateString(operationSystem)) {
        throw "Invalid OS passed";
    }

    int OSSize = rand() % 10;
    OSSize = (OSSize > 0) ? OSSize : 1;
    cout << "OS size - " << OSSize << endl;

    this->memorySize -= OSSize;

    this->OS = operationSystem;
}

string Phone::getOs() {
    return this->OS;
}

int Phone::getApplicationNumber() {
    return this->applicationNumber;
}

void Phone::setApplicationNumber(int number) {
    if (number < 0) {
        throw "Invalid number passed";
    } else if (number == 0) {
        this->hardReset();

        return;
    }

    this->applicationNumber = number;
}

double Phone::getApplicationSize() {
    return this->applicationSize;
}

void Phone::setApplicationSize(double size) {
    if (size < 0) {
        throw "Invalid size passed";
    } else if (size == 0) {
        this->hardReset();

        return;
    }

    this->applicationSize = size / 1000;
}

int Phone::getAverageApplicationNumber() {
    return floor((this->memorySize - this->applicationSize) * 1000 / this->getAverageApplicationSize());
};

void Phone::hardReset() {
    this->applicationSize = 0;
    this->applicationNumber = 0;
}

string Phone::getImei() {
    return this->IMEI;
};

// generates a random IMEI code
string generateImei() {
    int index;
    string IMEI;

    for (index = 0; index < 16; index++) {
        IMEI += to_string(rand() % 10);
    }

    return IMEI;
}

void testIphone() {
    // initialize class parameters
    ParamsMap params;
    params = {
            {"manufacturer", "Apple"},
            {"model",        "Iphone 13"},
            {"CPUfrequency", 3.2},
            {"coreNumber",   6},
            {"RAMSize",      6},
            {"RAMType",      "LPDDR4X"},
            {"MemorySize",   512.0},
            {"IMEI",         generateImei()}
    };

    Phone phone(params);

    cout << "Manufacturer - " << phone.getManufacturer() << endl;
    cout << "Model - " << phone.getModel() << endl;
    cout << "CPU frequency - " << phone.getCpufrequency() << endl;
    cout << "Core number - " << phone.getCoreNumber() << endl;
    cout << "RAM size - " << phone.getRamSize() << endl;
    cout << "RAM type - " << phone.getRamType() << endl;
    cout << "Memory size - " << phone.getMemorySize() << endl;
    cout << "IMEI - " << phone.getImei() << endl;

    phone.setOs("iOS 15");
    cout << "OS - " << phone.getOs() << endl;

    phone.setApplicationNumber(10);
    phone.setApplicationSize(732.1);
    cout << "Apps size - " << phone.getApplicationSize() << endl;
    cout << "Apps number - " << phone.getApplicationNumber() << endl;
    cout << "Average number of apps available for installation - " << phone.getAverageApplicationNumber() << endl;
}

int main() {
    srand(time(NULL));

    try {
        testIphone();

        return 0;
    } catch (const char *message) {
        cout << "Error: " << message << endl;

        return 1;
    }
}