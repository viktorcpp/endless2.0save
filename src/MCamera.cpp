
namespace endless
{
    const XMMATRIX MCamera::GetMatView()
    {
        if( req_update )
        {
            Update();
        }

        return XMLoadFloat4x4( &mat_view );

    } // GetMatView

    const XMMATRIX MCamera::GetMatProj()
    {
        return XMMatrixPerspectiveFovLH( projdata.fov, projdata.w/projdata.h, projdata.znear, projdata.zfar );

    } // GetMatProj

    void MCamera::Move( float velocity )
    {
        XMFLOAT3 _vec_direction = GetAxisZ();

        vec_position.x += _vec_direction.x * velocity * projdata.speed_shift;
	    vec_position.y += _vec_direction.y * velocity * projdata.speed_shift;
	    vec_position.z += _vec_direction.z * velocity * projdata.speed_shift;

        req_update = true;

    } // Move

    void MCamera::Strafe( float velocity )
    {
        XMFLOAT3 _vec_direction = GetAxisX();

        vec_position.x += _vec_direction.x * velocity * projdata.speed_shift;
	    vec_position.y += _vec_direction.y * velocity * projdata.speed_shift;
	    vec_position.z += _vec_direction.z * velocity * projdata.speed_shift;

        req_update = true;

    } // Strafe

    void MCamera::RotateAngleX( float angle )
    {
        XMFLOAT4 Rotation;;
        if( angle_counter+angle >= XM_PIDIV2 || angle_counter+angle <= -XM_PIDIV2 )
        {
            req_update = true;
            return;
        }
        angle_counter += angle;
        
		XMStoreFloat4( &Rotation, XMQuaternionRotationAxis( XMLoadFloat3( TransformVector( &XMFLOAT3( 1.0f, 0.0f, 0.0f ) ) ), angle ) );

		XMStoreFloat4( &quat_orientation, XMQuaternionMultiply(XMLoadFloat4( &quat_orientation ), XMLoadFloat4(&Rotation)));

        XMStoreFloat4( &quat_orientation, XMQuaternionNormalize( XMLoadFloat4( &quat_orientation ) ) );

        req_update = true;

    } // RotateAngleX

    void MCamera::RotateAngleY( float angle )
    {
        XMFLOAT4 Rotation;
        
		XMStoreFloat4( &Rotation, XMQuaternionRotationAxis( XMLoadFloat3( &XMFLOAT3( 0.0f, 1.0f, 0.0f ) ), angle ) );

		XMStoreFloat4( &quat_orientation, XMQuaternionMultiply(XMLoadFloat4( &quat_orientation ), XMLoadFloat4(&Rotation)));

        XMStoreFloat4( &quat_orientation, XMQuaternionNormalize( XMLoadFloat4( &quat_orientation ) ) );

        req_update = true;

    } // RotateAngleY

    void MCamera::RotateAngleZ( float angle )
    {
        //
        req_update = true;

    } // RotateAngleZ

    void MCamera::Read()
    {
        bool  is_forward = MCore::GetMInput()->GetKeyDown(KEY_W);
        bool  is_back    = MCore::GetMInput()->GetKeyDown(KEY_S);
        bool  is_left    = MCore::GetMInput()->GetKeyDown(KEY_A);
        bool  is_right   = MCore::GetMInput()->GetKeyDown(KEY_D);
        float m_delta_x  = (float)MCore::GetMInput()->GetMouseDeltaX();
        float m_delta_y  = (float)MCore::GetMInput()->GetMouseDeltaY();
        float time_delta = MCore::GetMTimer()->DeltaTime()*0.001f; // msec
        float velocity   = 0.03f;

        req_update = false;

        if(is_forward)
        {
            Move( time_delta*velocity );
        }
        if(is_back)
        {
            Move( -time_delta*velocity );
        }
        if(is_left)
        {
            Strafe( -time_delta*velocity );
        }
        if(is_right)
        {
            Strafe( time_delta*velocity );
        }
        if( m_delta_x != 0 )
        {
            RotateAngleY( m_delta_x * projdata.speed_rot_h * time_delta );
        }
        if( m_delta_y != 0 )
        {
            RotateAngleX( m_delta_y * projdata.speed_rot_v * time_delta );
        }

    } // Read

    void MCamera::Update()
    {
        if( !req_update ) return;

        XMMATRIX matTranslation = XMMatrixTranslation( -vec_position.x, -vec_position.y, -vec_position.z );

        XMMATRIX matRotation;
	    XMFLOAT4 rotation( -quat_orientation.x, -quat_orientation.y, -quat_orientation.z, quat_orientation.w );

        matRotation = XMMatrixRotationQuaternion( XMLoadFloat4( &rotation ) );

        XMStoreFloat4x4( &mat_view, XMMatrixMultiply( matTranslation, matRotation ) );

        req_update = false;

    } // Update

    void MCamera::Setup()
    {
        //
        req_update = true;

    } // Setup

    void MCamera::OnResize(int w, int h)
    {
        projdata.w = (float)w;
        projdata.h = (float)h;

        req_update = true;

    } // OnResize

    const XMFLOAT3 MCamera::GetAxisX() const
    {	
	    XMFLOAT3 vAxis;

	    vAxis.x = mat_view._11;
	    vAxis.y = mat_view._21;
	    vAxis.z = mat_view._31;

	    return vAxis;
    }

    const XMFLOAT3 MCamera::GetAxisY() const
    {
	    XMFLOAT3 vAxis;

	    vAxis.x = mat_view._12;
	    vAxis.y = mat_view._22;
	    vAxis.z = mat_view._32;

	    return vAxis;
    }

    const XMFLOAT3 MCamera::GetAxisZ() const
    {
	    XMFLOAT3 vAxis;

	    vAxis.x = mat_view._13;
	    vAxis.y = mat_view._23;
	    vAxis.z = mat_view._33;

	    return vAxis;
    }

    XMFLOAT3* MCamera::TransformVector( XMFLOAT3* axis )
    {
	    auto new_axis    = XMVectorSetW( XMLoadFloat3(axis), 1 );
	    auto orientation = XMLoadFloat4( &quat_orientation );
	    new_axis         = XMQuaternionMultiply(XMQuaternionMultiply(XMQuaternionConjugate(orientation), new_axis), orientation);
	
	    XMStoreFloat3(axis, new_axis);

	    return axis;

    } // TransformVector

    MCamera::MCamera()
    {
        projdata.fov         = MUtils::FOVDegreeToRadian( CFG.render_fov );
        projdata.w           = CFG.window_w;
        projdata.h           = CFG.window_h;
        projdata.znear       = CFG.render_znear;
        projdata.zfar        = CFG.render_zfar;
        projdata.speed_shift = 0.25f;
        projdata.speed_rot_h = CFG.render_cam_rot_speed * 0.0001f;
        projdata.speed_rot_v = projdata.speed_rot_h * ( projdata.h/projdata.w );

        vec_position  = CAM_POS_DEF;
        angle_counter = 0;

        XMStoreFloat4  ( &quat_orientation, XMQuaternionIdentity() );
	    XMStoreFloat4x4( &mat_view, XMMatrixIdentity() );

        Update();

        req_update = true;

    } // MCamera

    MCamera::~MCamera(){}

} // namespace endless
