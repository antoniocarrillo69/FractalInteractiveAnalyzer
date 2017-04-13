// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include <stdlib.h>
#include "Ayuda.h"
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

__fastcall TAyudaForm::TAyudaForm(TComponent* Owner): TForm(Owner)
{
}


// Abre el archivo por omision
void TAyudaForm::Abrir_archivo(char *tit, char *arch)
{
   TITULO = tit;
   ARCHIVO = arch;
   Caption = TITULO;
   EditorAyuda->Clear();
   if(arch[0]) EditorAyuda->Lines->LoadFromFile(ARCHIVO);
}

// Imprime el archivo
void __fastcall TAyudaForm::imprimir1Click(TObject *Sender)
{
   EditorAyuda->Print(TITULO);
}


// Configura la impresora
void __fastcall TAyudaForm::Configurarimpresora1Click(TObject *Sender)
{
   PrintDialog->Execute();    
}

// Salir del programa
void __fastcall TAyudaForm::Salir1Click(TObject *Sender)
{
   Close();        
}

// Copia el texto seleccionado
void __fastcall TAyudaForm::Copiar1Click(TObject *Sender)
{
   EditorAyuda->CopyToClipboard();        
}

// Selecciona todo el texto
void __fastcall TAyudaForm::Seleccionartodo1Click(TObject *Sender)
{
   EditorAyuda->SelectAll();                
}


void __fastcall TAyudaForm::Buscar1Click(TObject *Sender)
{
    FindDialog->FindText = EditorAyuda->SelText;
    FindDialog->Execute();
}


void __fastcall TAyudaForm::FindDialogFind(TObject *Sender)
{
    Show();
    TSearchTypes st;
    TFindDialog *cd;
    int newpos;

    if ((cd = dynamic_cast<TFindDialog *> (Sender)) == 0) MessageBox(NULL, "Error en solicitud de memoria dinámica", "Buscar", MB_OK + MB_ICONSTOP);

    if (cd->Options.Contains(frMatchCase)) st << stMatchCase;
    if (cd->Options.Contains(frWholeWord)) st << stWholeWord;

    if (EditorAyuda->SelLength) EditorAyuda->SelStart += 1;

    newpos = EditorAyuda->FindText(cd->FindText, EditorAyuda->SelStart, EditorAyuda->Text.Length(), st);

    if (newpos != -1) {
        EditorAyuda->SelStart = newpos;
        EditorAyuda->SelLength = cd->FindText.Length();
     } else {
        MessageBox(NULL, "Fin del documento", "Buscar", MB_OK + MB_ICONINFORMATION);
        EditorAyuda->SelStart = 0;
    }
}

