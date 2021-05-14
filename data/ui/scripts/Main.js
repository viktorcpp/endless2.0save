
class Main
{
    function this()
    {
        this._root           = $(#hud-main);

        self.mmenu_main      = new MenuMain();
        self.mmenu_console   = new MenuConsole();
        self.mmenu_settings  = new MenuSettings();
        self.mmenu_character = new MenuCharacter();
        self.fps             = new Fps();
        self.mcombobox       = new MCombobox();
        self.mdraggable      = new MDraggable();
        self.mscrollbar      = new MScrollbar();
        self.menudialog      = new MenuDialog();

        self.on( "keydown", this.OnKey );
        view.on( "size",    this.OnResize );

        this.UpdateCursor();

    } // constructor

    function CursorVis ( vis )  { try{ view.HUDAPI_CursorVis( vis );    } catch(e){} }
    function CursorClip( clip ) { try{ view.HUDAPI_CursorClip( clip );  } catch(e){} }
    function CursorPos ( x, y ) { try{ view.HUDAPI_CursorPos( x, y );   } catch(e){} }
    function ExitApp   ()       { try{ view.HUDAPI_OnBtnExit();         } catch(e){} }
    function PauseOnHUD( pause ){ try{ view.HUDAPI_PauseOnHUD( pause ); } catch(e){} }

    function OnMainMenu_Settings()
    {
        self.mmenu_main    .Visible = false;
        self.mmenu_settings.Visible = true;

    } // OnMainMenu_Settings

    function OnKey( event )
    {
        if( event.keyCode == Event.VK_ESCAPE )
        {
            if( self.mmenu_console.Visible )
            {
                self.mmenu_console.Visible = false;
            }
            else if( self.mmenu_settings.Visible )
            {
                self.mmenu_settings.Visible = false;
                self.mmenu_main.Visible = true;
            }
            else if( self.mmenu_character.Visible )
            {
                self.mmenu_character.Visible = false;
            }
            else
            {
                self.mmenu_main.Toggle();
            }
        }

        if( event.keyCode == Event.VK_I )
        {
            if( self.mmenu_main.Visible || self.mmenu_settings.Visible || self.mmenu_console.Visible )
            {
                // empty
            }
            else
            {
                self.mmenu_character.Toggle();
            }
        }

        if( event.keyCode == 0xC0 ) // `tilde
        {
            self.mmenu_console.Toggle();
        }

        self.mmain.UpdateCursor();

        return false;

    } // OnKey

    function UpdateCursor()
    {
        var vis = self.mmenu_main.Visible || 
                  self.mmenu_settings.Visible || 
                  self.mmenu_console.Visible || 
                  self.mmenu_character.Visible;

        this.CursorVis(vis);
        this.CursorClip(!vis);
        this.PauseOnHUD( vis );

    } // UpdateCursor

    function OnResize()
    {
        var (w,h) = this.box(#dimension);
        
    } // OnResize

} // class Main
