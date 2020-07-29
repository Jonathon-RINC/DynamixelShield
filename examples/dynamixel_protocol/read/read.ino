/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <DynamixelShield.h>

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
  #include <SoftwareSerial.h>
  SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
  #define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
  #define DEBUG_SERIAL SerialUSB    
#else
  #define DEBUG_SERIAL Serial
#endif

#define TIMEOUT 10    //default communication timeout 10ms
#define ID_ADDR                 7
#define ID_ADDR_LEN             1
#define BAUDRATE_ADDR           8
#define BAUDRATE_ADDR_LEN       1
#define PROTOCOL_TYPE_ADDR      13
#define PROTOCOL_TYPE_ADDR_LEN  1

int32_t ret = 0;
uint8_t enable = 1;
uint8_t disable = 0;

const uint8_t DXL_ID = 1;
const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl;

void setup() {
  // put your setup code here, to run once:
  
  // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);   //Set debugging port baudrate to 115200bps
  while(!DEBUG_SERIAL);         //Wait until the serial port for terminal is opened
  
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(57600);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  // Read DYNAMIXEL ID
  DEBUG_SERIAL.print("ID : ");
  dxl.read(DXL_ID, ID_ADDR, ID_ADDR_LEN, (uint8_t*)&ret, sizeof(ret), TIMEOUT);
  DEBUG_SERIAL.println(ret);
  delay(1000);
  // Read DYNAMIXEL Baudrate
  DEBUG_SERIAL.print("Baud Rate : ");
  dxl.read(DXL_ID, BAUDRATE_ADDR, BAUDRATE_ADDR_LEN, (uint8_t*)&ret, sizeof(ret), TIMEOUT);
  DEBUG_SERIAL.println(ret);
  delay(1000);
  // Read DYNAMIXEL Protocol type
  DEBUG_SERIAL.print("Protocol Type : ");
  dxl.read(DXL_ID, PROTOCOL_TYPE_ADDR, PROTOCOL_TYPE_ADDR_LEN, (uint8_t*)&ret, sizeof(ret), TIMEOUT);
  DEBUG_SERIAL.println(ret);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
}
