
class MenuMain
{
    function this()
    {
        this._root         = $(.menu-main);
        this._btn_settings = $(.menu-main .button-settings);
        this._btn_exit     = $(.menu-main .button-exit);
        this._btn_cancel   = $(.menu-main .button-cancel);

        this._btn_cancel  .on( "click", :{ self.mmenu_main.Visible = false; self.mmain.PauseOnHUD(false); } );
        this._btn_settings.on( "click", :{ self.mmain.OnMainMenu_Settings(); } );
        this._btn_exit    .on( "click", :{ self.mmain.ExitApp(); } );
    }

    function Toggle(){ this.Visible = !this.Visible; }

    property Visible(v)
    {
        get{ return this._root.attributes.hasClass("visible"); }
        set
        {
            this._root.attributes.toggleClass("visible", v);

            if(v)
            {
                var (x1,y1,x2,y2) = this._root.box( #rect, #inner, #view );
                self.mmain.CursorPos( x1+10, y1+10 );
            }
        }

    } // property Visible

} // class MenuMain
