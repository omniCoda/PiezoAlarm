// NODE 2 (alarm node)
// This sensor accepts a variable from node 1 (float sensor node)
// and sets off an piezo alarm
//
//
// Piezo pin out D3
// Sensor Node ID 2
// Alarm node ID's are 2 and 3
//
//
/////////////////////////////////////////////////////////////////

#define PIEZO_BUZZER 3 // Piezo alarm pin
#define CHILD_ID 1     // ID of the sensor child
#define ALARM_ON 1     // true
#define ALARM_OFF 0    // false
//
#include <MySensor.h>
#include <SPI.h>
//
#define PARENT_NODE_ID 1  // node ID of parent - static
#define CHILD_SENSOR_ID 1 // sensor ID on this node - static
//
// 
MySensor gw;  // start gw library
//
MyMessage msgOn(CHILD_SENSOR_ID, V_TRIPPED); // set variable for message sent to controller
//
// runs once
void setup() {
/* Gateway begin                   
 * incomingMessageCallback = callback function for incoming messages from other nodes or controller and request response. Default is NULL 
 * nodeID = The unique ID (1-254) for this sensor. Default is AUTO(255) which means sensor tries to fetch an ID from controller 
 * repeaterMode = Activate repeater mode. This node will forward messages to other nodes in the radio network. Default is FALSE
 * parentNodeID = Use this to force node to always communicate with a certain parent node. Default is AUTO, which means node automatically tries to find parent.
 */
  gw.begin(incomingMessage, 1, true);
// debug to serial
  Serial.print("Serial Started");
// send sketch info to controller
  gw.sendSketchInfo("Alarm Status", "1.1");
// present info to controller
  gw.present(CHILD_SENSOR_ID, V_TRIPPED);
// designate pin & INPUT or OUTPUT for buzzer
  pinMode(3, OUTPUT);
}
//
// runs multiple times
void loop() {
// check status of incoming message - processes message recieved
  gw.process();
}
//
// function for incomingMessage
void incomingMessage(const MyMessage &message) {
// checking message type
  if (message.type == V_TRIPPED) {
// activate buzzer if message from float is true
    digitalWrite(message.sensor-1+PIEZO_BUZZER, message.getBool()?ALARM_ON:ALARM_OFF);
// debug to serial
    Serial.print("Float Status: ");
    Serial.println(message.getBool());
  }
}

