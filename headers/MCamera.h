#pragma once

namespace endless
{

#define CAM_POS_DEF XMFLOAT3(0.f, 2.f,0.f)

    typedef struct ProjData
    {
        float fov;
        float w;
        float h;
        float znear;
        float zfar;
        float speed_shift;
        float speed_rot_h; // horiz
        float speed_rot_v; // vert

    } PROJDATA;

    class MCamera
    {

    public:

        const XMMATRIX GetMatView();
        const XMMATRIX GetMatProj();

        void Move( float dirvelocity );
        void Strafe( float velocity );
        void RotateAngleX( float angle );
        void RotateAngleY( float angle );
        void RotateAngleZ( float angle );

        void Read();
        void Update();
        void Setup();
        void OnResize(int w, int h);

        const XMFLOAT3 GetAxisX() const;
        const XMFLOAT3 GetAxisY() const;
        const XMFLOAT3 GetAxisZ() const;

        XMFLOAT3* TransformVector( XMFLOAT3* axis );

        MCamera();
        virtual ~MCamera();

    private:

        XMFLOAT3   vec_position;
        XMFLOAT4   quat_orientation;
        XMFLOAT4X4 mat_view;
        bool       req_update;
        PROJDATA   projdata;
        XMFLOAT2   vec_rot_buffer;
        float      angle_counter;

    }; // class MCamera

    /*
        mView(0,0) = mRight.x; 
	    mView(1,0) = mRight.y; 
	    mView(2,0) = mRight.z; 
	    mView(3,0) = x;   

	    mView(0,1) = mUp.x;
	    mView(1,1) = mUp.y;
	    mView(2,1) = mUp.z;
	    mView(3,1) = y;  

	    mView(0,2) = mLook.x; 
	    mView(1,2) = mLook.y; 
	    mView(2,2) = mLook.z; 
	    mView(3,2) = z;   

	    mView(0,3) = 0.0f;
	    mView(1,3) = 0.0f;
	    mView(2,3) = 0.0f;
        mView(3,3) = 1.0f;
    */

} // namespace endless
