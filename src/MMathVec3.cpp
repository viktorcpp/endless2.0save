
namespace endless
{
    namespace MMath
    {
        __forceinline float Vec3Length(const D3DXVECTOR3* v)
        {
            return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
        }

		__forceinline float Vec3LengthSq(const D3DXVECTOR3* v)
        {
            return v->x*v->x + v->y*v->y + v->z*v->z;
        }

		__forceinline float Vec3Dot(const D3DXVECTOR3* v1, const D3DXVECTOR3* v2)
        {
            return D3DXVec3Dot(v1, v2);
        }

		__forceinline D3DXVECTOR3* Vec3Cross(D3DXVECTOR3* out, const D3DXVECTOR3* v1, const D3DXVECTOR3* v2)
        {
            out->x = v1->y*v2->z - v1->z*v2->y;
			out->y = v1->z*v2->x - v1->x*v2->z;
			out->z = v1->x*v2->y - v1->y*v2->x;
			return out;
        }

		__forceinline D3DXVECTOR3* Vec3Add(D3DXVECTOR3* out, const D3DXVECTOR3* v1, const D3DXVECTOR3* v2)
        {
            return D3DXVec3Add(out, v1, v2);
        }

		__forceinline D3DXVECTOR3* Vec3Subtract(D3DXVECTOR3* out, const D3DXVECTOR3* v1, const D3DXVECTOR3* v2)
        {
            out->x = v1->y*v2->z - v1->z*v2->y;
			out->y = v1->z*v2->x - v1->x*v2->z;
			out->z = v1->x*v2->y - v1->y*v2->x;
			return out;
        }

		__forceinline D3DXVECTOR3* Vec3Minimize(D3DXVECTOR3* out, const D3DXVECTOR3* v1, const D3DXVECTOR3* v2)
        {
            return D3DXVec3Minimize(out, v1, v2);
        }

		__forceinline D3DXVECTOR3* Vec3Maximize(D3DXVECTOR3* out, const D3DXVECTOR3* v1, const D3DXVECTOR3* v2)
        {
            return D3DXVec3Maximize(out, v1, v2);
        }

		__forceinline D3DXVECTOR3* Vec3Scale(D3DXVECTOR3* out, const D3DXVECTOR3* v, float s)
        {
            return D3DXVec3Scale(out, v, s);
        }

		__forceinline D3DXVECTOR3* Vec3Lerp(D3DXVECTOR3* out, const D3DXVECTOR3* v1, const D3DXVECTOR3* v2, float s)
        {
            return D3DXVec3Lerp(out, v1, v2, s);
        }

		__forceinline D3DXVECTOR3* Vec3Normalize(D3DXVECTOR3* pout, CONST D3DXVECTOR3* pv)
        {
            D3DXVECTOR3 out;
			FLOAT       norm;

			norm = Vec3Length(pv);
			if ( !norm )
			{
				out.x = 0.0f;
				out.y = 0.0f;
				out.z = 0.0f;
			}
			else
			{
				out.x = pv->x / norm;
				out.y = pv->y / norm;
				out.z = pv->z / norm;
			}
			*pout = out;
			
			return pout;
        }

		__forceinline D3DXVECTOR3* Vec3Hermite(D3DXVECTOR3* pout, CONST D3DXVECTOR3* pv1, CONST D3DXVECTOR3* pt1, CONST D3DXVECTOR3* pv2, CONST D3DXVECTOR3* pt2, FLOAT s)
        {
            FLOAT h1, h2, h3, h4;

			h1 = 2.0f * s * s * s - 3.0f * s * s + 1.0f;
			h2 = s * s * s - 2.0f * s * s + s;
			h3 = -2.0f * s * s * s + 3.0f * s * s;
			h4 = s * s * s - s * s;

			pout->x = h1 * (pv1->x) + h2 * (pt1->x) + h3 * (pv2->x) + h4 * (pt2->x);
			pout->y = h1 * (pv1->y) + h2 * (pt1->y) + h3 * (pv2->y) + h4 * (pt2->y);
			pout->z = h1 * (pv1->z) + h2 * (pt1->z) + h3 * (pv2->z) + h4 * (pt2->z);
			
			return pout;
        }

		__forceinline D3DXVECTOR3* Vec3CatmullRom( D3DXVECTOR3* pout, CONST D3DXVECTOR3* pv0, CONST D3DXVECTOR3* pv1, CONST D3DXVECTOR3* pv2, CONST D3DXVECTOR3* pv3, FLOAT s)
        {
            pout->x = 0.5f * (2.0f * pv1->x + (pv2->x - pv0->x) *s + (2.0f *pv0->x - 5.0f * pv1->x + 4.0f * pv2->x - pv3->x) * s * s + (pv3->x -3.0f * pv2->x + 3.0f * pv1->x - pv0->x) * s * s * s);
			pout->y = 0.5f * (2.0f * pv1->y + (pv2->y - pv0->y) *s + (2.0f *pv0->y - 5.0f * pv1->y + 4.0f * pv2->y - pv3->y) * s * s + (pv3->y -3.0f * pv2->y + 3.0f * pv1->y - pv0->y) * s * s * s);
			pout->z = 0.5f * (2.0f * pv1->z + (pv2->z - pv0->z) *s + (2.0f *pv0->z - 5.0f * pv1->z + 4.0f * pv2->z - pv3->z) * s * s + (pv3->z -3.0f * pv2->z + 3.0f * pv1->z - pv0->z) * s * s * s);
			
			return pout;
        }

		__forceinline D3DXVECTOR3* Vec3BaryCentric(D3DXVECTOR3* pout, CONST D3DXVECTOR3* pv1, CONST D3DXVECTOR3* pv2, CONST D3DXVECTOR3* pv3, FLOAT f, FLOAT g)
        {
            pout->x = (1.0f-f-g) * (pv1->x) + f * (pv2->x) + g * (pv3->x);
			pout->y = (1.0f-f-g) * (pv1->y) + f * (pv2->y) + g * (pv3->y);
			pout->z = (1.0f-f-g) * (pv1->z) + f * (pv2->z) + g * (pv3->z);
			
			return pout;
        }

		__forceinline D3DXVECTOR4* Vec3Transform(D3DXVECTOR4* pout, CONST D3DXVECTOR3* pv, CONST D3DXMATRIX* pm)
        {
            pout->x = pm->m[0][0] * pv->x + pm->m[1][0] * pv->y + pm->m[2][0] * pv->z + pm->m[3][0];
			pout->y = pm->m[0][1] * pv->x + pm->m[1][1] * pv->y + pm->m[2][1] * pv->z + pm->m[3][1];
			pout->z = pm->m[0][2] * pv->x + pm->m[1][2] * pv->y + pm->m[2][2] * pv->z + pm->m[3][2];
			pout->w = pm->m[0][3] * pv->x + pm->m[1][3] * pv->y + pm->m[2][3] * pv->z + pm->m[3][3];
			
			return pout;
        }

		__forceinline D3DXVECTOR3* Vec3TransformNormal(D3DXVECTOR3* pout, CONST D3DXVECTOR3* pv, CONST D3DXMATRIX* pm)
        {
            CONST D3DXVECTOR3 v = *pv;
			
			pout->x = pm->m[0][0] * v.x + pm->m[1][0] * v.y + pm->m[2][0] * v.z;
			pout->y = pm->m[0][1] * v.x + pm->m[1][1] * v.y + pm->m[2][1] * v.z;
			pout->z = pm->m[0][2] * v.x + pm->m[1][2] * v.y + pm->m[2][2] * v.z;
			
			return pout;
        }

		__forceinline D3DXVECTOR4* Vec3TransformArray(D3DXVECTOR4* out, UINT outstride, CONST D3DXVECTOR3* in, UINT instride, CONST D3DXMATRIX* matrix, UINT elements)
        {
            UINT i;

			for( i = 0; i < elements; ++i )
			{
				Vec3Transform((D3DXVECTOR4*)((char*)out + outstride * i), (CONST D3DXVECTOR3*)((const char*)in + instride * i), matrix);
			}
			
			return out;
        }

		__forceinline D3DXVECTOR3* Vec3TransformCoord(D3DXVECTOR3* pout, CONST D3DXVECTOR3* pv, CONST D3DXMATRIX* pm)
        {
            D3DXVECTOR3 out;
			FLOAT       norm;

			norm = pm->m[0][3] * pv->x + pm->m[1][3] * pv->y + pm->m[2][3] *pv->z + pm->m[3][3];

			out.x = (pm->m[0][0] * pv->x + pm->m[1][0] * pv->y + pm->m[2][0] * pv->z + pm->m[3][0]) / norm;
			out.y = (pm->m[0][1] * pv->x + pm->m[1][1] * pv->y + pm->m[2][1] * pv->z + pm->m[3][1]) / norm;
			out.z = (pm->m[0][2] * pv->x + pm->m[1][2] * pv->y + pm->m[2][2] * pv->z + pm->m[3][2]) / norm;

			*pout = out;

			return pout;
        }

		__forceinline D3DXVECTOR3* Vec3TransformCoordArray(D3DXVECTOR3* out, UINT outstride, CONST D3DXVECTOR3* in, UINT instride, CONST D3DXMATRIX* matrix, UINT elements)
        {
            UINT i;

			for( i = 0; i < elements; ++i )
			{
				Vec3TransformCoord((D3DXVECTOR3*)((char*)out + outstride * i), (CONST D3DXVECTOR3*)((const char*)in + instride * i), matrix);
			}

			return out;
        }

		__forceinline D3DXVECTOR3* Vec3TransformNormalArray(D3DXVECTOR3* out, UINT outstride, CONST D3DXVECTOR3* in, UINT instride, CONST D3DXMATRIX* matrix, UINT elements)
        {
            UINT i;

			for( i = 0; i < elements; ++i )
			{
				Vec3TransformNormal((D3DXVECTOR3*)((char*)out + outstride * i), (CONST D3DXVECTOR3*)((const char*)in + instride * i), matrix);
			}
			
			return out;
        }

    } // namespace MMath

} // namespace endless
