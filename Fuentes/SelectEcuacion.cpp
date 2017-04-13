//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SelectEcuacion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSeleccionEcuacion *FormSeleccionEcuacion;
//---------------------------------------------------------------------------
__fastcall TFormSeleccionEcuacion::TFormSeleccionEcuacion(TComponent* Owner) : TForm(Owner)
{
   Aceptar = false;
}

void __fastcall TFormSeleccionEcuacion::Button1Click(TObject *Sender)
{
   Aceptar = true;
   Close();        
}

