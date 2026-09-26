# ESP32  Weather Station

> **A very special project for me!** This was my very first project, built with a lot of patience and excitement as I took my first steps into the world of electronics. It was where I began learning how to solder, read and create schematics, connect hardware, and bring together electronics, software, and the web into a working system. **November 2025**

An IoT project powered by an **ESP32** microcontroller and a **DHT11** temperature and humidity sensor. It reads environmental data in real-time and sends it to the **ThingSpeak** cloud platform via HTTP GET requests. Additionally, it features a custom web dashboard to display the data.

---

## Bill of Materials (BOM)

* **ESP32** Development Board
* **DHT11** (or DHT22) Temperature & Humidity Sensor

---

## Hardware
 ![Real Circuit Prototype]([hardware/IRL-Prototype.jpg])
> *The actual prototype! Sun-bleached wires proof that this project has been running and testing out in the real world.* **Photo taken: September 26, 2026**

---

## Project Structure

```text
.
├── firmware/         # ESP32 C++ source code (Arduino IDE)
├── web/              # Custom web dashboard interface
├── hardware/         # photos, schematics, and PCB files
└── extra/            # extra photos
