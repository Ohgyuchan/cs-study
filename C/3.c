#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float funcForce(float w, float v, float t) {
    float g = 32.2;
    float force = (w*v) / (t*g);
    return force;
}

float funcThrust(float w, float f) {
    float thrust = w + f;
    return thrust;
}

int main() {
    float weight, velocity, time;
    printf("INPUT DATA(ex. weight velocity time):");
    scanf("%f %f %f", &weight, &velocity, &time);
    printf("OUTPUT DATA:\n%.2f\n%.2f\n%.2f\n\n", weight, velocity, time);

    float force = funcForce(weight, velocity, time);
    float thrust = funcThrust(weight, force);

    printf("Force due to acceleration: %.2f\n", force);
    printf("Total thrust due to acceleration: %.2f\n", thrust);
    return 0;
}