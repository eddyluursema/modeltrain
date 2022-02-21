const float MICROSPERSECOND = 1000000.0;
const float MILLIMETERPERMETER = 1000.0;
const float METERPERSECONDTOKMH = 3.6;

float calculateSpeed(int sensorLength, long intervalMicros, int modelScale) {
  float speed = float(sensorLength) / float(intervalMicros); // mm per usec
  speed  = speed * MICROSPERSECOND;                   // mm/s
  speed  = speed / MILLIMETERPERMETER;                // m/s
  speed  = speed * METERPERSECONDTOKMH;               // km/h
  speed  = speed * modelScale;                        // km/h in real scale
  return speed;
}
