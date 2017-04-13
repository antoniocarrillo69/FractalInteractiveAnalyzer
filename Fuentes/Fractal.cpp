// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  55-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Fractal.res");
USEFORM("Principal.cpp", VentanaPrincipal);
USEFORM("Ayuda.cpp", AyudaForm);
USEFORM("Acecade.cpp", VAcercaDe);
USEFORM("VentanaMandelbrot.cpp", FormaMandelbrot);
USEFORM("ParamMandelbrot.cpp", VCap_Mandelbrot);
USEUNIT("DefiniciónEcuación.cpp");
USEFORM("ParamJulia.cpp", VCap_Julia);
USEFORM("VentanaJulia.cpp", FormaJulia);
USEFORM("SelectEcuacion.cpp", FormSeleccionEcuacion);
USEUNIT("..\Libreria\V_pixel.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TVentanaPrincipal), &VentanaPrincipal);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
