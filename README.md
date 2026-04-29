# An Arduino library for SPI-compatible boards using Lumenradio's Timotwo CRMX module
A short bare-metal Timotwo Ardunio library to check on SPI connection
- Ardunio SPI interface
- ESP32 dev boards (compatible to, i.e. ESP32 Wroom 32 or ESP32 S3)
- a [Radical Wireless LUMEN CONTROL CRMX](https://www.radicalwireless.com/products/lumen-control) board

## Current Features of the library
- Verifiying if a Timotwo model is available
- Set OEM info
- Set device name
- Set universe color
- Init TX mode and sending a test pattern via CRMX
- Showing firmware version
- Showing Link Status and Link Quality

## Current Features of the Timotwo driver
- complete list of Timotwo relevant SPI commands
