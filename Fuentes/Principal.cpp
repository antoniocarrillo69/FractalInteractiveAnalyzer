// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  55-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <Printers.hpp>
#include <vcl\Registry.hpp>
#include "Acecade.h"
#include "Ayuda.h"
#include "DefinicionEcuacion.hpp"
#pragma hdrstop

#include "Principal.h"
#include "VentanaMandelbrot.h"
#include "VentanaJulia.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVentanaPrincipal *VentanaPrincipal;

bool Configura_escenario = false;
bool Calculo_escenario   = false;
bool Detener_calculo     = false;
bool Limpia_ventana      = false;
bool Zoom_out            = false;
void *Ventana_activa     = NULL;
char TituloAplicacion[300];
C2D Posicion;
//---------------------------------------------------------------------------


__fastcall TVentanaPrincipal::TVentanaPrincipal(TComponent* Owner) : TForm(Owner)
{
   Caption = "Fractals Interactive Analyzer 1.0";
   Application->Title = Caption;

   TRegistry &regkey = * new TRegistry();
   bool keygood = regkey.OpenKey("Laboratorio de Dinamica no Lineal\\Fractals Interactive Analyzer 1.0",false);
   int top = 30, left = 30;
   if (keygood) {
      top = regkey.ReadInteger("Top");
      left = regkey.ReadInteger("Left");
   }
   Top = top, Left = left;
   
   try {
      Application->Icon->LoadFromFile("FRACTAL.ICO");
   } catch (...) {};
   // Tiempo maximo de muestra de Hits
   Application->HintHidePause = 10000;
   Posicion.X = 0.0;
   Posicion.Y = 0.0;
}

// Al crear la forma ...
void __fastcall TVentanaPrincipal::FormCreate(TObject *Sender)
{
   // Asigna la rutina de visualizacion de la barra de estado
   Application->OnHint = &OnHint;
}

// Controla la visualizacion de Hint en la barra de estado
void __fastcall TVentanaPrincipal::OnHint(TObject *Sender)
{
   BarraEstadoPrincipal->SimpleText = Application->Hint;
}

// Controla la solicitud de cerrar la forma
void __fastcall TVentanaPrincipal::FormCloseQuery(TObject *Sender,bool &CanClose)
{
   // Graba la configuracion de la ventana
   TRegistry &regkey = * new TRegistry();
   bool keygood = regkey.OpenKey("Laboratorio de Dinamica no Lineal\\Fractals Interactive Analyzer 1.0",true);
   if (keygood) {
      regkey.WriteInteger("Top", Top);
      regkey.WriteInteger("Left", Left);
   }

   CanClose = false;
   if (MessageBox(Handle,"Do you wish to end the program?",TituloAplicacion,MB_YESNO + MB_ICONQUESTION)  == IDYES) {
      CanClose = true;
   }
}


// MenuPrincipal->Archivo->Salir
void __fastcall TVentanaPrincipal::MenuFileExitClick(TObject *Sender)
{
   Close();     
}

// Acerca de ...
void __fastcall TVentanaPrincipal::MenuHelpAboutOfClick(TObject *Sender)
{
   TVAcercaDe *Acercade = new TVAcercaDe(this);
   if (Acercade) {
      Acercade->ShowModal();
      delete Acercade;
   }
}

// Ayuda General
void __fastcall TVentanaPrincipal::MenuHelpGeneralClick(TObject *Sender)
{
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo("General help","General.hlp");
      Ayuda->ShowModal();
      delete Ayuda;
   }
}

// Icono de ventana de Mandelbrot
void __fastcall TVentanaPrincipal::IconoMandelbrutClick(TObject *Sender)
{
   TFormaMandelbrot *vent_man = new TFormaMandelbrot(this);
   if(vent_man) {
      vent_man->Show();
   }
}

// Icono de ventana de Julia
void __fastcall TVentanaPrincipal::IconoJuliaClick(TObject *Sender)
{
   TFormaJulia *vent_jul = new TFormaJulia(this);
   if(vent_jul) {
      vent_jul->Show();
   }
}

// Icono de configurar escenario
void __fastcall TVentanaPrincipal::IconoAccionConfigurarEscenarioClick(TObject *Sender)
{
   Configura_escenario = true;
}

// Icono de calcular escenario
void __fastcall TVentanaPrincipal::IconoAccionCalcularClick(TObject *Sender)
{
   Calculo_escenario   = true;
}

// Icono de detener calculo
void __fastcall TVentanaPrincipal::IconoAccionDetenerCalculoClick(TObject *Sender)
{
   Detener_calculo     = true;
}

// Icono de limpiar ventana
void __fastcall TVentanaPrincipal::IconoAccionEraseScenaryWindowClick(TObject *Sender)
{
   Limpia_ventana      = true;
}

// Icono de zoom out
void __fastcall TVentanaPrincipal::IconoAccionZoomOutClick(TObject *Sender)
{
   Zoom_out            = true;        
}

void __fastcall TVentanaPrincipal::ManuFilePrintFileClick(TObject *Sender)
{
   OpenPictureDialog->Title = "Load File ...";
   if (OpenPictureDialog->Execute()) {
      Graphics::TBitmap *Bitmap = new Graphics::TBitmap;
      Bitmap->LoadFromFile(OpenPictureDialog->FileName);
      Printer()->BeginDoc();
      Printer()->Canvas->TextOut(100,100,Application->Title);
      Printer()->Canvas->StretchDraw(Rect(100,200,Printer()->PageWidth-100,Printer()->PageWidth-200),Bitmap);
      Printer()->Canvas->TextOut(100,(Printer()->PageWidth - 100),"Antonio Carrillo Ledesma, Facultad de Ciencias, UNAM");
      Printer()->Canvas->TextOut(100,(Printer()->PageWidth - 10),"E-mail: acl@hp.fciencias.unam.mx");
      Printer()->EndDoc();
      delete Bitmap;
   }
}

