# POINTER
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
    Lights lights;         // Light object
    Thermostat thermostat; // Thermostat object

public:
    void controlLights() {
        lights.turnOn();
        lights.dimLight(50);  // Dim the lights to 50%
    }

    void controlThermostat() {
        thermostat.turnOn();
        thermostat.setTemperature(24.0);  // Set temperature to 24°C
    }

    void showStatus() const {
        cout << "Light Status: " << (lights.isOn() ? "ON" : "OFF") << ", Brightness: " << lights.getBrightness() << "%" << endl;
        cout << "Thermostat Status: " << (thermostat.isOn() ? "ON" : "OFF") << ", Temperature: " << thermostat.getTemperature() << "°C" << endl;
    }
};

int main() {
    ControlSystem homeControl;

    // Control lights and thermostat
    homeControl.controlLights();
    homeControl.controlThermostat();

    // Show the status of appliances
    homeControl.showStatus();

    return 0;
}