# Array Of Object.
#include <iostream>
#include <string>
using namespace std;

class Appliance {
protected:
    bool powerStatus;  // On/Off status

public:
    Appliance() : powerStatus(false) {}  // Constructor to initialize powerStatus to off

    void turnOn() {
        this->powerStatus = true;  // Using 'this' pointer to refer to the member variable
        cout << "Appliance is turned ON." << endl;
    }

    void turnOff() {
        this->powerStatus = false;  // Using 'this' pointer to refer to the member variable
        cout << "Appliance is turned OFF." << endl;
    }

    bool isOn() const {
        return this->powerStatus;  // Using 'this' pointer to refer to the member variable
    }
};

class Lights : public Appliance {
private:
    int brightness;  // Brightness level of the light

public:
    Lights() : brightness(100) {}  // Constructor initializing brightness to 100%

    void dimLight(int level) {
        if (this->isOn()) {  // Using 'this' pointer to call the member function
            this->brightness = level;  // Using 'this' pointer to refer to the member variable
            cout << "Light dimmed to " << this->brightness << "%" << endl;
        } else {
            cout << "Cannot dim light because it is OFF." << endl;
        }
    }

    int getBrightness() const {
        return this->brightness;  // Using 'this' pointer to refer to the member variable
    }
};

class Thermostat : public Appliance {
private:
    float temperature;  // Desired temperature

public:
    Thermostat() : temperature(22.0) {}  // Default temperature set to 22.0°C

    void setTemperature(float temp) {
        if (this->isOn()) {  // Using 'this' pointer to call the member function
            this->temperature = temp;  // Using 'this' pointer to refer to the member variable
            cout << "Thermostat set to " << this->temperature << "°C" << endl;
        } else {
            cout << "Cannot set temperature because Thermostat is OFF." << endl;
        }
    }

    float getTemperature() const {
        return this->temperature;  // Using 'this' pointer to refer to the member variable
    }
};

class ControlSystem {
private:
    Lights lightsArray[3];         // Array of Light objects
    Thermostat thermostatArray[2]; // Array of Thermostat objects

public:
    void controlLights() {
        for (int i = 0; i < 3; ++i) {
            lightsArray[i].turnOn();
            lightsArray[i].dimLight(50);  // Dim each light to 50%
        }
    }

    void controlThermostats() {
        for (int i = 0; i < 2; ++i) {
            thermostatArray[i].turnOn();
            thermostatArray[i].setTemperature(24.0);  // Set each thermostat to 24°C
        }
    }

    void showStatus() const {
        for (int i = 0; i < 3; ++i) {
            cout << "Light " << i + 1 << " Status: " << (lightsArray[i].isOn() ? "ON" : "OFF")
                 << ", Brightness: " << lightsArray[i].getBrightness() << "%" << endl;
        }
        for (int i = 0; i < 2; ++i) {
            cout << "Thermostat " << i + 1 << " Status: " << (thermostatArray[i].isOn() ? "ON" : "OFF")
                 << ", Temperature: " << thermostatArray[i].getTemperature() << "°C" << endl;
        }
    }
};

int main() {
    ControlSystem homeControl;

    // Control lights and thermostats
    homeControl.controlLights();
    homeControl.controlThermostats();

    // Show the status of appliances
    homeControl.showStatus();

    return 0;
}