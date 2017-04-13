//---------------------------------------------------------------------------
#ifndef SelectEcuacionH
#define SelectEcuacionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormSeleccionEcuacion : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TButton *Button1;
        TStaticText *StaticText2;
        TComboBox *ComboBoxSeleccionEcuacion;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormSeleccionEcuacion(TComponent* Owner);
        bool       Aceptar;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSeleccionEcuacion *FormSeleccionEcuacion;
//---------------------------------------------------------------------------
#endif
