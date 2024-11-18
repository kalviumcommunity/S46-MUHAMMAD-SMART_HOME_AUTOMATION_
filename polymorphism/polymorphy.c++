// Polymorphism.

#include <iostream>
#include <string>
using namespace std;

// Base class representing a general appliance
class Appliance {
protected:
    bool powerStatus;        // On/Off status
    static int onCount;      // Static variable to count how many appliances are ON

public:
    Appliance() : powerStatus(false) {}

    void turnOn() {
        if (!powerStatus) {
            powerStatus = true;
            onCount++;
            cout << "Appliance is turned ON. Total ON appliances: " << onCount << endl;
        }
    }

    void turnOff() {
        if (powerStatus) {
            powerStatus = false;
            onCount--;
            cout << "Appliance is turned OFF. Total ON appliances: " << onCount << endl;
        }
    }

    bool isOn() {
        return powerStatus;
    }

    static int getOnCount() {
        return onCount;
    }
};

int Appliance::onCount = 0;

// SmartDevice as an intermediary class
class SmartDevice : public Appliance {
public:
    virtual void connectToWiFi() {
        if (isOn()) {
            cout << "SmartDevice is connected to WiFi." << endl;
        } else {
            cout << "Cannot connect to WiFi because the device is OFF." << endl;
        }
    }
};

// Lights class demonstrating constructor overloading
class Lights : public SmartDevice {
private:
    int brightness;

public:
    // Default constructor
    Lights() : brightness(100) {
        cout << "Default Light initialized with brightness: 100%" << endl;
    }

    // Parameterized constructor
    Lights(int initialBrightness) {
        if (initialBrightness >= 0 && initialBrightness <= 100) {
            brightness = initialBrightness;
        } else {
            brightness = 100;  // Fallback to default
        }
        cout << "Light initialized with brightness: " << brightness << "%" << endl;
    }

    // Overloaded methods for dimming the light
    void dimLight() {
        if (isOn()) {
            brightness = 50;  // Default brightness level
            cout << "Light dimmed to default 50%" << endl;
        } else {
            cout << "Cannot dim light because it is OFF." << endl;
        }
    }

    void dimLight(int level) {
        if (isOn()) {
            if (level >= 0 && level <= 100) {
                brightness = level;
                cout << "Light dimmed to " << brightness << "%" << endl;
            } else {
                cout << "Invalid brightness level. Please set a value between 0 and 100." << endl;
            }
        } else {
            cout << "Cannot dim light because it is OFF." << endl;
        }
    }
};

// Multilevel inheritance: SmartLight class
class SmartLight : public Lights {
public:
    void scheduleLightOn(int hour) {
        cout << "SmartLight scheduled to turn on at " << hour << ":00." << endl;
    }
};

// ControlSystem class managing appliances
class ControlSystem {
private:
    SmartLight smartLights[2] = {SmartLight(70), SmartLight(30)};
    Lights normalLight;

public:
    // Control smart lights
    void controlSmartLights() {
        for (int i = 0; i < 2; ++i) {
            smartLights[i].turnOn();
            smartLights[i].dimLight(40);
            smartLights[i].scheduleLightOn(18);
        }
    }

    // Control normal lights
    void controlNormalLight() {
        normalLight.turnOn();
        normalLight.dimLight();
    }

    // Show status
    void showStatus() {
        cout << "Total ON appliances: " << Appliance::getOnCount() << endl;
    }
};

int main() {
    ControlSystem homeControl;

    homeControl.controlSmartLights();
    homeControl.controlNormalLight();
    homeControl.showStatus();

    return 0;
}

