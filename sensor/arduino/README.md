# Arduino

**Arduino source code to manage and connect ESP8266 devices to Eclipse Kura**

**Description:**

This sections has a code structure to bringe some essential features to an IoT sensor as well the circuits examples. It allows you to:

* Create simple circuits of ESP8266
* Create low power sensors for a out of grid sensors
* Configure the sensor without a hardcode parameters based on a web interface
* Configure parameters into the WifiManager Captive Portal
* Save and reset the configurations easily

**Features:**

* WifiManager
* Low Power Energy ( Sleep Mode Option )
* Save Configurations
* Reset Configurations
* Send data to a MQTT Server
* Configure the MQTT parameters using the WifiManager
    * Custom MQTT Porta, Host, Topic

**Supported Sensors**

* Temperatura and Humidity:
    * DHT11
    * DHT22
* Power and Current:
    * EMOBLIB ( Power and Current Sensor )

**Projects**

* Temperature and Humidity Low Power:
    * Circuit: IMG
    * Code: sensor-temperature-humidity-low-power-01
* Temperature and Humidity:
    * Circuit: IMG
    * Code: sensor-temperature-humidity-01
* Power and Current + Temperature and Humidity:
    * Circuit: IMG
    * Code: sensor-temperature-humidity-power-currency-01
