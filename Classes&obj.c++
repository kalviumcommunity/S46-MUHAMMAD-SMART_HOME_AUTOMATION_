# CLASSES AND OBJECTS.
#include <iostream>
#include <string>
using namespace std;

// Base class representing a general appliance
class Appliance {
protected:
    bool powerStatus;  // On/Off status

public:
    // Constructor to initialize powerStatus to off
    Appliance() : powerStatus(false) {}

    // Method to turn the appliance on
    void turnOn() {
        powerStatus = true;
        cout << "Appliance is turned ON." << endl;
    }

    // Method to turn the appliance off
    void turnOff() {
        powerStatus = false;
        cout << "Appliance is turned OFF." << endl;
    }

    // Method to check if the appliance is on
    bool isOn() {
        return powerStatus;
    }
};

// Derived class representing Lights, inheriting from Appliance
class Lights : public Appliance {
private:
    int brightness;  // Brightness level of the light

public:
    // Constructor initializing brightness to 100%
    Lights() : brightness(100) {}

    // Method to dim the light to a specified level
    void dimLight(int level) {
        if (isOn()) {
            brightness = level;
            cout << "Light dimmed to " << brightness << "%" << endl;
        } else {
            cout << "Cannot dim light because it is OFF." << endl;
        }
    }

    // Method to get the current brightness level
    int getBrightness() {
        return brightness;
    }
};

// Derived class representing a Thermostat, inheriting from Appliance
class Thermostat : public Appliance {
private:
    float temperature;  // Desired temperature

public:
    // Constructor initializing temperature to 22.0°C
    Thermostat() : temperature(22.0) {}

    // Method to set the thermostat to a specified temperature
    void setTemperature(float temp) {
        if (isOn()) {
            temperature = temp;
            cout << "Thermostat set to " << temperature << "°C" << endl;
        } else {
            cout << "Cannot set temperature because Thermostat is OFF." << endl;
        }
    }

    // Method to get the current temperature setting
    float getTemperature() {
        return temperature;
    }
};

// ControlSystem class that manages the appliances
class ControlSystem {
private:
    Lights lights;         // Light object
    Thermostat thermostat; // Thermostat object

public:
    // Method to control the lights
    void controlLights() {
        lights.turnOn();
        lights.dimLight(50);  // Dim the lights to 50%
    }

    // Method to control the thermostat
    void controlThermostat() {
        thermostat.turnOn();
        thermostat.setTemperature(24.0);  // Set temperature to 24°C
    }

    // Method to display the status of appliances
    void showStatus() {
        cout << "Light Status: " << (lights.isOn() ? "ON" : "OFF") << ", Brightness: " << lights.getBrightness() << "%" << endl;
        cout << "Thermostat Status: " << (thermostat.isOn() ? "ON" : "OFF") << ", Temperature: " << thermostat.getTemperature() << "°C" << endl;
    }
};

// Main function to demonstrate the smart home control system
int main() {
    ControlSystem homeControl;

    // Control lights and thermostat
    homeControl.controlLights();
    homeControl.controlThermostat();

    // Show the status of appliances
    homeControl.showStatus();

    return 0;
}