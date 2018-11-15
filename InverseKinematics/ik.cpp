
#include "math.h"
#include "ik.h"
#include "config.h"

const float PI=3.14159265359;


void cart2polar(float a, float b, float& r, float& theta)
{
    // Determina la magnitud de las coordenadas cartesianas
    r = sqrt(a*a + b*b);

    if(r == 0) return;

    float c = a / r;
    float s = b / r;


    if(s > 1) s = 1;
    if(c > 1) c = 1;
    if(s < -1) s = -1;
    if(c < -1) c = -1;

    theta = acos(c);

    if(s < 0) theta *= -1;
}


bool cosangle(float opp, float adj1, float adj2, float& theta)
{
    // Regla del coseno:
    // C^2 = A^2 + B^2 - 2*A*B*cos(angle_AB)
    // cos(angle_AB) = (A^2 + B^2 - C^2)/(2*A*B)
    // C es el opuesto
    // A, B  son lados adyacentes
    float den = 2*adj1*adj2;

    if(den==0) return false;
    float c = (adj1*adj1 + adj2*adj2 - opp*opp)/den;

    if(c>1 || c<-1) return false;

    theta = acos(c);

    return true;
}


bool solve(float x, float y, float z, float& a0, float& a1, float& a2)
{

    float r, th0;
    cart2polar(y, x, r, th0);

    //Ajustar distancia de la muñeca(pinza + s4,s5)    
    r -= L3;

    float ang_P, R;
    cart2polar(r, z, R, ang_P);

    float B, C;
    if(!cosangle(L2, L1, R, B)) return false;
    if(!cosangle(R, L1, L2, C)) return false;

    a0 = th0;
    a1 = ang_P + B;
    a2 = C + a1 - PI;

    return true;
}
