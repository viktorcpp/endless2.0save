
class MenuSettings
{
    function this()
    {
        this._root     = $(.menu-settings);
        this._res_list = $(.menu-settings .mcombobox-resolutions);

        this.GeneResList();
    }

    function Toggle(){ this.Visible = !this.Visible; }

    property Visible(v)
    {
        get{ return this._root.attributes.hasClass("visible"); }
        set{ this._root.attributes.toggleClass("visible", v); }

    } // property Visible

    function GeneResList()
    {
        var display_res_list = null;
        try
        {
            display_res_list = JSON.parse( view.HUDAPI_DisplayResList() );
        }
        catch(e)
        {
            UIAPI.LogE( "<pre>" + display_res_list + "</pre>" );
            display_res_list = null;
        }

        if( display_res_list != null )
        {
            var _body = this._res_list.$(.body);
            var _buffer = "";
            for( var x = 0; x < display_res_list.length; x++ )
            {
                var _item = display_res_list[x];
                //_body.append( "<div class=\"item\" w=\"" + _item.w + "\" h=\"" + _item.h + "\">" + _item.str + "</div>" );
                _buffer += "<div class=\"item\" w=\"" + _item.w + "\" h=\"" + _item.h + "\">" + _item.str + "</div>";
            }
            _body.append( _buffer );
        }

    } // GeneResList

} // class MenuSettings
