
class MenuCharacter
{
    function this()
    {
        this._root = $(.menu-character);
    }

    function Toggle(){ this.Visible = !this.Visible; }

    property Visible(v)
    {
        get{ return this._root.attributes.hasClass("visible") }
        set{ this._root.attributes.toggleClass( "visible", v ); }
    }

} // class MenuCharacter
