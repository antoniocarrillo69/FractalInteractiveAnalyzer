// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


#include "DefinicionEcuacion.hpp"

// Constructor de la clase
DefinicionEcuacion::DefinicionEcuacion(void)
{
   // Sistema activo
   Sistema_activo = 0;

   // Ecuación en formato texto
   Ecuacion_texto[0] =  "Z = Z^2 + C";
   Ecuacion_texto[1] =  "Z = C * SIN(Z) + A";
   Ecuacion_texto[2] =  "Z = C * COS(Z) + A";
   Ecuacion_texto[3] =  "Z = C * EXP(Z) + A";
   Ecuacion_texto[4] =  "Z = C * COSH(Z) + A";
   Ecuacion_texto[5] =  "Z = C * SINH(Z) + A";
   // Asignacion de funciones
   funcion[0]  = &DefinicionEcuacion::f01;
   funcion[1]  = &DefinicionEcuacion::f02;
   funcion[2]  = &DefinicionEcuacion::f03;
   funcion[3]  = &DefinicionEcuacion::f04;
   funcion[4]  = &DefinicionEcuacion::f05;
   funcion[5]  = &DefinicionEcuacion::f06;
   // Numero de parámatros
   Numero_parametros[0] = 0;
   Numero_parametros[1] = 1;
   Numero_parametros[2] = 1;
   Numero_parametros[3] = 1;
   Numero_parametros[4] = 1;
   Numero_parametros[5] = 1;
   // Valor de los parámetros
   P[0][0] = 0.0;
   P[0][1] = 0.0;
   P[1][0] = 0.0;
   P[1][1] = 0.0;
   P[2][0] = 0.0;
   P[2][1] = 0.0;
   P[3][0] = 0.0;
   P[3][1] = 0.0;
   P[4][0] = 0.0;
   P[4][1] = 0.0;
   P[5][0] = 0.0;
   P[5][1] = 0.0;

   // Valor de Z en el escenario de Mandelbrot
   ZMandelbrot[0] = complex<long double>(0.0,0.0);
   ZMandelbrot[1] = complex<long double>(M_PI_2,0.0);
   ZMandelbrot[2] = complex<long double>(0.0,0.0);
   ZMandelbrot[3] = complex<long double>(0.0,0.0);
   ZMandelbrot[4] = complex<long double>(0.0,0.0);
   ZMandelbrot[5] = complex<long double>(0.0,0.0);


   // Valores por omisión para el punto de Julia
   Posicion.X = 0.0;
   Posicion.Y = 0.0;

   // Valor maximo para la norma
   Norma_Maxima_Mandelbrot   = 300.0;
   Norma_Minima_Mandelbrot   = 0.0;
   Norma_Maxima_Julia        = 300.0;
   Norma_Minima_Julia        = 0.0;
   Numero_Maximo_colores     = 16;
   Numero_Maximo_Iteraciones = 128;

   // Asigna parámetros
   AsignaParametros();
}


// Asigna valor a los parámetros
void DefinicionEcuacion::AsignaParametros()
{
   A = complex<long double>(P[Sistema_activo][0],P[Sistema_activo][1]);
}


