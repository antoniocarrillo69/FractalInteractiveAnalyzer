// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


#include <vcl\vcl.h>
#include "Acecade.h"
#pragma hdrstop


//---------------------------------------------------------------------------
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TVAcercaDe::TVAcercaDe(TComponent* Owner) : TForm(Owner)
{
   // Nombre de la aplicación
   Label10->Caption = Application->Title;
   // Fecha de generacion de la versión
   FechaGeneracion->Caption = __DATE__;
}
//---------------------------------------------------------------------------



