#include "include.h"

// Implementation of the DataValidator class
bool DataValidator::validateString(string string) {
    return string.size() > 1;
}

bool DataValidator::validateImei(string IMEI) {
    return IMEI.size() == 16;
}

// Application class implementation
Application::Application(string &name, double &size) {
    this->name = name;
    this->size = size;
}

string Application::getName() {
    return name;
}

double Application::getSize() const {
    return size;
}

bool Phone::checkSystem() {
    if (OS.length() == 0) {
        cout << "Please install the system" << endl;

        return false;
    }

    return true;
}

void Phone::validateParams(ParamsMap &params) {
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
        throw invalid_argument("Invalid OS passed");
    }

    int OSSize = rand() % 10;
    OSSize = (OSSize > 0) ? OSSize : 1;
    cout << "OS size (gb) - " << OSSize << endl;

    this->memorySize -= OSSize;

    this->OS = operationSystem;
}

string Phone::getOs() {
    return this->OS;
}

int Phone::getApplicationsNumber() {
    return this->applications.size();
}

void Phone::installApplication(string name, double size) {
    if (this->applications.find(name) == this->applications.end()) {
        Application app(name, size);
        this->applications.insert({name, app});
    } else {
        throw logic_error("The app is already installed");
    }
}

void Phone::uninstallApplication(string name) {
    if (checkExistApplication(name)) {
        auto iterator = this->applications.find(name);
        this->applications.erase(iterator);
    } else {
        throw logic_error("App not found");
    }
}

double Phone::getApplicationsSize() {
    double sum = 0;

    for (const auto &[key, value]: this->applications) {
        sum += value.getSize();
    }

    return sum;
}

bool Phone::checkExistApplication(string name) {
    auto iterator = applications.find(name);

    if (iterator == applications.end()) {
        return false;
    }

    return true;
}

void Phone::hardReset() {
    this->applications.clear();
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
    try {
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

        cout << "-----" << endl;

        phone.setOs("iOS 15");
        cout << "OS - " << phone.getOs() << endl;

        cout << "-----" << endl;

        phone.installApplication("Chrome", 112);
        phone.installApplication("Spotify", 145);
        cout << "Apps size - " << phone.getApplicationsSize() << endl;
        cout << "Apps count - " << phone.getApplicationsNumber() << endl;
        phone.installApplication("Spotify", 145);
    } catch (invalid_argument &exception) {
        cerr << "Invalid argument exception: " << exception.what() << endl;
    } catch (logic_error &exception) {
        cerr << "Logic error: " << exception.what() << endl;
    } catch (...) {
        cerr << "Unknown exception";
    }
}

int main() {
    srand(time(NULL));

    testIphone();
}