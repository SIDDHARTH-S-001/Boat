# Aquasavior Vessel
<h3>Introduction</h3>
<br>This project aims to monitor and control water pollution in real-time. An unmanned surface vehicle in the form of a boat is equipped with sensors whose readings are constantly verified and sent to a cloud database. 
The boat is loaded with plants that are capable of absorbing certain pollutants from water. When the pollution level (indicated by the sensors) cross a particular threshold, the boat stops moving to let plants do their job.
Once the situation is contained within limits, the boat takes the help of GPS sensor and Magnetometer to navigate around the water body. On top of this, with consistent data from the sensors can be used to predict the pollution level in
the water body a day in advanced.

The figure below shows the workflow, 

<br> <img width="968" alt="image" src="https://github.com/SIDDHARTH-S-001/Boat/assets/73553742/72dc646a-7e92-468b-af2e-c3580e70c8fb">

<h3>CAD model</h3>
<br> Below is the CAD model of the boat (Designed in Autodesk Fusion 360).
<br> The actual boat was then manufactured using FRP.

<br><img width="575" alt="image" src="https://github.com/SIDDHARTH-S-001/Boat/assets/73553742/b3a09302-e0de-4ff6-905b-6ffdea2bd154">

<h3>Components</h3>

*  ESP32
*  Neo-6M GPS module
*  QMC5883L Magnetometer
*  JSN-SR04M-2
*  TDS Meter
*  DHT11 Temperature Humidity Sensor
*  1000 RPM Johnson Geared Motor
*  L298N Dual Channel Motor driver
*  11.1V Li-Ion battery

<br> The figure below shows the PCB that has been designed in Eagle 9.6.2 

<br> <img width="322" alt="image" src="https://github.com/SIDDHARTH-S-001/Boat/assets/73553742/d929ad75-d677-4961-b957-21810c4de6a7">

<br> You can find these files in the [PCB](https://github.com/SIDDHARTH-S-001/Boat/tree/main/PCB) folder. 
