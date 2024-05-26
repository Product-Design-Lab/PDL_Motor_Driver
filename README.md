 # MotorDriver Library
 
 This library provides basic functionality to control various DC motors using PWM and direction pins. It includes support for popular motor drivers such as DRV8838, L298N, and MP6550. This module is tested on the SEEED Xiao BLE board with the FreeRTOS framework.
 
 ## Installation
 
 1. Download the library from the GitHub repository: [PDL_Motor_Driver](https://github.com/Product-Design-Lab/PDL_Motor_Driver).
 2. Unzip the library and place the `MotorDriver` folder in your Arduino `libraries` directory.
 3. Restart the Arduino IDE.
 
 ## Usage
 
 ### Including the Library
 
 ```cpp
 #include <motor_driver.h>
 ```
 
 ### Creating an Instance
 
 ```cpp
 MotorDriver motor;
 ```
 
 ### Setting Pins
 
 Different motor drivers have different pin definitions. Ensure you set the appropriate pins for the motor driver you are using. Refer to the example sketches in the `examples` folder for specific pin setups.
 
 ```cpp
 motor.setPwmPin(PWM_pin);
 motor.setDirPin(DIR_pin);
 motor.setVisenPin(VISEN_pin); // optional for current sensing
 motor.setEnablePin(ENABLE_pin); // optional for enabling motor
 ```
 
 ### Running the Motor
 
 ```cpp
 motor.runMotor(pwm); // pwm value between -1 and 1
 ```
 
 ## API Reference
 
 - `MotorDriver()`: Constructor for the MotorDriver class.
 - `~MotorDriver()`: Destructor for the MotorDriver class.
 - `void setPwmPin(const uint8_t pin)`: Set the PWM pin.
 - `void setPwmPin(const uint8_t pin1, const uint8_t pin2)`: Set two PWM pins.
 - `void setDirPin(const uint8_t pin)`: Set the direction pin.
 - `void setDirPin(const uint8_t pin1, const uint8_t pin2)`: Set two direction pins.
 - `void setDirNoPin()`: Set no direction pin.
 - `void setVisenPin(const uint8_t pin)`: Set the current sensing pin.
 - `void setVisenNoPin()`: Set no current sensing pin.
 - `void setEnablePin(const uint8_t pin)`: Set the enable pin.
 - `void setEnableNoPin()`: Set no enable pin.
 - `void setEnable(bool enable)`: Enable or disable the motor.
 - `void setMaxPwm(const uint32_t max_pwm)`: Set the maximum PWM value.
 - `void runMotor(const float pwm)`: Run the motor with a given PWM value.
 - `bool hasCurrentPin()`: Check if current sensing pin is set.
 - `int getCurrent()`: Get the current value.
 - `void setVisenSensitivity(const float A_per_V)`: Set the sensitivity for the current sensing pin.
 - `float getCurrent_mA()`: Get the current in milliamps.
 - `void setDebug(bool enable)`: Enable or disable debug mode.
 
 ## License
 
 This library is licensed under the MIT License. See the `LICENSE` file for more details.
