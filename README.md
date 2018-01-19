# Arduino Thermostat

An Arduino program that reads temperature from a thermistor and determines the state of a heating pump. The following parameters are expected to be defined:

| Parameter | Meaning |
|-----------|---------|
| SAMPLE_FREQUENCY_HZ | How often readings should be taken from the thermistor. |
| TARGET_TEMPERATURE_{MIN,MAX}_K | The minimum/maximum temperatures we can accept before altering the heat pump state.
| THERMISTOR_{A,B,C} | Thermistor constants.
| PULL_UP_RESISTANCE | The value of the pull up resistance.
| VREF_V | The reference voltage, in volts.
| ADC_MAX | The maximum value that can be read from the ADC.

The program will then regulate the heat pump state according to the following algorithm:

```python
if temp < TARGET_TEMPERATURE_MIN_K:
  pump.on()
elif temp > TARGET_TEMPERATURE_MAX_K:
  pump.off()
else:
  # maintain the current pump state
  pass
```
