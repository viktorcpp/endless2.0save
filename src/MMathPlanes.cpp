
namespace endless
{
    namespace MMath
    {
        __forceinline float PlaneDot(const D3DXPLANE* p, const D3DXVECTOR4* v)
        {
            return D3DXPlaneDot(p, v);
        }

		__forceinline float PlaneDotCoord(const D3DXPLANE* p, const D3DXVECTOR3* v)
        {
            return D3DXPlaneDotCoord(p, v);
        }

		__forceinline float PlaneDotNormal(const D3DXPLANE* p, const D3DXVECTOR3* v)
        {
            return D3DXPlaneDotNormal(p, v);
        }

		__forceinline D3DXPLANE* PlaneScale(D3DXPLANE* out, const D3DXPLANE* p, float s)
        {
            return D3DXPlaneScale(out, p, s);
        }

		__forceinline D3DXPLANE* PlaneNormalize(D3DXPLANE* pout, const D3DXPLANE* pp)
        {
            D3DXPLANE out;
			float norm;

			norm = sqrt(pp->a * pp->a + pp->b * pp->b + pp->c * pp->c);
			if ( norm )
			{
				out.a = pp->a / norm;
				out.b = pp->b / norm;
				out.c = pp->c / norm;
				out.d = pp->d / norm;
			}
			else
			{
				out.a = 0.0f;
				out.b = 0.0f;
				out.c = 0.0f;
				out.d = 0.0f;
			}
			*pout = out;
			
			return pout;
        }

		__forceinline D3DXVECTOR3* PlaneIntersectLine(D3DXVECTOR3* pout, const D3DXPLANE* pp, const D3DXVECTOR3* pv1, const D3DXVECTOR3* pv2)
        {
            D3DXVECTOR3 direction, normal;
			float dot, temp;

			normal.x = pp->a;
			normal.y = pp->b;
			normal.z = pp->c;
			direction.x = pv2->x - pv1->x;
			direction.y = pv2->y - pv1->y;
			direction.z = pv2->z - pv1->z;
			dot = Vec3Dot(&normal, &direction);
			if ( !dot ) return NULL;
			temp = ( pp->d + Vec3Dot(&normal, pv1) ) / dot;
			pout->x = pv1->x - temp * direction.x;
			pout->y = pv1->y - temp * direction.y;
			pout->z = pv1->z - temp * direction.z;
			
			return pout;
        }

		__forceinline D3DXPLANE* PlaneFromPointNormal(D3DXPLANE* pout, const D3DXVECTOR3* pvpoint, const D3DXVECTOR3* pvnormal)
        {
            pout->a = pvnormal->x;
			pout->b = pvnormal->y;
			pout->c = pvnormal->z;
			pout->d = -Vec3Dot(pvpoint, pvnormal);
			
			return pout;
        }

		__forceinline D3DXPLANE* PlaneFromPoints(D3DXPLANE* pout, const D3DXVECTOR3* pv1, const D3DXVECTOR3* pv2, const D3DXVECTOR3* pv3)
        {
            D3DXVECTOR3 edge1, edge2, normal, Nnormal;

			edge1.x = 0.0f; edge1.y = 0.0f; edge1.z = 0.0f;
			edge2.x = 0.0f; edge2.y = 0.0f; edge2.z = 0.0f;
			
			Vec3Subtract(&edge1, pv2, pv1);
			Vec3Subtract(&edge2, pv3, pv1);
			Vec3Cross(&normal, &edge1, &edge2);
			Vec3Normalize(&Nnormal, &normal);
			PlaneFromPointNormal(pout, pv1, &Nnormal);
			
			return pout;
        }

		__forceinline D3DXPLANE* PlaneTransform(D3DXPLANE* pout, const D3DXPLANE* pplane, const D3DXMATRIX* pm)
        {
            const D3DXPLANE plane = *pplane;
			
			pout->a = pm->m[0][0] * plane.a + pm->m[1][0] * plane.b + pm->m[2][0] * plane.c + pm->m[3][0] * plane.d;
			pout->b = pm->m[0][1] * plane.a + pm->m[1][1] * plane.b + pm->m[2][1] * plane.c + pm->m[3][1] * plane.d;
			pout->c = pm->m[0][2] * plane.a + pm->m[1][2] * plane.b + pm->m[2][2] * plane.c + pm->m[3][2] * plane.d;
			pout->d = pm->m[0][3] * plane.a + pm->m[1][3] * plane.b + pm->m[2][3] * plane.c + pm->m[3][3] * plane.d;
			
			return pout;
        }

		__forceinline D3DXPLANE* PlaneTransformArray(D3DXPLANE* out, UINT outstride, const D3DXPLANE* in, UINT instride, const D3DXMATRIX* matrix, UINT elements)
        {
            UINT i;

			for( i = 0; i < elements; ++i )
			{
				PlaneTransform((D3DXPLANE*)((char*)out + outstride * i), (const D3DXPLANE*)((const char*)in + instride * i), matrix);
			}

			return out;
        }

    } // namespace MMath

} // namespace endless
