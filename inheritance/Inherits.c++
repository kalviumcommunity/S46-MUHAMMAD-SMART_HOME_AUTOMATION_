// INHERITANCE

#include <iostream>
#include <string>
using namespace std;

// Base class representing a general appliance
class Appliance {
protected:
    bool powerStatus;  // On/Off status
    static int onCount;  // Static variable to count how many appliances are ON

public:
    Appliance() : powerStatus(false) {}

    virtual void turnOn() {
        if (!powerStatus) {
            powerStatus = true;
            onCount++;
            cout << "Appliance is turned ON. Total ON appliances: " << onCount << endl;
        }
    }

    virtual void turnOff() {
        if (powerStatus) {
            powerStatus = false;
            onCount--;
            cout << "Appliance is turned OFF. Total ON appliances: " << onCount << endl;
        }
    }

    bool isOn() const {
        return powerStatus;
    }

    static int getOnCount() {
        return onCount;
    }

    virtual ~Appliance() = default;
};

int Appliance::onCount = 0;  // Initialize static variable

// Derived class: SmartDevice adds connectivity functionality
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

// Derived class: Lights add brightness control
class Lights : public SmartDevice {
protected:
    int brightness;  // Brightness level of the light

public:
    Lights() : brightness(100) {}

    void dimLight(int level) {
        if (isOn()) {
            brightness = level;
            cout << "Light dimmed to " << brightness << "%" << endl;
        } else {
            cout << "Cannot dim light because it is OFF." << endl;
        }
    }

    int getBrightness() const {
        return brightness;
    }
};

// Derived class: SmartLight adds scheduling functionality
class SmartLight : public Lights {
public:
    void scheduleLightOn(int hour) {
        if (isOn()) {
            cout << "SmartLight is scheduled to turn on at " << hour << ":00." << endl;
        } else {
            cout << "Cannot schedule SmartLight because it is OFF." << endl;
        }
    }
};

// Derived class: Thermostat adds temperature control
class Thermostat : public SmartDevice {
private:
    float temperature;

public:
    Thermostat() : temperature(22.0) {}

    void setTemperature(float temp) {
        if (isOn()) {
            temperature = temp;
            cout << "Thermostat set to " << temperature << "°C" << endl;
        } else {
            cout << "Cannot set temperature because Thermostat is OFF." << endl;
        }
    }

    float getTemperature() const {
        return temperature;
    }
};

// ControlSystem class that uses the hierarchy
class ControlSystem {
private:
    SmartLight smartLights[3];
    Thermostat thermostats[2];

public:
    void controlSmartLights() {
        for (int i = 0; i < 3; ++i) {
            smartLights[i].turnOn();
            smartLights[i].dimLight(50);  // Dim to 50%
            smartLights[i].scheduleLightOn(18);  // Schedule for 18:00
        }
    }

    void controlThermostats() {
        for (int i = 0; i < 2; ++i) {
            thermostats[i].turnOn();
            thermostats[i].setTemperature(24.0);  // Set to 24°C
        }
    }

    void showStatus() const {
        cout << "Currently ON appliances: " << Appliance::getOnCount() << endl;
    }
};

int main() {
    ControlSystem homeControl;

    homeControl.controlSmartLights();
    homeControl.controlThermostats();

    homeControl.showStatus();

    return 0;
}
