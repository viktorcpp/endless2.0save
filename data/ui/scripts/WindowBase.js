
class WindowBase
{
    function this(window)
    {
        var _loop        = {};
        _loop._window    = this._window    = window;
        _loop._btn_close = this._btn_close = window.$(.title .btn-close);

        this._window   ._loop = _loop;
        this._btn_close._loop = _loop;

        this._btn_close.on( "mouseup", |{ this.OnBtnClose(); } );
    }

    function OnBtnClose()
    {
        this._window.attributes.removeClass("visible");

    } // OnBtnClose

} // class WindowBase
