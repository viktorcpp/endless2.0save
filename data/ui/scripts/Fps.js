
class Fps
{
    function this()
    {
        this._root_el = $(.fps);
    }

    function Value( str )
    {
        this._root_el.text = str;
    }

    this var _root_el = null;

} // class Fps
