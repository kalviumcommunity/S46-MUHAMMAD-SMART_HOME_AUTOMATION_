 SolidPrinciple1
=======

#include <iostream>
#include <string>
using namespace std;

// Base class representing a general appliance
class Appliance {
protected:
    bool powerStatus;  // On/Off status
    static int onCount;  // Static variable to count how many appliances are ON

public:
    // Constructor to initialize powerStatus to off
    Appliance() : powerStatus(false) {}

    // Method to turn the appliance on
    void turnOn() {
        if (!powerStatus) {  // Only increment count if the appliance was previously off
            powerStatus = true;
            onCount++;
            cout << "Appliance is turned ON. Total ON appliances: " << onCount << endl;
        }
    }

    // Method to turn the appliance off
    void turnOff() {
        if (powerStatus) {  // Only decrement count if the appliance was previously on
            powerStatus = false;
            onCount--;
            cout << "Appliance is turned OFF. Total ON appliances: " << onCount << endl;
        }
    }

    // Method to check if the appliance is on
    bool isOn() {
        return powerStatus;
    }

    // Static method to get the count of ON appliances
    static int getOnCount() {
        return onCount;
    }
};

// Initialize static variable
int Appliance::onCount = 0;  // Initially, no appliances are ON

// Intermediary class SmartDevice (demonstrating multilevel inheritance)
class SmartDevice : public Appliance {
public:
    // SmartDevice-specific functionality (for future extension)
    virtual void connectToWiFi() {
        if (isOn()) {
            cout << "SmartDevice is connected to WiFi." << endl;
        } else {
            cout << "Cannot connect to WiFi because the device is OFF." << endl;
        }
    }
};

// Derived class representing Lights, inheriting from SmartDevice (multilevel inheritance)
class Lights : public SmartDevice {
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

// Multilevel inheritance: Derived class SmartLight inherits from Lights
class SmartLight : public Lights {
public:
    // Additional functionality for SmartLight
    void scheduleLightOn(int hour) {
        cout << "SmartLight is scheduled to turn on at " << hour << ":00." << endl;
    }
};

// Derived class representing a Thermostat, inheriting from Appliance (single inheritance)
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
    SmartLight smartLights[3];   // Array of SmartLight objects (using multilevel inheritance)
    Thermostat thermostats[2];   // Array of Thermostat objects (using single inheritance)

public:
    // Method to control the smart lights
    void controlSmartLights() {
        for (int i = 0; i < 3; ++i) {
            smartLights[i].turnOn();
            smartLights[i].dimLight(50);  // Dim each light to 50%
            smartLights[i].scheduleLightOn(18);  // Schedule each light to turn on at 18:00
        }
    }

    // Method to control the thermostats
    void controlThermostats() {
        for (int i = 0; i < 2; ++i) {
            thermostats[i].turnOn();
            thermostats[i].setTemperature(24.0);  // Set temperature to 24°C
        }
    }

    // Method to display the status of appliances
    void showStatus() {
        cout << "Currently ON appliances: " << Appliance::getOnCount() << endl;
    }
};

int main() {
    ControlSystem homeControl;

    // Control lights and thermostat
    homeControl.controlSmartLights();
    homeControl.controlThermostats();

    // Show the status of appliances
    homeControl.showStatus();

    return 0;
}
