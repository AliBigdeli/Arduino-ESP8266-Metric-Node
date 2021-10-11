<h1 align="center">ESP8266 Metric Data Node</h1>
<h3 align="center">this is a simple Node to gather temperature and humidity form enviroment and post to server</h3>
<p align="center">
<a href="https://www.arduino.cc/" target="_blank"> <img src="https://cdn.worldvectorlogo.com/logos/arduino-1.svg" alt="arduino" width="40" height="40"/> </a> <a href="https://www.cprogramming.com/" target="_blank"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg" alt="c" width="40" height="40"/> </a> <a href="https://www.w3schools.com/cpp/" target="_blank"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" alt="cplusplus" width="40" height="40"/> </a> <a href="https://git-scm.com/" target="_blank"> <img src="https://www.vectorlogo.zone/logos/git-scm/git-scm-icon.svg" alt="git" width="40" height="40"/> </a> <a href="https://easyeda.com" target="_blank"> <img src="https://easyeda.com/images/easyeda-thumbnail.png?id=d5ed1fe5930602975df1" alt="easyeda" width="40" height="40"/> </a>
<a href="https://sparkfun.com/" target="_blank"> <img src="https://cdn.sparkfun.com/assets/5/3/4/3/1/52b1e48a757b7f28448b4567.png" alt="fritzing" width="40" height="40"/> </a>
  <a href="https://platformio.org" target="_blank"> <img src="https://cdn.platformio.org/images/platformio-logo.17fdc3bc.png" alt="platformio" width="40" height="40"/> </a>
</p>

### Overview
- [Overview](#overview)
- [Features](#features)
- [Setup](#setup)
- [Fritzing schema](#fritzing-schema)
- [Todo](#todo)
- [Bugs or Opinion](#bugs-or-opinion)



### Features
- Arduino platform
- PlatformIO Project
- ArduinoJson
- DHT
- WiFiManager
- ESPHTTPClient
- Fs / SPIFFS
- ESP8266


### Setup
All you have to do is to open the project in vscode by PlatformIO extension

### Configuration
after uploading the code all you have to is to connect to Esp access point called "Metric Node" with 12345678 as password, then you can setup server address ,device token and bearer token for authentication.
<p align="center">
<img src="https://user-images.githubusercontent.com/29748439/136797180-dda9a246-fc53-45c4-8e11-519fc65f861f.gif" alt="platformio" width="300" /> 
</p>
### Fritzing schema
A simple view of the project model schema.
<p align="center">
<img src="https://user-images.githubusercontent.com/29748439/136793875-56343e9e-0538-4308-b5e5-b89b02fba14d.PNG" alt="Fritzing schema" width="500"/>
</p>




### Todo
- [ ] refactor code
- [ ] create a video tutorial

### Bugs or Opinion
Feel free to let me know if there are any problems or any request you have for this repo.
