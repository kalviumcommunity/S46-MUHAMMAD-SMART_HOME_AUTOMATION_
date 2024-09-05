// New and Delete

#include <iostream>
#include <string>
using namespace std;

class Appliance {
protected:
    bool powerStatus;

public:
    Appliance() : powerStatus(false) {}

    void turnOn() {
        this->powerStatus = true; // Using 'this' pointer
        cout << "Appliance is turned ON." << endl;
    }

    void turnOff() {
        this->powerStatus = false; // Using 'this' pointer
        cout << "Appliance is turned OFF." << endl;
    }

    bool isOn() const {
        return powerStatus;
    }
};

class Lights : public Appliance {
private:
    int brightness;

public:
    Lights() : brightness(100) {}

    void dimLight(int level) {
        if (isOn()) {
            this->brightness = level; // Using 'this' pointer
            cout << "Light dimmed to " << brightness << "%" << endl;
        } else {
            cout << "Cannot dim light because it is OFF." << endl;
        }
    }

    int getBrightness() const {
        return brightness;
    }
};

class Thermostat : public Appliance {
private:
    float temperature;

public:
    Thermostat() : temperature(22.0f) {}

    void setTemperature(float temp) {
        if (isOn()) {
            this->temperature = temp; // Using 'this' pointer
            cout << "Thermostat set to " << temperature << "°C" << endl;
        } else {
            cout << "Cannot set temperature because Thermostat is OFF." << endl;
        }
    }

    float getTemperature() const {
        return temperature;
    }
};

class ControlSystem {
private:
    Lights* lights;         // Using pointers for dynamic allocation
    Thermostat* thermostat;

public:
    ControlSystem() {
        lights = new Lights[2];        // Array of objects
        thermostat = new Thermostat();
    }

    void controlLights() {
        lights[0].turnOn();
        lights[0].dimLight(50);
    }

    void controlThermostat() {
        thermostat->turnOn();
        thermostat->setTemperature(24.0f);
    }

    void showStatus() const {
        cout << "Light Status: " << (lights[0].isOn() ? "ON" : "OFF") << ", Brightness: " << lights[0].getBrightness() << "%" << endl;
        cout << "Thermostat Status: " << (thermostat->isOn() ? "ON" : "OFF") << ", Temperature: " << thermostat->getTemperature() << "°C" << endl;
    }

    ~ControlSystem() {
        delete[] lights;   // Deleting dynamically allocated memory
        delete thermostat;
    }
};

int main() {
    ControlSystem* homeControl = new ControlSystem();

    homeControl->controlLights();
    homeControl->controlThermostat();
    homeControl->showStatus();

    delete homeControl; // Clean up dynamic memory

    return 0;
}