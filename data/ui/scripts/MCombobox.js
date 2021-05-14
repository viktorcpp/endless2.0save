
class MCombobox
{
    function this()
    {
        var _cbox_list = $$(.mcombobox);

        for( var x = 0; x < _cbox_list.length; x++ )
        {
            var _el_curr    = _cbox_list[x];
            var _loop       = {};
            _loop.mcombobox = this;
            _loop.cont      = _el_curr;
            _loop.title     = _el_curr.$(.title);
            _loop.body      = _el_curr.$(.body);

            _loop.cont ._loop = _loop;
            _loop.title._loop = _loop;
            _loop.body ._loop = _loop;

            _loop.title.on( "click", this.OnTitle );

            var _items_list = _loop.body.$$(.item);

            for( var y = 0; y < _items_list.length; y++ )
            {
                var _item       = _items_list[y];
                    _item._loop = _loop;
                _item.on( "click", this.OnItem );
            }
        }

    } // this()

    function OnTitle(event)
    {
        var _loop = this._loop;
        _loop.cont.attributes.toggleClass("opened");

    } // OnTitle

    function OnItem()
    {
        var _loop = this.parent._loop;
        _loop.title.text = this.text;
        _loop.cont.attributes.removeClass("opened");

    } // OnItem

} // class MCombobox
