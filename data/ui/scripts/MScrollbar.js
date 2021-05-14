
class MScrollbar
{
    function this()
    {
        var _sb_list = $$(.mscrollbar);
        for( var x = 0; x < _sb_list.length; x++ )
        {
            var _sb_curr             = _sb_list[x];
            _sb_curr._loop           = {};
            _sb_curr._loop.sb        = _sb_curr;
            _sb_curr._loop.up        = _sb_curr.$(.up);
            _sb_curr._loop.thumb     = _sb_curr.$(.thumb);
            _sb_curr._loop.down      = _sb_curr.$(.down);
            _sb_curr._loop.container = self.select( _sb_curr.attributes["sb-target"] );
            _sb_curr._loop.content   = _sb_curr._loop.container[0];

            _sb_curr._loop.sb       ._loop = _sb_curr._loop;
            _sb_curr._loop.up       ._loop = _sb_curr._loop;
            _sb_curr._loop.thumb    ._loop = _sb_curr._loop;
            _sb_curr._loop.down     ._loop = _sb_curr._loop;
            _sb_curr._loop.container._loop = _sb_curr._loop;

            _sb_curr._loop.container.on( "mouseenter", this.OnContentMouseEnter );
            _sb_curr._loop.container.on( "mouseleave", this.OnContentMouseLeave );

            _sb_curr._loop.sb.on( "scroll", this.OnSBScrollRouter );

            var ( container_w, container_h ) = GetElSize( _sb_curr._loop.container );
            var ( content_w,   content_h )   = GetElSize( _sb_curr._loop.content );
            var ( sb_w,        sb_h )        = GetElSize( _sb_curr._loop.sb );

            if( content_h < container_h )
            {
                _sb_curr.attributes.removeClass("visible");
            }

            _sb_curr._loop.thumb.style["height"] = ( container_h / (content_h * 1.0) ) * sb_h;
        }
    }

    function OnContentMouseEnter(event)
    {
        var _loop = this._loop;
        var ( container_w, container_h ) = GetElSize( _loop.container );
        var ( content_w,   content_h )   = GetElSize( _loop.content );

        if( content_h < container_h ){ return; } // it is necessary

        this.on( "scroll", self.mscrollbar.OnContentScroll );
        _loop.sb.on( "scroll", self.mscrollbar.OnSBScrollRouter );

        stdout.println( "Entered" );

    } // OnContentMouseEnter

    function OnContentMouseLeave(event)
    {
        var _loop = this._loop;

        this.off( "scroll", self.mscrollbar.OnContentScroll );
        _loop.sb.off( "scroll", self.mscrollbar.OnSBScrollRouter );

        stdout.println( "Leaved" );

    } // OnContentMouseLeave

    function OnContentScroll(event)
    {
        var _loop = this._loop;
        var ( container_w, container_h ) = GetElSize( _loop.container );
        var ( content_w,   content_h )   = GetElSize( _loop.content );
        var ( sb_w,        sb_h )        = GetElSize( _loop.sb );
        var ( sb_up_w,     sb_up_h )     = GetElSize( _loop.up );

        if( content_h < container_h ){ return; } // it is necessary

        var max_scroll      = content_h - container_h;
        var max_scroll_perc = container_h / ((content_h - container_h)*1.0);

        //stdout.println( "Scroll: " + event.scrollPos + "    w="+content_w + "    h="+content_h + "    max="+max_scroll + "    maxp="+max_scroll_perc );
        //stdout.println( event.scrollPos / (content_h*1.0) );

        var _offset = sb_up_h + 1;
        var _top = sb_h * ( event.scrollPos / (content_h*1.0) ) - _offset;
            _top = _top < _offset ? _offset : _top;
        _loop.thumb.style["top"] = _top;

    } // OnContentScroll

    function OnSBScrollRouter(event)
    {
        self.mscrollbar.OnContentScroll(event);

    } // OnSBScrollRouter

    /* (w,h) */
    function GetElSize( el )
    {
        return el.box( #dimension, #inner, #view);

    } // GetElSize

} // class MScrollbar
