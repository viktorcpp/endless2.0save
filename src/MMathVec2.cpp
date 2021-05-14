
namespace endless
{
    namespace MMath
    {
        __forceinline D3DXVECTOR2* Vec2BaryCentric(D3DXVECTOR2* pout, CONST D3DXVECTOR2* pv1, CONST D3DXVECTOR2* pv2, CONST D3DXVECTOR2* pv3, FLOAT f, FLOAT g)
        {
            pout->x = (1.0f-f-g) * (pv1->x) + f * (pv2->x) + g * (pv3->x);
			pout->y = (1.0f-f-g) * (pv1->y) + f * (pv2->y) + g * (pv3->y);
			
			return pout;
        }

		__forceinline D3DXVECTOR2* Vec2CatmullRom(D3DXVECTOR2* pout, CONST D3DXVECTOR2* pv0, CONST D3DXVECTOR2* pv1, CONST D3DXVECTOR2* pv2, CONST D3DXVECTOR2* pv3, FLOAT s)
        {
            pout->x = 0.5f * (2.0f * pv1->x + (pv2->x - pv0->x) *s + (2.0f *pv0->x - 5.0f * pv1->x + 4.0f * pv2->x - pv3->x) * s * s + (pv3->x -3.0f * pv2->x + 3.0f * pv1->x - pv0->x) * s * s * s);
			pout->y = 0.5f * (2.0f * pv1->y + (pv2->y - pv0->y) *s + (2.0f *pv0->y - 5.0f * pv1->y + 4.0f * pv2->y - pv3->y) * s * s + (pv3->y -3.0f * pv2->y + 3.0f * pv1->y - pv0->y) * s * s * s);
			
			return pout;
        }

		__forceinline D3DXVECTOR2* Vec2Hermite(D3DXVECTOR2* pout, CONST D3DXVECTOR2* pv1, CONST D3DXVECTOR2* pt1, CONST D3DXVECTOR2* pv2, CONST D3DXVECTOR2* pt2, FLOAT s)
        {
            FLOAT h1, h2, h3, h4;

			h1 = 2.0f * s * s * s - 3.0f * s * s + 1.0f;
			h2 = s * s * s - 2.0f * s * s + s;
			h3 = -2.0f * s * s * s + 3.0f * s * s;
			h4 = s * s * s - s * s;

			pout->x = h1 * (pv1->x) + h2 * (pt1->x) + h3 * (pv2->x) + h4 * (pt2->x);
			pout->y = h1 * (pv1->y) + h2 * (pt1->y) + h3 * (pv2->y) + h4 * (pt2->y);
			
			return pout;
        }

		__forceinline D3DXVECTOR2* Vec2Normalize(D3DXVECTOR2* pout, CONST D3DXVECTOR2* pv)
        {
            D3DXVECTOR2 out;
			FLOAT       norm;

			norm = Vec2Length(pv);
			if ( !norm )
			{
				out.x = 0.0f;
				out.y = 0.0f;
			}
			else
			{
				out.x = pv->x / norm;
				out.y = pv->y / norm;
			}
			*pout = out;

			return pout;
        }

		__forceinline D3DXVECTOR4* Vec2Transform(D3DXVECTOR4* pout, CONST D3DXVECTOR2* pv, CONST D3DXMATRIX* pm)
        {
            pout->x = pm->m[0][0] * pv->x + pm->m[1][0] * pv->y  + pm->m[3][0];
			pout->y = pm->m[0][1] * pv->x + pm->m[1][1] * pv->y  + pm->m[3][1];
			pout->z = pm->m[0][2] * pv->x + pm->m[1][2] * pv->y  + pm->m[3][2];
			pout->w = pm->m[0][3] * pv->x + pm->m[1][3] * pv->y  + pm->m[3][3];
			
			return pout;
        }

		__forceinline D3DXVECTOR4* Vec2TransformArray(D3DXVECTOR4* out, UINT outstride, CONST D3DXVECTOR2* in, UINT instride, CONST D3DXMATRIX* matrix, UINT elements)
        {
            UINT i;

			for(i = 0; i < elements; ++i)
			{
				Vec2Transform((D3DXVECTOR4*)((char*)out + outstride * i), (CONST D3DXVECTOR2*)((const char*)in + instride * i), matrix);
			}

			return out;
        }

		__forceinline D3DXVECTOR2* Vec2TransformCoord(D3DXVECTOR2* pout, CONST D3DXVECTOR2* pv, CONST D3DXMATRIX* pm)
        {
            D3DXVECTOR2 v;
			FLOAT       norm;

			v    = *pv;
			norm = pm->m[0][3] * pv->x + pm->m[1][3] * pv->y + pm->m[3][3];

			pout->x = (pm->m[0][0] * v.x + pm->m[1][0] * v.y + pm->m[3][0]) / norm;
			pout->y = (pm->m[0][1] * v.x + pm->m[1][1] * v.y + pm->m[3][1]) / norm;

			return pout;
        }

		__forceinline D3DXVECTOR2* Vec2TransformCoordArray(D3DXVECTOR2* out, UINT outstride, CONST D3DXVECTOR2* in, UINT instride, CONST D3DXMATRIX* matrix, UINT elements)
        {
            UINT i;

			for( i = 0; i < elements; ++i )
			{
				Vec2TransformCoord((D3DXVECTOR2*)((char*)out + outstride * i), (CONST D3DXVECTOR2*)((const char*)in + instride * i), matrix);
			}

			return out;
        }

		__forceinline D3DXVECTOR2* Vec2TransformNormal(D3DXVECTOR2* pout, CONST D3DXVECTOR2* pv, CONST D3DXMATRIX* pm)
        {
            CONST D3DXVECTOR2 v = *pv;
			
			pout->x = pm->m[0][0] * v.x + pm->m[1][0] * v.y;
			pout->y = pm->m[0][1] * v.x + pm->m[1][1] * v.y;
			
			return pout;
        }

		__forceinline D3DXVECTOR2* Vec2TransformNormalArray(D3DXVECTOR2* out, UINT outstride, CONST D3DXVECTOR2* in, UINT instride, CONST D3DXMATRIX* matrix, UINT elements)
        {
            UINT i;

			for( i = 0; i < elements; ++i )
			{
				Vec2TransformNormal((D3DXVECTOR2*)((char*)out + outstride * i), (CONST D3DXVECTOR2*)((const char*)in + instride * i), matrix);
			}
			return out;
        }

		__forceinline float Vec2Length(const D3DXVECTOR2* v)
        {
            return sqrt(v->x*v->x + v->y*v->y);
        }

		__forceinline float Vec2LengthSq(const D3DXVECTOR2* v)
        {
            return v->x*v->x + v->y*v->y;
        }

		__forceinline float Vec2Dot(const D3DXVECTOR2* v1, const D3DXVECTOR2* v2)
        {
            return v1->x*v2->x + v1->y*v2->y;
        }

		__forceinline float Vec2CCW(const D3DXVECTOR2* v1, const D3DXVECTOR2* v2)
        {
            return D3DXVec2CCW(v1, v2);
        }

		__forceinline D3DXVECTOR2* Vec2Add(D3DXVECTOR2* out, const D3DXVECTOR2* v1, const D3DXVECTOR2* v2)
        {
            return D3DXVec2Add(out, v1, v2);
        }

		__forceinline D3DXVECTOR2* Vec2Subtract(D3DXVECTOR2* out, const D3DXVECTOR2* v1, const D3DXVECTOR2* v2)
        {
            return D3DXVec2Subtract(out, v1, v2);
        }

		__forceinline D3DXVECTOR2* Vec2Minimize(D3DXVECTOR2* out, const D3DXVECTOR2* v1, const D3DXVECTOR2* v2)
        {
            return D3DXVec2Minimize(out, v1, v2);
        }

		__forceinline D3DXVECTOR2* Vec2Maximize(D3DXVECTOR2* out, const D3DXVECTOR2* v1, const D3DXVECTOR2* v2)
        {
            return D3DXVec2Maximize(out, v1, v2);
        }

		__forceinline D3DXVECTOR2* Vec2Scale(D3DXVECTOR2* out, const D3DXVECTOR2* v, float s)
        {
            return D3DXVec2Scale(out, v, s);
        }

		__forceinline D3DXVECTOR2* Vec2Lerp(D3DXVECTOR2* out, const D3DXVECTOR2* v1, const D3DXVECTOR2* v2, float s)
        {
            return D3DXVec2Lerp(out, v1, v2, s);
        }

    } // namespace MMath

} // namespace endless
