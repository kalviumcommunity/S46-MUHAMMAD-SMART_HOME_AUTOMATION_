#include <iostream>
#include <string>
#include <vector>
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

    bool isOn() const {
        return powerStatus;
    }

    static int getOnCount() {
        return onCount;
    }
};

int Appliance::onCount = 0;

// Class handling light-specific behavior
class LightController {
private:
    int brightness;

public:
    LightController(int initialBrightness = 100) : brightness(initialBrightness) {}

    void dimLight(int level) {
        if (level >= 0 && level <= 100) {
            brightness = level;
            cout << "Light dimmed to " << brightness << "%" << endl;
        } else {
            cout << "Invalid brightness level. Please set a value between 0 and 100." << endl;
        }
    }

    int getBrightness() const {
        return brightness;
    }
};

// Derived class for lights
class Lights : public Appliance {
private:
    LightController controller;

public:
    Lights(int initialBrightness = 100) : controller(initialBrightness) {
        cout << "Light initialized with brightness: " << controller.getBrightness() << "%" << endl;
    }

    void dimLight(int level) {
        if (isOn()) {
            controller.dimLight(level);
        } else {
            cout << "Cannot dim light because it is OFF." << endl;
        }
    }
};

// Derived class for smart lights
class SmartLight : public Lights {
public:
    SmartLight(int initialBrightness = 100) : Lights(initialBrightness) {}

    void scheduleLightOn(int hour) {
        cout << "SmartLight scheduled to turn on at " << hour << ":00." << endl;
    }
};

// Class responsible for managing all appliances
class ApplianceManager {
private:
    vector<Appliance*> appliances;

public:
    void addAppliance(Appliance* appliance) {
        appliances.push_back(appliance);
    }

    void showStatus() const {
        cout << "Total ON appliances: " << Appliance::getOnCount() << endl;
    }

    ~ApplianceManager() {
        for (auto appliance : appliances) {
            delete appliance;
        }
    }
};

int main() {
    ApplianceManager manager;

    SmartLight* smartLight1 = new SmartLight(70);
    SmartLight* smartLight2 = new SmartLight(30);
    Lights* normalLight = new Lights();

    manager.addAppliance(smartLight1);
    manager.addAppliance(smartLight2);
    manager.addAppliance(normalLight);

    // Control Smart Lights
    smartLight1->turnOn();
    smartLight1->dimLight(40);
    smartLight1->scheduleLightOn(18);

    smartLight2->turnOn();
    smartLight2->dimLight(50);

    // Control Normal Light
    normalLight->turnOn();
    normalLight->dimLight(75);

    // Show status
    manager.showStatus();

    return 0;
}
