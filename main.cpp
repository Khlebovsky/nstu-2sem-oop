#include "include.h"

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