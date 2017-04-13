// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


//---------------------------------------------------------------------------
#ifndef ParamJuliaH
#define ParamJuliaH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Tabnotbk.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Dialogs.hpp>
//---------------------------------------------------------------------------
class TVCap_Julia : public TForm
{
__published:	// IDE-managed Components
   TButton *Button1;
   TColorDialog *ColorDialog;
        TTabbedNotebook *TabbedNotebook1;
        TPanel *Panel1;
        TStaticText *StaticText1;
        TListBox *ListBoxParametros;
        TStaticText *NombreParametro;
        TPanel *Panel2;
        TGroupBox *GroupBox2;
        TLabel *Label6;
        TLabel *Label7;
        TGroupBox *GroupBox1;
        TLabel *Label4;
        TLabel *Label5;
        TEdit *EditHMin;
        TEdit *EditHMax;
        TEdit *EditVMin;
        TEdit *EditVMax;
        TPanel *Panel4;
        TLabel *Label8;
        TEdit *Edit8;
        TEdit *EditValorParametro;
        TLabel *Label1;
        TEdit *Edit9;
        TLabel *Label2;
        TEdit *Edit10;
        TPanel *Panel3;
        TEdit *EditPosicionX;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TEdit *EditPosicionY;
        TLabel *Label3;
        TEdit *Edit1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall ListBoxParametrosClick(TObject *Sender);
        void __fastcall EditValorParametroKeyPress(TObject *Sender,
          char &Key);
private:	// User declarations
public:		// User declarations
        bool Aceptar;

   __fastcall TVCap_Julia(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
 
