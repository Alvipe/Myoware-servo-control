/* This firmware implements a simple threshold-based myoelectric control system
that uses a Myoware EMG sensor as the control input. Instead of using the
hardware-processed EMG signal provided by the Myoware sensor, the raw EMG signal
is used. This signal is digitally processed to obtain a measure of its amplitude.
First, the signal baseline is lowered to 0 V and then rectified. Then, the running
moving average of the rectified signal is computed to have the amplitude of the
signal. This amplitude is compared to an activation threshold in order to move
a servomotor. */

#include <MyoControl.h>
#include <Servo.h>

MyoControl emgSens1(A0);
MyoControl emgSens2(A1);

Servo finger1;
Servo finger2;

void setup() {
    pinMode(13, OUTPUT);
    finger1.attach(9);
    finger2.attach(10);
    finger1.writeMicroseconds(1800);
    finger2.writeMicroseconds(1800);
    Serial.begin(115200);
    delay(5000);
    emgSens1.calibration();
    emgSens2.calibration();
}

void loop() {
    if(emgSens1.activation()) {
        finger1.writeMicroseconds(1200);
        digitalWrite(13, HIGH);
    }
    else {
        finger1.writeMicroseconds(1800);
        digitalWrite(13, LOW);
    }
    if(emgSens2.activation()) {
        finger2.writeMicroseconds(1200);
        digitalWrite(13, HIGH);
    }
    else {
        finger2.writeMicroseconds(1800);
        digitalWrite(13, LOW);
    }
}
