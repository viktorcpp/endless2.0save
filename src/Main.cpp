
#include <includes.h>

int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
    //SCITER+
    // Sciter needs it for Drag-n-drop, etc.
    OleInitialize(NULL);
    //SCITER-

    using namespace endless;
    try
    {
        std::shared_ptr<MCore> core( new MCore() );
        core->Module(hPrevInstance);
        core->Setup();
        core->Run();
        
    }
    catch( std::exception exc )
    {
        MUtils::alert( exc.what() );
    }

} // WinMain
