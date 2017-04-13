// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  55-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


//---------------------------------------------------------------------------
#ifndef PrincipalH
#define PrincipalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TVentanaPrincipal : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *BarraEstadoPrincipal;
        TMainMenu *Menu;
        TMenuItem *MenuFile;
        TMenuItem *MenuFileExit;
        TMenuItem *MenuHelp;
        TPanel *Panel1;
        TPanel *Panel2;
        TMenuItem *Separador1;
        TMenuItem *MenuHelpAboutOf;
        TMenuItem *MenuHelpGeneral;
        TSpeedButton *IconoMandelbrut;
        TSpeedButton *IconoJulia;
        TMenuItem *Separador2;
        TMenuItem *MenuFilePrintSetup;
        TMenuItem *MenuScenery;
        TMenuItem *MenuSceneryMandelbrot;
        TMenuItem *MenuSceneryJulia;
        TMenuItem *MenuCalculate;
        TSpeedButton *IconoAccionConfigurarEscenario;
        TSpeedButton *IconoAccionCalcular;
        TSpeedButton *IconoAccionDetenerCalculo;
        TSpeedButton *IconoAccionEraseScenaryWindow;
        TMenuItem *MenuCalculateScenary;
        TMenuItem *Windows1;
        TMenuItem *MenuWindowsEraseScenery;
        TSpeedButton *IconoAccionZoomOut;
        TMenuItem *MenuWindowZoomOut;
        TMenuItem *N1;
        TMenuItem *MenuCalculateStopCalculate;
        TOpenPictureDialog *OpenPictureDialog;
        TMenuItem *ManuFilePrintFile;
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall MenuFileExitClick(TObject *Sender);
        void __fastcall MenuHelpAboutOfClick(TObject *Sender);
        void __fastcall MenuHelpGeneralClick(TObject *Sender);
        void __fastcall IconoMandelbrutClick(TObject *Sender);
        void __fastcall IconoJuliaClick(TObject *Sender);
        void __fastcall IconoAccionConfigurarEscenarioClick(
          TObject *Sender);
        void __fastcall IconoAccionCalcularClick(TObject *Sender);
        void __fastcall IconoAccionDetenerCalculoClick(TObject *Sender);
        void __fastcall IconoAccionEraseScenaryWindowClick(TObject *Sender);
        void __fastcall IconoAccionZoomOutClick(TObject *Sender);
        void __fastcall ManuFilePrintFileClick(TObject *Sender);
private:	// User declarations
        // Controla la visualizacion de Hint en la barra de estado
        void __fastcall OnHint(TObject *Sender);
public:		// User declarations
        __fastcall TVentanaPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TVentanaPrincipal *VentanaPrincipal;
//---------------------------------------------------------------------------
#endif
