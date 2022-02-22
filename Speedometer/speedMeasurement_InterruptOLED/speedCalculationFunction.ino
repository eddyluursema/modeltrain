/*
  Calculates speed of loc given the time interval passing two IR gateways according to scale and length of gateway
*/
const float METERPERSECONDTOKMH = 3.6;

float calculateSpeed(float sensorLength, long intervalMillis, int modelScale) {
  float speed = sensorLength / float(intervalMillis);   // mm per msec
   speed  = speed * METERPERSECONDTOKMH;                 // km/h
  speed  = speed * float(modelScale);                   // km/h in real scale
  return speed;
}
