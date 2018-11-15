
#ifndef ARM_H
#define ARM_H

#include <Arduino.h>
#include <Servo_t3.h>

const float pi=3.14159265359;

struct ServoInfo {
    int n_min, n_max;   // Nos montamos una estructura auxiliar para sobrecargar los valores máximos y mínimos de pwm de los servos
    float gain;         // PWM - radianes
    float zero;         // PWM en ángulo 0. Todavía probando algunas mejoras. Ya veremos como funciona
};

class meArm {
  public:
    meArm(int sweepMinBase=145, int sweepMaxBase=49, float angleMinBase=-pi/4, float angleMaxBase=pi/4,
      int sweepMinShoulder=118, int sweepMaxShoulder=22, float angleMinShoulder=pi/4, float angleMaxShoulder=3*pi/4,
      int sweepMinElbow=144, int sweepMaxElbow=36, float angleMinElbow=pi/4, float angleMaxElbow=-pi/4,
      int sweepMinGripper=75, int sweepMaxGripper=115, float angleMinGripper=pi/2, float angleMaxGripper=0);
    
    void begin(int pinBase, int pinShoulder, int pinElbow, int pinGripper);
    
    void gotoPoint(float x, float y, float z);
 
    void goDirectlyTo(float x, float y, float z);

    void gotoPointCylinder(float theta, float r, float z);
    void goDirectlyToCylinder(float theta, float r, float z);

    void openGripper();
    void closeGripper();

    bool isReachable(float x, float y, float z);

    float getX();
    float getY();
    float getZ();

    float getR();
    float getTheta();
  private:
    void polarToCartesian(float theta, float r, float& x, float& y);
    float _x, _y, _z;
    float _r, _t;
    Servo _base, _shoulder, _elbow, _gripper;
    ServoInfo _svoBase, _svoShoulder, _svoElbow, _svoGripper;
    int _pinBase, _pinShoulder, _pinElbow, _pinGripper;
};

#endif
