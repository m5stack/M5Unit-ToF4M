/**
 * @file ContinuousWithDetails.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief M5Unit ToF4M Continuous Read Data With Details Demo.
 * @version 0.1
 * @date 2023-11-23
 *
 *
 * @Hardwares: M5Unit ToF4M
 * @Platform Version: Arduino M5Stack Board Manager v2.0.7
 * @Dependent Library:
 * VL53L1X: https://github.com/pololu/vl53l1x-arduino
 * M5Unified: https://github.com/m5stack/M5Unified
 */

#include "M5Unified.h"
#include <Wire.h>
#include <VL53L1X.h>

VL53L1X sensor;

void setup() {
    M5.begin();
    // M5.Ex_I2C.begin(21, 22, 400000);
    M5.Ex_I2C.begin();
    sensor.setBus(&Wire);
    sensor.setTimeout(500);
    if (!sensor.init()) {
        Serial.println("Failed to detect and initialize sensor!");
        while (1)
            ;
    }

    // Use long distance mode and allow up to 50000 us (50 ms) for a
    // measurement. You can change these settings to adjust the performance of
    // the sensor, but the minimum timing budget is 20 ms for short distance
    // mode and 33 ms for medium and long distance modes. See the VL53L1X
    // datasheet for more information on range and timing limits.
    sensor.setDistanceMode(VL53L1X::Long);
    sensor.setMeasurementTimingBudget(50000);

    // Start continuous readings at a rate of one measurement every 50 ms (the
    // inter-measurement period). This period should be at least as long as the
    // timing budget.
    sensor.startContinuous(50);
}

void loop() {
    sensor.read();

    Serial.print("range: ");
    Serial.print(sensor.ranging_data.range_mm);
    Serial.print("\tstatus: ");
    Serial.print(
        VL53L1X::rangeStatusToString(sensor.ranging_data.range_status));
    Serial.print("\tpeak signal: ");
    Serial.print(sensor.ranging_data.peak_signal_count_rate_MCPS);
    Serial.print("\tambient: ");
    Serial.print(sensor.ranging_data.ambient_count_rate_MCPS);

    Serial.println();
}
