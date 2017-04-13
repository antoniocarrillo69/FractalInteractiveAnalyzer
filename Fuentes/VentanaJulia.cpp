// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


#include <vcl.h>
#include <Printers.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "Acecade.h"
#include "Ayuda.h"
#pragma hdrstop

#include "VentanaJulia.h"
#include "SelectEcuacion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
// Objetosglobales del sistema IyD

// Variables globales

const char *VGJ_TXT01   = "Arrastre el mouse para seleccionar el área";
char *NOMBRE_VENTANAJULIA = "Julia set scenery";
extern C2D Posicion;
extern bool Configura_escenario;
extern bool Calculo_escenario;
extern bool Detener_calculo;
extern bool Limpia_ventana;
extern bool Zoom_out;
extern void *Ventana_activa;

// Constructor de la clase
__fastcall TFormaJulia::TFormaJulia(TComponent* Owner) : TForm(Owner)
{
   // Inicialización del arreglo de pixeles
   pix = new Arreglo_pixeles [16];

   Sw_se_grafico = false;
   // Controla si esta activo algun calculo
   Sw_Proceso_calculo = false;
   Sw_cerrar_ventana = false;
   // Inicializa el indicador de recuadro
   Sw_Dibuja_rectangulo = false;
   Ventana_seleccionada = false;
   Sw_Recuadro_activo = true;

   // Dimenciones de la ventana
   Dim_Vtn.Xi = -4.0;
   Dim_Vtn.Xf = 4.0;
   Dim_Vtn.Yi = -4.0;
   Dim_Vtn.Yf = 4.0;


   // Dimensiones originales
   Dim_orig = Dim_Vtn;
   // Indice de zooms
   Ind_zoom = 0;
   
   Pix_x = VTJulia->Width;
   Pix_y = VTJulia->Height;

   // Color de los graficos
   Color_fondo = clSilver;
   
   for (int i = 0; i < 16; i++ ) pix[i].Inicializa(Pix_x,Pix_y, false, Dim_Vtn);

   // Sistema activo por omisión
   def_ecu.Sistema_activo = 0;
   def_ecu.AsignaParametros();
   Nombre_de_ecuacion();
}

// Revisa cada segundo si se ha solicitado el cierre de la ventana
void __fastcall TFormaJulia::Timer1Timer(TObject *Sender)
{
   // Almacena la ventana activa
   if (Focused()) {
      Ventana_activa = this;
   }   
   // Revisa si es la ventana activa 
   if (Ventana_activa == this) {
      // Configura el escenario
      if (Configura_escenario) {
          Configura_escenario = false;
          MenuConfigurarParametrosClick(this);
      }
      // Calcula
      if (Calculo_escenario) {
          Calculo_escenario = false;
          MenuCalculaJuliaClick(this);
      }
      // Detener cálculo
      if (Detener_calculo) {
          Detener_calculo = false;
          MenuCalcularDetenerelcalculoClick(this);
      }
      // Limpia la ventana
      if (Limpia_ventana) {
          Limpia_ventana = false;
          MenuVentanaLimpiarClick(this);
      }
      // Zoom out
      if (Zoom_out) {
          Zoom_out = false;
          MenuVentanaZoomOutClick(this);
      }
   }
   // Controla que no este calculando para cerrar la ventana
   if (Sw_cerrar_ventana && !Sw_Proceso_calculo) {
      Ventana_activa = NULL;
      Free();
   }
}


// Al solicitar cerrar la ventana ...
void __fastcall TFormaJulia::FormCloseQuery(TObject *Sender, bool &CanClose)
{
   CanClose = false;
   if (MessageBox(Handle,"Do you wish to close this window?",NOMBRE_VENTANAJULIA,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
      Sw_cancela_calculo = true;
      Sw_cerrar_ventana = true;
   }
}

// Al cerrar la forma ...
void __fastcall TFormaJulia::FormClose(TObject *Sender, TCloseAction &Action)
{
   delete []pix;
}


// Al repintar la forma ...
void __fastcall TFormaJulia::FormPaint(TObject *Sender)
{
   // Grafica el contenido de la ventana
   Grafica();        
}

// Al cambiar de tamaño la forma
void __fastcall TFormaJulia::FormResize(TObject *Sender)
{
   Sw_cancela_calculo = true;
   bool st = Sw_se_grafico;
   Sw_se_grafico = false;
   // Cambia la dimensión de la ventana de pixeles
   Pix_x = VTJulia->Width;
   Pix_y = VTJulia->Height;
   for (int i = 0; i < 16; i++ ) pix[i].Cambia_cantidad_pixeles(Pix_x,Pix_y, false, Dim_Vtn);
   // Calcula la escala de la ventana de visualizacion
   Escala1.X = (VTJulia->Width -1) / (Dim_Vtn.Xf - Dim_Vtn.Xi);
   Escala1.Y = (VTJulia->Height -1) / (Dim_Vtn.Yf - Dim_Vtn.Yi);
   if (st) Calcula_Julia();   
}


///////////////////////////////////////////////////////////////////////////////
//  Definición de Comportamientos del Menu 
///////////////////////////////////////////////////////////////////////////////

// Menu->Archivo->Grabar BMP
void __fastcall TFormaJulia::MenuArchivoGrabarBMPClick(TObject *Sender)
{
   TRect   xRect = Rect(0,0,VTJulia->ClientWidth,VTJulia->ClientHeight);
   Graphics::TBitmap *Bitmap = new Graphics::TBitmap;
   Bitmap->Width = VTJulia->ClientWidth;
   Bitmap->Height = VTJulia->ClientHeight;
   Bitmap->Canvas->CopyRect(xRect, VTJulia->Canvas, xRect);
   SaveDialog->Title = "Save as ...";
   if (SaveDialog->Execute()) Bitmap->SaveToFile(SaveDialog->FileName);           
   delete Bitmap;
}

// Menu->Archivo->Imprimir
void __fastcall TFormaJulia::MenuArchivoImprimirClick(TObject *Sender)
{
   char buff[300];
   TRect   xRect = Rect(0,0,VTJulia->ClientWidth,VTJulia->ClientHeight);
   Graphics::TBitmap *Bitmap = new Graphics::TBitmap;
   Bitmap->Width = VTJulia->ClientWidth;
   Bitmap->Height = VTJulia->ClientHeight;
   Bitmap->Canvas->CopyRect(xRect, VTJulia->Canvas, xRect);
   Bitmap->SaveToFile("Prn_img.bmp");
   delete Bitmap;
   def_ecu.C = complex<long double>(def_ecu.Posicion.X,def_ecu.Posicion.Y);
   sprintf(buff,"Dimensions(%3.8Lf, %3.8Lf, %3.8Lf, %3.8Lf)    C = (%3.8Lf,%3.8Lf)",Dim_Vtn.Xi, Dim_Vtn.Yi, Dim_Vtn.Xf, Dim_Vtn.Yf,def_ecu.Posicion.X,def_ecu.Posicion.Y);
   Bitmap = new Graphics::TBitmap;
   Bitmap->LoadFromFile("Prn_img.bmp");
   Printer()->BeginDoc();
   Printer()->Canvas->TextOut(100,10,Application->Title);
   Printer()->Canvas->TextOut(100,100,Caption);
   Printer()->Canvas->TextOut(100,200,buff);
   Printer()->Canvas->StretchDraw(Rect(100,300,Printer()->PageWidth-100,Printer()->PageWidth-200),Bitmap);
   Printer()->Canvas->TextOut(100,(Printer()->PageWidth - 100),"Antonio Carrillo Ledesma, Facultad de Ciencias, UNAM");
   Printer()->Canvas->TextOut(100,(Printer()->PageWidth - 10),"E-mail: acl@hp.fciencias.unam.mx");
   Printer()->EndDoc();
   delete Bitmap;
   unlink("Prn_img.bmp");
}

// Menu->Archivo->Cerrar
void __fastcall TFormaJulia::MenuArchivoCerrarClick(TObject *Sender)
{
   Close();     
}

// Menu->Edición->Pegar posición del mouse del aventana de Mandelbrot
void __fastcall TFormaJulia::MenuEdicionPegarClick(TObject *Sender)
{
   def_ecu.Posicion.X = Posicion.X;
   def_ecu.Posicion.Y = Posicion.Y;
}


// Menu->Calcular->Julia
void __fastcall TFormaJulia::MenuCalculaJuliaClick(TObject *Sender)
{
   Calcula_Julia();
}

// Menu->Calcular->Numero de Rotación// Menu->Calcular->Sincronización// Menu->Calcular->Exponente de Lyapunov// Menu->Ventana->Detener el calculo
void __fastcall TFormaJulia::MenuCalcularDetenerelcalculoClick(TObject *Sender)
{
   Sw_cancela_calculo  = true;
}


// Menu->Ventana->Limpiar
void __fastcall TFormaJulia::MenuVentanaLimpiarClick(TObject *Sender)
{
   Sw_se_grafico = false;
   Limpia_matriz_pixeles();
   Limpiar_vantana();
}

// Menu->Ventana->Zoom Out
void __fastcall TFormaJulia::MenuVentanaZoomOutClick(TObject *Sender)
{
   Sw_se_grafico = false;
   // Almacena las dimensiones actuales
   if (Ind_zoom > 0) {
      Ind_zoom --;
      Dim_Vtn = Dim_zoom[Ind_zoom];
      for (int i = 0; i < 16; i++ ) pix[i].Cambia_dimension(Dim_Vtn);
      // Calcula la escala de la ventana de visualizacion
      Escala1.X = (VTJulia->Width -1) / (Dim_Vtn.Xf - Dim_Vtn.Xi);
      Escala1.Y = (VTJulia->Height -1) / (Dim_Vtn.Yf - Dim_Vtn.Yi);
      Calcula_Julia();
      if (Ind_zoom < 1) MenuVentanaZoomOut->Enabled = false;
   }
}

// Menu->Ventana->Dimensiones originales
void __fastcall TFormaJulia::MenuVentanaDimensionesOriginalesClick(TObject *Sender)
{
   Sw_se_grafico = false;
   Dim_Vtn = Dim_orig;
   Ind_zoom = 0;
   MenuVentanaZoomOut->Enabled = false;
   for (int i = 0; i < 16; i++ ) pix[i].Cambia_dimension(Dim_Vtn);
   // Calcula la escala de la ventana de visualizacion
   Escala1.X = (VTJulia->Width -1) / (Dim_Vtn.Xf - Dim_Vtn.Xi);
   Escala1.Y = (VTJulia->Height -1) / (Dim_Vtn.Yf - Dim_Vtn.Yi);
   Calcula_Julia();
}

// Menu->Configura->Ecuación
void __fastcall TFormaJulia::MenuConfigurarEcuationClick(TObject *Sender)
{
   TFormSeleccionEcuacion *configura = new TFormSeleccionEcuacion(this);
   if (configura) {
      // Sistema activo
      configura->ComboBoxSeleccionEcuacion->Items->Clear();
      for( int i = 0; i < NUM_MAX_ECUACIONES; i++) {
         configura->ComboBoxSeleccionEcuacion->Items->Add(def_ecu.Ecuacion_texto[i]);
      }
      configura->ComboBoxSeleccionEcuacion->ItemIndex = def_ecu.Sistema_activo;
      configura->ShowModal();
      if (configura->Aceptar) {
         // Sistema activo
         def_ecu.Sistema_activo = configura->ComboBoxSeleccionEcuacion->ItemIndex;
         // Asigna parámetros
         def_ecu.AsignaParametros();
         Dim_Vtn = Dim_orig;
         for (int i = 0; i < 16; i++ ) pix[i].Cambia_dimension(Dim_Vtn);
         // Calcula la escala de la ventana de visualizacion
         Escala1.X = (VTJulia->Width -1) / (Dim_Vtn.Xf - Dim_Vtn.Xi);
         Escala1.Y = (VTJulia->Height -1) / (Dim_Vtn.Yf - Dim_Vtn.Yi);
         Nombre_de_ecuacion();
      }
      delete configura;
   }  
   MenuVentanaLimpiarClick(this);
}

// Menu->Configura->Parametros
void __fastcall TFormaJulia::MenuConfigurarParametrosClick(TObject *Sender)
{
   configura = new TVCap_Julia(this);
   if (configura) {
      PasarValoresConfiguracion();
      configura->TabbedNotebook1->PageIndex = 0;   
      configura->ShowModal();
      RetornarValoresConfiguracion();
      delete configura;
   }
}

// Menu->Configura->Dimensions
void __fastcall TFormaJulia::MenuConfigurarDimensionsClick(TObject *Sender)
{
   configura = new TVCap_Julia(this);
   if (configura) {
      PasarValoresConfiguracion();
      configura->TabbedNotebook1->PageIndex = 1;   
      configura->ShowModal();
      RetornarValoresConfiguracion();
      delete configura;
   }
}

// Menu->Configura->Calcular
void __fastcall TFormaJulia::MenuConfigurarCalculateClick(TObject *Sender)
{
   configura = new TVCap_Julia(this);
   if (configura) {
      PasarValoresConfiguracion();
      configura->TabbedNotebook1->PageIndex = 2;   
      configura->ShowModal();
      RetornarValoresConfiguracion();
      delete configura;
   }
}

// Menu->Configura->Position
void __fastcall TFormaJulia::MenuCalculatePositionClick(TObject *Sender)
{
   configura = new TVCap_Julia(this);
   if (configura) {
      PasarValoresConfiguracion();
      configura->TabbedNotebook1->PageIndex = 3;   
      configura->ShowModal();
      RetornarValoresConfiguracion();
      delete configura;
   }
}


// Menu->Ayuda->Acerca de ...
void __fastcall TFormaJulia::MenuAyudaAcercadeClick(TObject *Sender)
{
   TVAcercaDe *Acercade = new TVAcercaDe(this);
   if (Acercade) {
      Acercade->ShowModal();
      delete Acercade;
   }
}

// Menu->Ayuda->Julia
void __fastcall TFormaJulia::MenuAyudaJuliaSetClick(TObject *Sender)
{
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      try {
      Ayuda->Abrir_archivo(NOMBRE_VENTANAJULIA,"Julia.hlp");
      Ayuda->ShowModal();
      } catch (...) {};
      delete Ayuda;
   }
}

///////////////////////////////////////////////////////////////////////////////
//  Definición de Comportamientos de Jilia
///////////////////////////////////////////////////////////////////////////////

TColor ColoresJ[] = {
   clWhite,
   clGray,
   clSilver,
   clMaroon,
   clGreen,
   clOlive,
   clNavy,
   clPurple,
   clTeal,
   clRed,
   clLime,
   clYellow,
   clBlue,
   clFuchsia,
   clAqua,
   clBlack
};

// Calcula Julia
void TFormaJulia::Calcula_Julia(void)
{
   if (Sw_Proceso_calculo) return;
   Sw_Proceso_calculo = true;
   TCursor antcursor = Cursor;
   // Cambia el cursor del mouse
   VTJulia->Cursor = crHourGlass;
   long double Incx, Incy;
   int px, py;
   int i;
   C2D pos;
   char xcad[200];
   long double porc;

   MenuVentanaLimpiarClick(this);
   
   Incx = (Dim_Vtn.Xf - Dim_Vtn.Xi) / (long double) (Pix_x);
   Incy = (Dim_Vtn.Yf - Dim_Vtn.Yi) / (long double) (Pix_y);

   Sw_cancela_calculo = false;
   Sw_se_grafico = true;

   int Numero_Maximo_Iteraciones = def_ecu.Numero_Maximo_Iteraciones;
   def_ecu.Numero_Maximo_Iteraciones = Numero_Maximo_Iteraciones / 4;
   // Loop vertical
   for (pos.Y = Dim_Vtn.Yf; pos.Y >= Dim_Vtn.Yi; pos.Y -= Incy*5) {
       // Controla la cancelacion del calculo
       Application->ProcessMessages();
       if (Sw_cancela_calculo) break;
       // Loop horizontal
       for (pos.X = Dim_Vtn.Xi; pos.X < Dim_Vtn.Xf; pos.X += Incx*5) {
           // Julia
           i = def_ecu.Calcula_Julia(pos.X, pos.Y);
           // dibuja el punto
           pix[i].Asigna_valor(pos.X,pos.Y,true);
           px = (pos.X - Dim_Vtn.Xi) * Escala1.X;
           py = VTJulia->Height - (((pos.Y - Dim_Vtn.Yi) * Escala1.Y) + 1.0);
           VTJulia->Canvas->Pen->Color = ColoresJ[i];
           VTJulia->Canvas->Brush->Color = ColoresJ[i];
           if (px >= 0 && px < VTJulia->Width && py >= 0 && py < VTJulia->Height) VTJulia->Canvas->Rectangle(px-3,py-3,px+3,py+3);
       }
   }
   def_ecu.Numero_Maximo_Iteraciones = Numero_Maximo_Iteraciones;

   for (pos.Y = Dim_Vtn.Yf; pos.Y >= Dim_Vtn.Yi; pos.Y -= Incy) {
       porc = ( (100.0 * (Dim_Vtn.Yf - pos.Y) ) /(Dim_Vtn.Yf - Dim_Vtn.Yi) );
       sprintf(xcad,"Calculating Julia set %2.1Lf %% complete",porc);
       BarraDeEstadosJuliaSet->SimpleText=(AnsiString) xcad;
       // Controla la cancelacion del calculo
       Application->ProcessMessages();
       if (Sw_cancela_calculo) break;
       // Loop horizontal
       for (pos.X = Dim_Vtn.Xi; pos.X < Dim_Vtn.Xf; pos.X += Incx) {
           // Julia
           i = def_ecu.Calcula_Julia(pos.X, pos.Y);
           // dibuja el punto
           pix[i].Asigna_valor(pos.X,pos.Y,true);
           px = (pos.X - Dim_Vtn.Xi) * Escala1.X;
           py = VTJulia->Height - (((pos.Y - Dim_Vtn.Yi) * Escala1.Y) + 1.0);
           if (px >= 0 && px < VTJulia->Width && py >= 0 && py < VTJulia->Height) VTJulia->Canvas->Pixels[px][py] = ColoresJ[i];
       }
   }
   BarraDeEstadosJuliaSet->SimpleText=(AnsiString) " ";
   // Cambia el cursor del mouse
   VTJulia->Cursor = antcursor;
   Sw_Proceso_calculo = false;
}


// Grafica las curvas calculadas
void TFormaJulia::Grafica(void)
{
   if (!Sw_se_grafico) return;
   Sw_Proceso_calculo = true;
   unsigned int x, y;
   C2D escala;

   // Calcula la escala de la ventana de visualizacion con respecto a la ventana de pixeles
   escala.X = VTJulia->Width  / (long double) Pix_x;
   escala.Y = VTJulia->Height / (long double) Pix_y;

   // Visualiza el Julia
   for (int i = 0; i < 16; i++ ) {
      for (y = 0; y < Pix_y; y++) {
         for (x = 0; x < Pix_x; x++) {
             if (pix[i].Retorna_valor(x, y)) VTJulia->Canvas->Pixels[x * escala.X][y * escala.Y] = ColoresJ[i];
         }
      }
   }
   Sw_Proceso_calculo = false;
}

// Limpia la ventana de graficacion
void TFormaJulia::Limpiar_vantana(void)
{
   VTJulia->Canvas->Pen->Color = Color_fondo;
   VTJulia->Canvas->Brush->Color = Color_fondo;
   VTJulia->Canvas->Rectangle(0, 0, VTJulia->Width, VTJulia->Height);
}

///////////////////////////////////////////////////////////////////////////////
// Controla el movimiento del mouse y genereación del recuadro para el zoom del
// la ventana de Julia
///////////////////////////////////////////////////////////////////////////////



// Pasa los valores de configuración de la ventana de captura
void TFormaJulia::PasarValoresConfiguracion(void)
{
   ////////////////////////////////////////////////////////
   // Parámetros
   ////////////////////////////////////////////////////////
   // Parámetros
   if (def_ecu.Numero_parametros[def_ecu.Sistema_activo]) {
      configura->StaticText1->Visible = true;
      configura->ListBoxParametros->Visible = true;
      configura->ListBoxParametros->Items->Clear();
//      for(int i = 0; i < def_ecu.Numero_parametros[def_ecu.Sistema_activo]; i++) {
         sprintf(xcad,"Re(A)  = %1.10Lf",def_ecu.P[def_ecu.Sistema_activo][0]);
         configura->ListBoxParametros->Items->Add(xcad);
         sprintf(xcad,"Im(A)  = %1.10Lf",def_ecu.P[def_ecu.Sistema_activo][1]);
         configura->ListBoxParametros->Items->Add(xcad);
//      }
   }  
   ////////////////////////////////////////////////////////
   // Dimensiones
   ////////////////////////////////////////////////////////
   sprintf(xcad,"%1.10Lf",Dim_Vtn.Xi);
   configura->EditHMin->Text = (AnsiString) xcad;
   sprintf(xcad,"%1.10Lf",Dim_Vtn.Xf);
   configura->EditHMax->Text = (AnsiString) xcad;
   sprintf(xcad,"%1.10Lf",Dim_Vtn.Yi);
   configura->EditVMin->Text = (AnsiString) xcad;
   sprintf(xcad,"%1.10Lf",Dim_Vtn.Yf);
   configura->EditVMax->Text = (AnsiString) xcad;
   ////////////////////////////////////////////////////////
   // Escenario
   ////////////////////////////////////////////////////////
   sprintf(xcad,"%1.10Lf",def_ecu.Norma_Minima_Julia);
   configura->Edit8->Text = (AnsiString) xcad;
   sprintf(xcad,"%1.10Lf",def_ecu.Norma_Maxima_Julia);
   configura->Edit1->Text = (AnsiString) xcad;
   sprintf(xcad,"%d",def_ecu.Numero_Maximo_Iteraciones);
   configura->Edit9->Text = (AnsiString) xcad;
   sprintf(xcad,"%d",def_ecu.Numero_Maximo_colores);
   configura->Edit10->Text = (AnsiString) xcad;
   ////////////////////////////////////////////////////////
   // Parametro
   ////////////////////////////////////////////////////////
   sprintf(xcad,"%1.10Lf",def_ecu.Posicion.X);
   configura->EditPosicionX->Text = (AnsiString) xcad;
   sprintf(xcad,"%1.10Lf",def_ecu.Posicion.Y);
   configura->EditPosicionY->Text = (AnsiString) xcad;
}

// Retorna los valores de configuración de la ventana de captura
void TFormaJulia::RetornarValoresConfiguracion(void)
{
   if (!configura->Aceptar) return;
   ////////////////////////////////////////////////////////
   // Parámetros
   ////////////////////////////////////////////////////////
   if (def_ecu.Numero_parametros[def_ecu.Sistema_activo]) {
//   for (int i = 0; i < def_ecu.Numero_parametros[def_ecu.Sistema_activo]; i++) {
       int i = 0;
       unsigned int i1, i2;
       char xcad[100], xcad1[100];
       strcpy(xcad1,configura->ListBoxParametros->Items->Strings[i].c_str());
       // Valor del parámetro
       for (i2 = 0, i1 = 9; i1 < strlen(xcad1); i2++, i1++) xcad[i2] = xcad1[i1];
       xcad[i2] = 0;
       def_ecu.P[def_ecu.Sistema_activo][0] = _atold(xcad);

       i++;
       strcpy(xcad1,configura->ListBoxParametros->Items->Strings[i].c_str());
       // Valor del parámetro
       for (i2 = 0, i1 = 9; i1 < strlen(xcad1); i2++, i1++) xcad[i2] = xcad1[i1];
       xcad[i2] = 0;
       def_ecu.P[def_ecu.Sistema_activo][1] = _atold(xcad);
//   }
       def_ecu.AsignaParametros();
   }
   ////////////////////////////////////////////////////////
   // Dimensiones
   ////////////////////////////////////////////////////////
   Dim_Vtn.Xi = _atold(configura->EditHMin->Text.c_str());       
   Dim_Vtn.Xf = _atold(configura->EditHMax->Text.c_str());       
   Dim_Vtn.Yi = _atold(configura->EditVMin->Text.c_str());       
   Dim_Vtn.Yf = _atold(configura->EditVMax->Text.c_str());
   ////////////////////////////////////////////////////////
   // Escenario
   ////////////////////////////////////////////////////////
   def_ecu.Norma_Minima_Julia = _atold(configura->Edit8->Text.c_str());       
   def_ecu.Norma_Maxima_Julia = _atold(configura->Edit1->Text.c_str());       
   def_ecu.Numero_Maximo_Iteraciones = atoi(configura->Edit9->Text.c_str());       
   def_ecu.Numero_Maximo_colores = atoi(configura->Edit10->Text.c_str());       
   ////////////////////////////////////////////////////////
   // Parametro
   ////////////////////////////////////////////////////////
   def_ecu.Posicion.X = _atold(configura->EditPosicionX->Text.c_str());       
   def_ecu.Posicion.Y = _atold(configura->EditPosicionY->Text.c_str());       
   /////////////////////////////////////////////////////////
   // Al terminar
   /////////////////////////////////////////////////////////
   for (int i = 0; i < 16; i++ ) pix[i].Cambia_dimension(Dim_Vtn);
   // Calcula la escala de la ventana de visualizacion
   Escala1.X = (VTJulia->Width -1) / (Dim_Vtn.Xf - Dim_Vtn.Xi);
   Escala1.Y = (VTJulia->Height -1) / (Dim_Vtn.Yf - Dim_Vtn.Yi);
   Calcula_Julia();
}


///////////////////////////////////////////////////////////////////////////////
// Controla el movimiento del mouse y genereación del recuadro para el zoom del
// la ventana de Julia
///////////////////////////////////////////////////////////////////////////////

// Al presionar el botón del mouse
void __fastcall TFormaJulia::VTJuliaMouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (Sw_Recuadro_activo) {
      if (Button == mbLeft) {
         Vt2.Xf = Vt1.Xf = Vt2.Xi = Vt1.Xi = X;
         Vt2.Yf = Vt1.Yf = Vt2.Yi = Vt1.Yi = Y;
         Sw_Dibuja_rectangulo = true;
         Sw_Dibuja_rectangulo_ant = false;
         Ventana_seleccionada = false;
      }
   }
}


// Al mover el mouse
void __fastcall TFormaJulia::VTJuliaMouseMove(TObject *Sender,TShiftState Shift, int X, int Y)
{
   if (Sw_Recuadro_activo) {
      if (Sw_Dibuja_rectangulo) {
         TPenMode mode;

         mode = VTJulia->Canvas->Pen->Mode;
         VTJulia->Canvas->Pen->Mode = pmNot;
      
         if (Sw_Dibuja_rectangulo_ant) {
            VTJulia->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
            VTJulia->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
            VTJulia->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
            VTJulia->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
            VTJulia->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
            VTJulia->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
            VTJulia->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
            VTJulia->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
         }
         VTJulia->Canvas->MoveTo(Vt1.Xi,Vt1.Yi);
         VTJulia->Canvas->LineTo(X,Vt1.Yi);
         VTJulia->Canvas->MoveTo(Vt1.Xi,Vt1.Yi);
         VTJulia->Canvas->LineTo(Vt1.Xi,Y);
         VTJulia->Canvas->MoveTo(X,Y);
         VTJulia->Canvas->LineTo(Vt1.Xi,Y);
         VTJulia->Canvas->MoveTo(X,Y);
         VTJulia->Canvas->LineTo(X,Vt1.Yi);
      
         Vt2.Xf = X;
         Vt2.Yf = Y;
         VTJulia->Canvas->Pen->Mode = mode;
         Sw_Dibuja_rectangulo_ant = true;

         // Ajusta a que xVt tenga el inicio y el final de la ventana
         xVt.Xi = Vt1.Xi, xVt.Xf = Vt2.Xf, xVt.Yi = Vt1.Yi, xVt.Yf = Vt2.Yf;
         int  xtmp;
         if (xVt.Xi > xVt.Xf) xtmp = xVt.Xi, xVt.Xi = xVt.Xf, xVt.Xf = xtmp;
         if (xVt.Yi > xVt.Yf) xtmp = xVt.Yi, xVt.Yi = xVt.Yf, xVt.Yf = xtmp;
         // Ajusta los valores a la longitud de la ventana
         if (xVt.Xi < 0) xVt.Xi = 0;
         if (xVt.Yi < 0) xVt.Yi = 0;
         if (xVt.Xf > VTJulia->Width) xVt.Xf = VTJulia->Width;
         if (xVt.Yf > VTJulia->Height) xVt.Yf = VTJulia->Height;
         // Visualiza los valores de la region seleccionada segun la dimención de la ventana
         Vs.Xi = xVt.Xi / Escala1.X + Dim_Vtn.Xi;
         Vs.Yi = (-(xVt.Yi - VTJulia->Height) / Escala1.Y) + Dim_Vtn.Yi;
         Vs.Xf = xVt.Xf / Escala1.X + Dim_Vtn.Xi;
         Vs.Yf = (-(xVt.Yf - VTJulia->Height) / Escala1.Y) + Dim_Vtn.Yi;
         sprintf(xcad,"%s: (%3.5Lf, %3.5Lf, %3.5Lf, %3.5Lf)",VGJ_TXT01,Vs.Xi,Vs.Yf,Vs.Xf,Vs.Yi);
         BarraDeEstadosJuliaSet->SimpleText = (AnsiString) xcad;
      } else {
         Vs.Xf = X, Vs.Yf = Y;
         Vs.Xi = Vs.Xf / Escala1.X + Dim_Vtn.Xi;
         Vs.Yi = (-(Vs.Yf - VTJulia->Height) / Escala1.Y) + Dim_Vtn.Yi;

         sprintf(Msg,"Mouse position: (%3.8Lf, %3.8Lf)", Vs.Xi, Vs.Yi);
         BarraDeEstadosJuliaSet->SimpleText = (AnsiString) Msg;
      }    
   }
}

// Al soltar el botón del mouse
void __fastcall TFormaJulia::VTJuliaMouseUp(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (Sw_Recuadro_activo) {
      if (Button == mbLeft) {
         TPenMode mode;
         mode = VTJulia->Canvas->Pen->Mode;
         VTJulia->Canvas->Pen->Mode = pmNot;
         VTJulia->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
         VTJulia->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
         VTJulia->Canvas->MoveTo(Vt2.Xi,Vt2.Yi);
         VTJulia->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
         VTJulia->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
         VTJulia->Canvas->LineTo(Vt2.Xi,Vt2.Yf);
         VTJulia->Canvas->MoveTo(Vt2.Xf,Vt2.Yf);
         VTJulia->Canvas->LineTo(Vt2.Xf,Vt2.Yi);
         VTJulia->Canvas->Pen->Mode = mode;
         Vt1.Xf = X;
         Vt1.Xf = Y;
         Sw_Dibuja_rectangulo = false;
         Sw_Dibuja_rectangulo_ant = false;
         BarraDeEstadosJuliaSet->SimpleText = (AnsiString) " ";
         Ventana_seleccionada = true;
         // Revisa si realmente se solicito el zoom
         if (abs(Vt2.Xf - Vt2.Xi) > 5 && abs(Vt2.Yf - Vt2.Yi) > 5) {
            // Pregunta si se desea hacer el zoom
            if (MessageBox(Handle,"Do you wish to zoom?",NOMBRE_VENTANAJULIA,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
               // Almacena las dimensiones actuales
               Dim_zoom[Ind_zoom] = Dim_Vtn;
               if ((Ind_zoom + 1) < NUM_MAX_DIM_ZOOM) Ind_zoom ++;
               MenuVentanaZoomOut->Enabled = true;
               long double incx = fabsl(Vs.Xf - Vs.Xi);
               long double incy = fabsl(Vs.Yf - Vs.Yi);
               long double inc  = (incx > incy ? incx : incy);
               // Actualiza las dimensiones de las ventanas de trabajo
               Dim_Vtn.Xi = Vs.Xi;
               Dim_Vtn.Yi = Vs.Yf;
               Dim_Vtn.Xf = Vs.Xi + inc;
               Dim_Vtn.Yf = Vs.Yf + inc;
               for (int i = 0; i < 16; i++) pix[i].Cambia_dimension(Dim_Vtn);
               // Calcula la escala de la ventana de visualizacion
               Escala1.X = (VTJulia->Width -1) / (Dim_Vtn.Xf - Dim_Vtn.Xi);
               Escala1.Y = (VTJulia->Height -1) / (Dim_Vtn.Yf - Dim_Vtn.Yi);
               Calcula_Julia();
            }
         }
      }
   }
}


// Al solicitar repintar la forma
void __fastcall TFormaJulia::VTJuliaPaint(TObject *Sender)
{
   Grafica();        
}






