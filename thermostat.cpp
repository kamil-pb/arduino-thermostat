/**
 * An Arduino program that reads the temperature from a thermistor and
 * determines the state of a heating pump.
 *
 * This program is meant to approximate the behavior of a thermostat, which
 * maintains the temperature within a certain range.
 */
#include <Arduino.h>

// How often to sample the temperature.
#define SAMPLE_FREQUENCY_HZ 1

// The thermostat's target temperature in Kelvin.
#define TARGET_TEMPERATURE_K 294.15

// The minimum acceptable temperature (target - 10%).
#define TARGET_TEMPERATURE_MIN_K 264.735

// The maximum acceptable temperature (target + 10%).
#define TARGET_TEMPERATURE_MAX_K 323.565

// Thermistor constants.
#define THERMISTOR_A 0.0006232719375
#define THERMISTOR_B 0.0002276660423
#define THERMISTOR_C 0.00000007184906863

// The pull up resistor's value in ohms.
#define PULL_UP_RESISTANCE 20000

// The reference voltage in volts.
#define VREF_V 3.3

// The ADC's max value (2^10 - 1).
#define ADC_MAX 1023

// The current pump state.
static bool pump_state;

/**
 * Returns whether the pump should change, given a temperature and the current
 * pump state.
 * @returns True if the pump should be on; false otherwise.
 */
static bool get_pump_state(double temperature, bool current_state) {
  if (temperature < TARGET_TEMPERATURE_MIN_K) {
    return true;
  } else if (temperature > TARGET_TEMPERATURE_MAX_K) {
    return false;
  }

  return current_state;
}

/**
 * Reads the temperature from a sensor and returns the value in Kelvin.
 * @return The temperature in Kelvin.
 */
static double read_temperature() {
  double v = ((double) analogRead(A0) / ADC_MAX) * VREF_V;
  double r = PULL_UP_RESISTANCE * v / (VREF_V - v);
  double x = log(r);

  // 1 / T = A + B * ln(R) + C * (ln(R))^3
  return 1 / (THERMISTOR_A + THERMISTOR_B * x + THERMISTOR_C * pow(x, 3));
}

/**
 * Sets up the program state.
 */
void setup() {
  // Assume the pump is initially off.
  pump_state = false;
}

/**
 * Runs the program event loop.
 */
void loop() {
  double temperature = read_temperature();
  pump_state = get_pump_state(temperature, pump_state);
  if (pump_state) {
    // TODO(kjiwa): Turn pump on.
  } else {
    // TODO(kjiwa): Turn pump off.
  }

  delay((long) (1 / SAMPLE_FREQUENCY_HZ + 0.5));
}
