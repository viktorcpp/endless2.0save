
namespace endless
{
    namespace MMath
    {
        __forceinline float Vec4Length( const D3DXVECTOR4* v )
        {
            return sqrt(v->x*v->x + v->y*v->y + v->z*v->z + v->w*v->w);
        }

		__forceinline float Vec4LengthSq( const D3DXVECTOR4* v )
        {
            return v->x*v->x + v->y*v->y + v->z*v->z + v->w*v->w;
        }

		__forceinline float Vec4Dot(const D3DXVECTOR4* v1, const D3DXVECTOR4* v2)
        {
            return D3DXVec4Dot(v1, v2);
        }

		__forceinline D3DXVECTOR4* Vec4Add(D3DXVECTOR4* out, const D3DXVECTOR4* v1, const D3DXVECTOR4* v2)
        {
            return D3DXVec4Add(out, v1, v2);
        }

		__forceinline D3DXVECTOR4* Vec4Subtract(D3DXVECTOR4* out, const D3DXVECTOR4* v1, const D3DXVECTOR4* v2)
        {
            return D3DXVec4Subtract(out, v1, v2);
        }

		__forceinline D3DXVECTOR4* Vec4Minimize(D3DXVECTOR4* out, const D3DXVECTOR4* v1, const D3DXVECTOR4* v2)
        {
            return D3DXVec4Minimize(out, v1, v2);
        }

		__forceinline D3DXVECTOR4* Vec4Maximize(D3DXVECTOR4* out, const D3DXVECTOR4* v1, const D3DXVECTOR4* v2)
        {
            return D3DXVec4Maximize(out, v1, v2);
        }

		__forceinline D3DXVECTOR4* Vec4Scale(D3DXVECTOR4* out, const D3DXVECTOR4* v, float s)
        {
            return D3DXVec4Scale(out, v, s);
        }

		__forceinline D3DXVECTOR4* Vec4Lerp(D3DXVECTOR4* out, const D3DXVECTOR4* v1, const D3DXVECTOR4* v2, float s)
        {
            return D3DXVec4Lerp(out, v1, v2, s);
        }

		__forceinline D3DXVECTOR4* Vec4Cross(D3DXVECTOR4* pout, CONST D3DXVECTOR4* pv1, CONST D3DXVECTOR4* pv2, CONST D3DXVECTOR4* pv3)
        {
            D3DXVECTOR4 out;
			
			out.x = pv1->y * (pv2->z * pv3->w - pv3->z * pv2->w) - pv1->z * (pv2->y * pv3->w - pv3->y * pv2->w) + pv1->w * (pv2->y * pv3->z - pv2->z *pv3->y);
			out.y = -(pv1->x * (pv2->z * pv3->w - pv3->z * pv2->w) - pv1->z * (pv2->x * pv3->w - pv3->x * pv2->w) + pv1->w * (pv2->x * pv3->z - pv3->x * pv2->z));
			out.z = pv1->x * (pv2->y * pv3->w - pv3->y * pv2->w) - pv1->y * (pv2->x *pv3->w - pv3->x * pv2->w) + pv1->w * (pv2->x * pv3->y - pv3->x * pv2->y);
			out.w = -(pv1->x * (pv2->y * pv3->z - pv3->y * pv2->z) - pv1->y * (pv2->x * pv3->z - pv3->x *pv2->z) + pv1->z * (pv2->x * pv3->y - pv3->x * pv2->y));
			*pout = out;
			
			return pout;
        }

		__forceinline D3DXVECTOR4* Vec4Normalize(D3DXVECTOR4* pout, CONST D3DXVECTOR4* pv)
        {
            D3DXVECTOR4 out;
			FLOAT norm;

			norm = Vec4Length(pv);

			out.x = pv->x / norm;
			out.y = pv->y / norm;
			out.z = pv->z / norm;
			out.w = pv->w / norm;

			*pout = out;
			return pout;
        }

		__forceinline D3DXVECTOR4* Vec4Hermite(D3DXVECTOR4* pout, CONST D3DXVECTOR4* pv1, CONST D3DXVECTOR4* pt1, CONST D3DXVECTOR4* pv2, CONST D3DXVECTOR4* pt2, FLOAT s)
        {
            FLOAT h1, h2, h3, h4;

			h1 = 2.0f * s * s * s - 3.0f * s * s + 1.0f;
			h2 = s * s * s - 2.0f * s * s + s;
			h3 = -2.0f * s * s * s + 3.0f * s * s;
			h4 = s * s * s - s * s;

			pout->x = h1 * (pv1->x) + h2 * (pt1->x) + h3 * (pv2->x) + h4 * (pt2->x);
			pout->y = h1 * (pv1->y) + h2 * (pt1->y) + h3 * (pv2->y) + h4 * (pt2->y);
			pout->z = h1 * (pv1->z) + h2 * (pt1->z) + h3 * (pv2->z) + h4 * (pt2->z);
			pout->w = h1 * (pv1->w) + h2 * (pt1->w) + h3 * (pv2->w) + h4 * (pt2->w);
			
			return pout;
        }

		__forceinline D3DXVECTOR4* Vec4CatmullRom(D3DXVECTOR4* pout, CONST D3DXVECTOR4* pv0, CONST D3DXVECTOR4* pv1, CONST D3DXVECTOR4* pv2, CONST D3DXVECTOR4* pv3, FLOAT s)
        {
            pout->x = 0.5f * (2.0f * pv1->x + (pv2->x - pv0->x) *s + (2.0f *pv0->x - 5.0f * pv1->x + 4.0f * pv2->x - pv3->x) * s * s + (pv3->x -3.0f * pv2->x + 3.0f * pv1->x - pv0->x) * s * s * s);
			pout->y = 0.5f * (2.0f * pv1->y + (pv2->y - pv0->y) *s + (2.0f *pv0->y - 5.0f * pv1->y + 4.0f * pv2->y - pv3->y) * s * s + (pv3->y -3.0f * pv2->y + 3.0f * pv1->y - pv0->y) * s * s * s);
			pout->z = 0.5f * (2.0f * pv1->z + (pv2->z - pv0->z) *s + (2.0f *pv0->z - 5.0f * pv1->z + 4.0f * pv2->z - pv3->z) * s * s + (pv3->z -3.0f * pv2->z + 3.0f * pv1->z - pv0->z) * s * s * s);
			pout->w = 0.5f * (2.0f * pv1->w + (pv2->w - pv0->w) *s + (2.0f *pv0->w - 5.0f * pv1->w + 4.0f * pv2->w - pv3->w) * s * s + (pv3->w -3.0f * pv2->w + 3.0f * pv1->w - pv0->w) * s * s * s);
			
			return pout;
        }

		__forceinline D3DXVECTOR4* Vec4BaryCentric(D3DXVECTOR4* pout, CONST D3DXVECTOR4* pv1, CONST D3DXVECTOR4* pv2, CONST D3DXVECTOR4* pv3, FLOAT f, FLOAT g)
        {
            pout->x = (1.0f-f-g) * (pv1->x) + f * (pv2->x) + g * (pv3->x);
			pout->y = (1.0f-f-g) * (pv1->y) + f * (pv2->y) + g * (pv3->y);
			pout->z = (1.0f-f-g) * (pv1->z) + f * (pv2->z) + g * (pv3->z);
			pout->w = (1.0f-f-g) * (pv1->w) + f * (pv2->w) + g * (pv3->w);
			
			return pout;
        }

		__forceinline D3DXVECTOR4* Vec4Transform(D3DXVECTOR4* pout, CONST D3DXVECTOR4* pv, CONST D3DXMATRIX* pm)
        {
            D3DXVECTOR4 out;
			
			out.x = pm->m[0][0] * pv->x + pm->m[1][0] * pv->y + pm->m[2][0] * pv->z + pm->m[3][0] * pv->w;
			out.y = pm->m[0][1] * pv->x + pm->m[1][1] * pv->y + pm->m[2][1] * pv->z + pm->m[3][1] * pv->w;
			out.z = pm->m[0][2] * pv->x + pm->m[1][2] * pv->y + pm->m[2][2] * pv->z + pm->m[3][2] * pv->w;
			out.w = pm->m[0][3] * pv->x + pm->m[1][3] * pv->y + pm->m[2][3] * pv->z + pm->m[3][3] * pv->w;
			*pout = out;
			
			return pout;
        }

		__forceinline D3DXVECTOR4* Vec4TransformArray(D3DXVECTOR4* out, UINT outstride, CONST D3DXVECTOR4* in, UINT instride, CONST D3DXMATRIX* matrix, UINT elements)
        {
            UINT i;

			for( i = 0; i < elements; ++i )
			{
				Vec4Transform((D3DXVECTOR4*)((char*)out + outstride * i), (CONST D3DXVECTOR4*)((const char*)in + instride * i), matrix);
			}

			return out;
        }

    } // namespace MMath

} // namespace endless
