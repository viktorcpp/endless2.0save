
class MDraggable
{
    function this()
    {
        this.screen_size = {};
        var drag_list = $$(.draggable);
        for( var x = 0; x < drag_list.length; x++ )
        {
            var _loop = {};
            _loop._root   = drag_list[x];
            _loop._rec    = null;

            if( _loop._root.attributes.hasClass("receiver") )
            {
                _loop._rec = _loop._root;
            }
            else
            {
                _loop._rec = _loop._root.$(.receiver);
            }
            
            _loop._root._loop = _loop;
            _loop._rec ._loop = _loop;

            _loop._rec.on( "mousedown",  this.DragStart );

        }
    }

    function DragStart(event)
    {
        var _loop = this._loop;

        this.draginfo = {};

        this.draginfo.mouse_x = event.xView;
        this.draginfo.mouse_y = event.yView;
        this.draginfo.pos_x   = this.box( #left, #inner, #view );
        this.draginfo.pos_y   = this.box( #top,  #inner, #view );
        this.draginfo.delta_x = this.draginfo.mouse_x - this.draginfo.pos_x;
        this.draginfo.delta_y = this.draginfo.mouse_y - this.draginfo.pos_y;

        self.dragging = this;
        self.on( "mousemove", self.mdraggable.DragMove );
        self.on( "mouseup",   self.mdraggable.DragEnd  );

        _loop._rec.on( "mouseout", self.mdraggable.DragEnd   );

    } // DragStart

    function DragMove(event)
    {
        if( !self.dragging )
        {
            self.off( "mousemove", self.mdraggable.DragMove );
        }

        var _loop                      = self.dragging._loop;
        var _mouse_x                   = event.xView - self.dragging.draginfo.delta_x;
        var _mouse_y                   = event.yView - self.dragging.draginfo.delta_y;
        var ( _x0, _y0, _x1, _y1 )     = _loop._root.box( #rect, #inner, #view );
        var ( _sx0, _sy0, _sx1, _sy1 ) = view.box( #rect, #inner, #view );
        var _win_w                     = _x1 - _x0;
        var _win_h                     = _y1 - _y0;
        var _max_x                     = (_sx1 - _sx0) - _win_w;
        var _max_y                     = (_sy1 - _sy0) - _win_h;

        _mouse_x = _mouse_x < 0 ? 0 : _mouse_x;
        _mouse_x = _mouse_x > _max_x ? _max_x : _mouse_x;
        _mouse_y = _mouse_y < 0 ? 0 : _mouse_y;
        _mouse_y = _mouse_y > _max_y ? _max_y : _mouse_y;

        _loop._root.move( _mouse_x, _mouse_y, #view );

    } // DragMove

    function DragEnd(event)
    {
        self.off( "mousemove", self.mdraggable.DragMove );
        self.off( "mouseup",   self.mdraggable.DragEnd  );
        self.dragging._loop._rec.off( "mouseout", self.mdraggable.DragEnd   );

        self.dragging.draginfo = null;
        self.dragging          = null;

    } // DragEnd

} // class MDraggable
