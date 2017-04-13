// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


#ifndef VentanaJuliaH
#define VentanaJuliaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "V_pixel.hpp"
#include "ParamJulia.h"
#include "DefinicionEcuacion.hpp"

#define ADELANTE         1
#define ATRAZ            0
#define NUM_MAX_DIM_ZOOM 10
//---------------------------------------------------------------------------
class TFormaJulia : public TForm
{
   __published:	// IDE-managed Components
        TStatusBar *BarraDeEstadosJuliaSet;
        TMainMenu *MenuPrincipal;
        TMenuItem *MenuArchivo;
        TMenuItem *MenuArchivoGrabarConfiguracion;
        TMenuItem *MenuArchivoLeerConfiguracion;
        TMenuItem *MenuArchivoReportedeConfiguracion;
        TMenuItem *Separador2;
        TMenuItem *MenuArchivoCerrar;
        TMenuItem *MenuEdicion;
        TMenuItem *MenuEdicionCopiar;
        TMenuItem *MenuEdicionPegar;
        TMenuItem *MenuCalcular;
        TMenuItem *MenuCalcularJulia;
        TMenuItem *MenuVentana;
        TMenuItem *MenuVentanaLimpiar;
        TMenuItem *MenuConfigurar;
        TMenuItem *MenuConfigurarParametros;
        TMenuItem *MenuAyuda;
        TMenuItem *MenuAyudaAcercade;
        TMenuItem *Separador1;
        TMenuItem *MenuAyudaJuliaSet;
        TMenuItem *MenuCalcularDetenerelcalculo;
        TMenuItem *Separador4;
        TMenuItem *MenuArchivoGrabarBMP;
        TMenuItem *MenuArchivoImprimir;
        TSavePictureDialog *SaveDialog;
        TTimer *Timer1;
        TMenuItem *Separador5;
        TMenuItem *MenuVentanaZoomOut;
        TMenuItem *Separador6;
        TMenuItem *MenuVentanaDimensionesOriginales;
        TPanel *Panel1;
        TPaintBox *VTJulia;
        TMenuItem *MenuConfigurarDimensions;
        TMenuItem *MenuConfigurarCalculate;
        TMenuItem *MenuConfigurarEcuation;
        TMenuItem *Separador7;
        TMenuItem *MenuCalculatePosition;
        void __fastcall MenuArchivoCerrarClick(TObject *Sender);
        void __fastcall MenuAyudaJuliaSetClick(TObject *Sender);
        void __fastcall MenuAyudaAcercadeClick(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall MenuCalculaJuliaClick(TObject *Sender);
        void __fastcall MenuVentanaLimpiarClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall MenuCalcularDetenerelcalculoClick(TObject *Sender);
        void __fastcall MenuConfigurarParametrosClick(TObject *Sender);
        void __fastcall MenuArchivoGrabarBMPClick(TObject *Sender);
        void __fastcall MenuArchivoImprimirClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall MenuVentanaZoomOutClick(TObject *Sender);
        void __fastcall MenuVentanaDimensionesOriginalesClick(
          TObject *Sender);
        void __fastcall VTJuliaMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VTJuliaMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall VTJuliaMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall MenuEdicionPegarClick(TObject *Sender);
        void __fastcall VTJuliaPaint(TObject *Sender);
        void __fastcall MenuConfigurarDimensionsClick(TObject *Sender);
        void __fastcall MenuConfigurarCalculateClick(TObject *Sender);
        void __fastcall MenuConfigurarEcuationClick(TObject *Sender);
        void __fastcall MenuCalculatePositionClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   private:	// User declarations
        // Puntero a la ventana de configuracion
        TVCap_Julia           *configura;
        char                   xcad[300];

        // Variables necesarias para dibujar recuadro de selecccion de una area 
        Definicion_Ventana     Vt1, Vt2, xVt;
        Dimencion_Ventana      Vs;
        bool                   Ventana_seleccionada;
        bool                   Sw_Dibuja_rectangulo;
        bool                   Sw_Dibuja_rectangulo_ant;
        bool                   Sw_Recuadro_activo;
        int                    Ind_zoom;
        Dimencion_Ventana      Dim_zoom[NUM_MAX_DIM_ZOOM];
        Dimencion_Ventana      Dim_orig;

        // Variables para mostrar la posición del mouse dentro de la ventana
        char                   Msg[100];

//        Arreglo_pixeles        pix[16];  // Clase que contiene los graficos generados
        Arreglo_pixeles       *pix;  // Clase que contiene los graficos generados
        C2D                    Escala1; // Escala del gráfico
        unsigned int           Pix_x;
        unsigned int           Pix_y; 
        Dimencion_Ventana      Dim_Vtn;
        TColor                 Color_fondo;
        bool                   Sw_cancela_calculo;
        bool                   Sw_Proceso_calculo;
        bool                   Sw_cerrar_ventana;
        bool                   Sw_se_grafico;

                               // Constructor de la clase 
                               TFormaJulia(void);
       
        void                   Grafica(void);
        void                   Limpiar_vantana(void);
        void                   Limpia_matriz_pixeles(void)
                               {   
                                  for (int i = 0; i < 16; i++ ) pix[i].Asigna_todo_array(false);
                               }
        void                   PasarValoresConfiguracion(void);
        void                   RetornarValoresConfiguracion(void);
        
   public:		// User declarations
        __fastcall TFormaJulia(TComponent* Owner);

        // Definición de escuación
        DefinicionEcuacion     def_ecu;
        void                   Nombre_de_ecuacion(void)
                               {
                                  sprintf(xcad,"Julia set scenery, Equation: %s",def_ecu.Ecuacion_texto[def_ecu.Sistema_activo]);
                                  Caption = xcad;
                               }
        void                   Calcula_Julia(void);
};
//---------------------------------------------------------------------------
#endif

