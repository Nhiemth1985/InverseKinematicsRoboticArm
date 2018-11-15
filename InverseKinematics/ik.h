#ifndef IK_H_INCLUDED
#define IK_H_INCLUDED

extern float L1, L2, L3;

/**
 * void cart2polar(float, float, float&, float&)
 * Obtiene coordenadas polares a partir de las
 * coordenadas cartesianas
 */
void cart2polar(float a, float b, float& r, float& theta);

/**
 * bool cosangle(float opp, float adj1, float adj2, float& theta)
 * Obtiene ángulo a partir de la regla del coseno
 */
bool cosangle(float opp, float adj1, float adj2, float& theta);

/**
 * bool solve(float x, float y, float z, float& a0, float& a1, float& a2)
 * Resuelve el cálculo de ángulos
 */
bool solve(float x, float y, float z, float& a0, float& a1, float& a2);

#endif // IK_H_INCLUDED
