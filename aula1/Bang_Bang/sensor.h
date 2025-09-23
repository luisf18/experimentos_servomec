#define SENSOR_COUNT (sizeof(sensores)/sizeof(*sensores))

#define S1 A6
#define S2 A5
#define S3 A4
#define S4 A3
#define S5 A2
#define S6 A1
#define S7 A0

int   sensor_trig = 70;
int   sensores[] = {S7, S6, S5, S4, S3, S2, S1};
bool  sensor_dig[SENSOR_COUNT];
int   sensor_an[SENSOR_COUNT];

void sensor_update() {
    for (size_t i = 0; i<SENSOR_COUNT; i++) {
      sensor_an[i] = analogRead(sensores[i]);
      sensor_dig[i] = (sensor_an[i] < sensor_trig);
    }
}