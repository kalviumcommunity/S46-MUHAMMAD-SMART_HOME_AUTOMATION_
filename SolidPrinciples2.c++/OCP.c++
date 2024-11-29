
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class for appliances
class Appliance {
protected:
    bool powerStatus;        // On/Off status
    static int onCount;      // Static variable to count how many appliances are ON

public:
    Appliance() : powerStatus(false) {}

    virtual ~Appliance() = default;

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

    virtual void displayInfo() const = 0; // Pure virtual function for extending behavior
};

int Appliance::onCount = 0;

// Interface for light behavior
class LightBehavior {
public:
    virtual ~LightBehavior() = default;
    virtual void dimLight(int level) = 0;
};

// Concrete implementation for basic light control
class BasicLightController : public LightBehavior {
private:
    int brightness;

public:
    BasicLightController(int initialBrightness = 100) : brightness(initialBrightness) {}

    void dimLight(int level) override {
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

// New class: Smart dimming light controller
class SmartLightController : public LightBehavior {
private:
    int brightness;

public:
    SmartLightController(int initialBrightness = 50) : brightness(initialBrightness) {}

    void dimLight(int level) override {
        if (level >= 0 && level <= 100) {
            brightness = level;
            cout << "Smart light dimmed to " << brightness << "%. Adaptive lighting enabled." << endl;
        } else {
            cout << "Invalid brightness level for smart dimming. Please set a value between 0 and 100." << endl;
        }
    }

    int getBrightness() const {
        return brightness;
    }
};

// Derived class for lights
class Lights : public Appliance {
private:
    LightBehavior* lightBehavior; // Use abstraction for light control

public:
    Lights(LightBehavior* behavior) : lightBehavior(behavior) {}

    ~Lights() {
        delete lightBehavior;
    }

    void dimLight(int level) {
        if (isOn()) {
            lightBehavior->dimLight(level);
        } else {
            cout << "Cannot dim light because it is OFF." << endl;
        }
    }

    void displayInfo() const override {
        cout << "This is a light appliance." << endl;
    }
};

// Derived class for smart lights
class SmartLight : public Lights {
public:
    SmartLight(LightBehavior* behavior) : Lights(behavior) {}

    void scheduleLightOn(int hour) {
        cout << "SmartLight scheduled to turn on at " << hour << ":00." << endl;
    }

    void displayInfo() const override {
        cout << "This is a smart light appliance." << endl;
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
        for (const auto& appliance : appliances) {
            appliance->displayInfo();
        }
    }

    ~ApplianceManager() {
        for (auto appliance : appliances) {
            delete appliance;
        }
    }
};

// Main function to demonstrate functionality
int main() {
    ApplianceManager manager;

    SmartLight* smartLight1 = new SmartLight(new BasicLightController(70));
    SmartLight* smartLight2 = new SmartLight(new SmartLightController(50)); // Uses new behavior
    Lights* normalLight = new Lights(new BasicLightController());

    manager.addAppliance(smartLight1);
    manager.addAppliance(smartLight2);
    manager.addAppliance(normalLight);

    // Control Smart Lights
    smartLight1->turnOn();
    smartLight1->dimLight(40);
    smartLight1->scheduleLightOn(18);

    smartLight2->turnOn();
    smartLight2->dimLight(60); // Demonstrates new dimming behavior

    // Control Normal Light
    normalLight->turnOn();
    normalLight->dimLight(75);

    // Show status
    manager.showStatus();

    return 0;
}
