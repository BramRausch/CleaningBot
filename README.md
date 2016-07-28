# CleaningBot
This robot drives autonomous around the house sweeping. The robot has multiple sensors: three hc-sr05 distance sensor and a bumper. The bumper detects low nearby objects and the distance sensors detect objects on a distance. If the robot detects a object it goes backwards and turns to go past the object. The microcontroller used on the robot is a Arduino uno WiFi and it's connected to the WiFi network spitting out all the data it collects. 

## What does it do?
The robot drives around sensing the distance. 
If sensor 1 has a more distance left than sensor 3 and sensor 3 has less than 20cm left the robot turns right. 
If sensor 3 has a more distance left than sensor 1 and sensor 1 has less than 20cm left the robot turns left.
The default turn is to the right, If the bumper is hit or sensor 2 has less than 20cm left the robot turns right.

##Wiring:

                                          +-----+
             +----[PWR]-------------------| USB |--+
             |                            +-----+  |
             |         GND/RST2  [ ][ ]            |
             |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |   
             |          5V/MISO2 [ ][ ]  A4/SDA[ ] |    
             |                             AREF[ ] |
             |                              GND[ ] |
             | [ ]N/C                    SCK/13[ ] |   
             | [ ]IOREF                 MISO/12[ ] |   Bumper
             | [ ]RST                   MOSI/11[ ]~|   Motor control
             | [ ]3V3    +---+               10[ ]~|   Motor
             | [ ]5v    -| A |-               9[ ]~|   Motor
             | [ ]GND   -| R |-               8[ ] |   Motor
             | [ ]GND   -| D |-                    |
             | [ ]Vin   -| U |-               7[ ] |   EchoPin3
             |          -| I |-               6[ ]~|   TrigPin3
             | [ ]A0    -| N |-               5[ ]~|   EchoPin2
             | [ ]A1    -| O |-               4[ ] |   TrigPin2
             | [ ]A2     +---+           INT1/3[ ]~|   EchoPin1
             | [ ]A3                     INT0/2[ ] |   TrigPin1
             | [ ]A4/SDA  RST SCK MISO     TX>1[ ] |   
             | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] |   
             |            [ ] [ ] [ ]              |
             |  UNO_R3    GND MOSI 5V  ____________/
              \_______________________/

##Required libraries
* Wire
* ArduinoWiFi
