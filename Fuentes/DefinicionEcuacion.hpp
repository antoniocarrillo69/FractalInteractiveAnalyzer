// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipodromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


#ifndef __DefinicionEcuacion_HPP__
#define __DefinicionEcuacion_HPP__



#include <complex.h>
#include "Definic.hpp"


#define NUM_MAX_ECUACIONES 6

/////////////////////////////////////////////////////////////////////////////////
//         Clase que contiene la definicion de la ecuación del sistema         //
/////////////////////////////////////////////////////////////////////////////////

class DefinicionEcuacion {
   private:

      int                  ind;

      void (DefinicionEcuacion::*funcion[NUM_MAX_ECUACIONES])(void);

      void f01(void)
           {Z = Z*Z + C;}
      void f02(void)
           {Z = C*sin(Z) + A;}
      void f03(void)
           {Z = C*cos(Z) + A;}
      void f04(void)
           {Z = C*exp(Z) + A;}
      void f05(void)
           {Z = C*cosh(Z) + A;}
      void f06(void)
           {Z = C*sinh(Z) + A;}

   public:

      int                  Sistema_activo;
                           // Ecuación en formato texto
      char                *Ecuacion_texto[NUM_MAX_ECUACIONES];
                           // Parámetros del sistema
      long double          P[NUM_MAX_ECUACIONES][2];
                           // indica el numero de parametros por ecuación
      int                  Numero_parametros[NUM_MAX_ECUACIONES];
                           // Punto pasado desde Mandelbrot
      C2D                  Posicion;
                           // Valor maximo de la norma
      long double          Norma_Maxima_Mandelbrot;
      long double          Norma_Minima_Mandelbrot;
      long double          Norma_Maxima_Julia;
      long double          Norma_Minima_Julia;
      int                  Numero_Maximo_colores;
      int                  Numero_Maximo_Iteraciones;
      complex<long double> ZMandelbrot[NUM_MAX_ECUACIONES];
      complex<long double> Z,A,B,C;



                           // Constructor de la clase
                           DefinicionEcuacion(void);
                           // Calcula Mandelbrot
      int                  Calcula_Mandelbrot(const long double x, const long double y)
                           {
                              C = complex<long double>(x,y);
                              Z = ZMandelbrot[Sistema_activo];
                              ind = 0;
                              // Loop de iteraciones
                              do {
                                  (this->*funcion[Sistema_activo])();
                                  ind++;
                              } while (norm(Z) >= Norma_Minima_Mandelbrot && norm(Z) <= Norma_Maxima_Mandelbrot && ind < Numero_Maximo_Iteraciones);
                              if (ind >= Numero_Maximo_Iteraciones) return 15;
                              if (Numero_Maximo_colores > 2) return (ind%15);
                              return 0;
                           }
                           // Calcula Julia
      int                  Calcula_Julia(const long double x, const long double y)
                           {
                              C = complex<long double>(Posicion.X,Posicion.Y);
                              Z = complex<long double>(x,y);
                              ind = 0;
                              // Loop de iteraciones
                              do {
                                  (this->*funcion[Sistema_activo])();
                                  ind++;
                              } while (norm(Z) >= Norma_Minima_Julia && norm(Z) <= Norma_Maxima_Julia && ind < Numero_Maximo_Iteraciones);
                              if (ind >= Numero_Maximo_Iteraciones) return 15;
                              if (Numero_Maximo_colores > 2) return (ind%15);
                              return 15;
                           }
      void                 AsignaParametros(void);
};

#endif







