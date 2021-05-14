
class MenuConsole
{
    function this()
    {
        this._root   = $(.menu-console);
        this._buffer = $(.menu-console .buffer);
        this._input  = $(.menu-console input);

        this._input.on( "keydown", this.OnKey );
    }

    function LogN( str )
    {
        this._buffer.append("<div class=\"white\">" + str + "</div>");
        this._buffer.scrollTo( 0, 999999 );

    } // LogN

    function LogW( str )
    {
        this._buffer.append("<div class=\"yellow\">" + str + "</div>");
        this._buffer.scrollTo( 0, 999999 );

    } // LogW

    function LogE( str )
    {
        this._buffer.append("<div class=\"red\">" + str + "</div>");
        this._buffer.scrollTo( 0, 999999 );

    } // LogE

    function Toggle(){ this.Visible = !this.Visible; }

    property Visible(v)
    {
        get{ return this._root.attributes.hasClass("visible"); }
        set
        {
            this._root.attributes.toggleClass( "visible", v );
            this._input.state.focus = v;
            this._input.text        = "";

            if( v )
            {
                self.mmain.CursorPos( 5, 5 );
                self.on( "keydown", this.OnKey );
            }
            else
            {
                self.off( "keydown", this.OnKey );
            }
        }
    }

    function OnKey( event )
    {
        if( event.keyCode == Event.VK_RETURN )
        {
            self.mmenu_console.LogN( self.mmenu_console._input.text );
            self.mmenu_console._input.text = "";
            return true;
        }

        return false;

    } // OnKey

} // MenuConsole
