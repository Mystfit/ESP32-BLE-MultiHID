/*
 * A simple sketch that maps a single pin on the ESP32 to a single button on the controller
 */

#include <Arduino.h>
#include <GamepadDevice.h>
#include <BleCompositeHID.h>

BleCompositeHID compositeHID("Player indicator gamepad", "Mystfit", 100);
GamepadDevice gamepad;

void OnPlayerIndicatorChanged(uint8_t playerIndicator)
{
    Serial.println("Player indicator changed to " + String(playerIndicator));
}

void setup()
{
    GamepadConfiguration gamepadConfig;
    gamepadConfig.setIncludePlayerIndicators(true);
    gamepad.setConfig(gamepadConfig);

    FunctionSlot<uint8_t> playerIndicatorChangedSlot(OnPlayerIndicatorChanged);
    gamepad.onPlayerIndicatorChanged.attach(playerIndicatorChangedSlot);

    compositeHID.addDevice(gamepad);
    compositeHID.begin();
}

void loop()
{
    if (compositeHID.isConnected())
    {
        delay(1000);
    }
}