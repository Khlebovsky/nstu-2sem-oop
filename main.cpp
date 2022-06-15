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