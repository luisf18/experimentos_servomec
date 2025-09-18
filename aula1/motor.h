#define motorDir1 10
#define motorDir2 11
#define motorEsq1 8
#define motorEsq2 7

void motor(uint8_t p1, uint8_t p2, int16_t vel) {
    if (vel < 0) {
        analogWrite(p1, 0);
        analogWrite(p2, constrain(-vel,0,255));
    } else {
        analogWrite(p1, constrain(vel,0,255) );
        analogWrite(p2, 0);
    }
}

void mover(int16_t vel_esq, int16_t vel_dir) {
    motor(motorEsq1, motorEsq2, vel_esq);
    motor(motorDir1, motorDir2, vel_dir);
}

void stop() {
    mover(0, 0);
    running = false;
}

void start(){
    running = true;
}