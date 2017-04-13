// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef AyudaH
#define AyudaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
class TAyudaForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *Archivo1;
        TMenuItem *Salir1;
        TMenuItem *Edicin1;
        TMenuItem *Copiar1;
        TMenuItem *Seleccionartodo1;
        TMenuItem *N1;
        TMenuItem *Configurarimpresora1;
        TMenuItem *imprimir1;
        TPrintDialog *PrintDialog;
        TRichEdit *EditorAyuda;
        TFindDialog *FindDialog;
        TMenuItem *N2;
        TMenuItem *Buscar1;
        void __fastcall Configurarimpresora1Click(TObject *Sender);
        void __fastcall Salir1Click(TObject *Sender);
        void __fastcall Copiar1Click(TObject *Sender);
        void __fastcall Seleccionartodo1Click(TObject *Sender);
        void __fastcall imprimir1Click(TObject *Sender);
        void __fastcall Buscar1Click(TObject *Sender);
        void __fastcall FindDialogFind(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAyudaForm(TComponent* Owner);


        char *ARCHIVO;
        char *TITULO;

              // Abre el archivo por omision
        void  Abrir_archivo(char *tit, char *arch);
};
#endif
