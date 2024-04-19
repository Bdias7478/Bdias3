#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>

#define LED1_PATH "/sys/class/gpio/gpio2/value"
#define LED2_PATH "/sys/class/gpio/gpio2/value"
#define LED3_PATH "/sys/class/gpio/gpio2/value"
#define LED4_PATH "/sys/class/gpio/gpio2/value"
#define USER_BUTTON_PATH "/sys/class/gpio/gpio1/value"

void controlLed(const std::string& ledPath, int state) {
    std::ofstream file(ledPath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << ledPath << std::endl;
        return;
    }

    file << state;
}

int main() {
    // Export GPIO pins
    system("echo 21 > /sys/class/gpio/export");
    system("echo 22 > /sys/class/gpio/export");
    system("echo 23 > /sys/class/gpio/export");
    system("echo 24 > /sys/class/gpio/export");
    system("echo 17 > /sys/class/gpio/export");

    // Set direction for LED GPIO pins
    system("echo out > /sys/class/gpio/gpio2/direction");

    // Set direction for USER_BTN GPIO pin
    system("echo in > /sys/class/gpio/gpio1/direction");

    // Keep track of button presses
    int buttonPresses = 0;
    bool buttonPressed = false;
    bool buttonHeld = false;

    while (true) {
        // Check button state
        std::ifstream buttonFile(USER_BUTTON_PATH);
        if (buttonFile.is_open()) {
            std::string buttonState;
            buttonFile >> buttonState;
            buttonFile.close();

            // Button is pressed
            if (buttonState == "0") {
                buttonPressed = true;
                usleep(100000); // Wait for debounce
            }
            // Button is released
            else if (buttonState == "1" && buttonPressed) {
                buttonPressed = false;

                // Increment button presses
                buttonPresses++;

                // Handle different press counts
                switch (buttonPresses) {
                    case 1:
                        // Flash all LEDs
                        for (int i = 0; i < 5; ++i) {
                            controlLed(LED1_PATH, 1);
                            controlLed(LED2_PATH, 1);
                            controlLed(LED3_PATH, 1);
                            controlLed(LED4_PATH, 1);
                            usleep(500000); // 500ms delay
                            controlLed(LED1_PATH, 0);
                            controlLed(LED2_PATH, 0);
                            controlLed(LED3_PATH, 0);
                            controlLed(LED4_PATH, 0);
                            usleep(500000); // 500ms delay
                        }
                        break;
                    case 2:
                        // Blink individual LEDs
                        for (int i = 0; i < 5; ++i) {
                            controlLed(LED1_PATH, 1);
                            usleep(500000); // 500ms delay
                            controlLed(LED1_PATH, 0);
                            usleep(500000); // 500ms delay
                        }
                        for (int i = 0; i < 5; ++i) {
                            controlLed(LED2_PATH, 1);
                            usleep(500000); // 500ms delay
                            controlLed(LED2_PATH, 0);
                            usleep(500000); // 500ms delay
                        }
                        for (int i = 0; i < 5; ++i) {
                            controlLed(LED3_PATH, 1);
                            usleep(500000); // 500ms delay
                            controlLed(LED3_PATH, 0);
                            usleep(500000); // 500ms delay
                        }
                        for (int i = 0; i < 5; ++i) {
                            controlLed(LED4_PATH, 1);
                            usleep(500000); // 500ms delay
                            controlLed(LED4_PATH, 0);
                            usleep(500000); // 500ms delay
                        }
                        break;
                    default:
                        // Reset button presses after handling
                        buttonPresses = 0;
                }
            }
        }
    }

    return 0;
}

