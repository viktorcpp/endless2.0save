
namespace endless
{
	namespace MMath
	{
		__forceinline D3DXMATRIX* MatrixIdentity( D3DXMATRIX* out )
		{
			*out = mat_identity;
			return out;
		}

		__forceinline bool MatrixIsIdentity( const D3DXMATRIX* m )
        {
            int i, j;
			D3DXMATRIX testmatrix;

			if( !m ) return false;
			MatrixIdentity( &testmatrix );

			for( j = 0; j < 4; j++ )
			{
				if ( (*m).m[i][j] != (testmatrix).m[i][j] ) return false;
			}

			return true;
        }

		__forceinline float MatrixDeterminant(const D3DXMATRIX* pm)
        {
            D3DXVECTOR4 minor, v1, v2, v3;
			float det;

			v1.x = pm->m[0][0]; v1.y = pm->m[1][0]; v1.z = pm->m[2][0]; v1.w = pm->m[3][0];
			v2.x = pm->m[0][1]; v2.y = pm->m[1][1]; v2.z = pm->m[2][1]; v2.w = pm->m[3][1];
			v3.x = pm->m[0][2]; v3.y = pm->m[1][2]; v3.z = pm->m[2][2]; v3.w = pm->m[3][2];
			Vec4Cross(&minor, &v1, &v2, &v3);
			det =  - (pm->m[0][3] * minor.x + pm->m[1][3] * minor.y + pm->m[2][3] * minor.z + pm->m[3][3] * minor.w);

			return det;
        }

		__forceinline HRESULT MatrixDecompose(D3DXVECTOR3* poutscale, D3DXQUATERNION* poutrotation, D3DXVECTOR3* pouttranslation, const D3DXMATRIX* pm)
        {
            D3DXMATRIX normalized;
			D3DXVECTOR3 vec;

			/*Compute the scaling part.*/
			vec.x = pm->m[0][0];
			vec.y = pm->m[0][1];
			vec.z = pm->m[0][2];
			poutscale->x = Vec3Length(&vec);

			vec.x = pm->m[1][0];
			vec.y = pm->m[1][1];
			vec.z = pm->m[1][2];
			poutscale->y = Vec3Length(&vec);

			vec.x = pm->m[2][0];
			vec.y = pm->m[2][1];
			vec.z = pm->m[2][2];
			poutscale->z = Vec3Length(&vec);

			/*Compute the translation part.*/
			pouttranslation->x = pm->m[3][0];
			pouttranslation->y = pm->m[3][1];
			pouttranslation->z = pm->m[3][2];

			/*Let's calculate the rotation now*/
			if ( (poutscale->x == 0.0f) || (poutscale->y == 0.0f) || (poutscale->z == 0.0f) ) return D3DERR_INVALIDCALL;

			normalized.m[0][0] = pm->m[0][0]/poutscale->x;
			normalized.m[0][1] = pm->m[0][1]/poutscale->x;
			normalized.m[0][2] = pm->m[0][2]/poutscale->x;
			normalized.m[1][0] = pm->m[1][0]/poutscale->y;
			normalized.m[1][1] = pm->m[1][1]/poutscale->y;
			normalized.m[1][2] = pm->m[1][2]/poutscale->y;
			normalized.m[2][0] = pm->m[2][0]/poutscale->z;
			normalized.m[2][1] = pm->m[2][1]/poutscale->z;
			normalized.m[2][2] = pm->m[2][2]/poutscale->z;

			QuaternionRotationMatrix(poutrotation, &normalized);

			return S_OK;
        }

		__forceinline D3DXMATRIX* MatrixTranspose(D3DXMATRIX* pout, const D3DXMATRIX* pm)
        {
            const D3DXMATRIX m = *pm;
			int i,j;

			for(i=0; i<4; i++)
				for(j=0; j<4; j++) pout->m[i][j] = m.m[j][i];

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixMultiply(D3DXMATRIX* pout, const D3DXMATRIX* pm1, const D3DXMATRIX* pm2)
        {
            D3DXMATRIX out;
			int i,j;

			for (i=0; i<4; i++)
			{
				for (j=0; j<4; j++)
				{
					out.m[i][j] = pm1->m[i][0] * pm2->m[0][j] + pm1->m[i][1] * pm2->m[1][j] + pm1->m[i][2] * pm2->m[2][j] + pm1->m[i][3] * pm2->m[3][j];
				}
			}

			*pout = out;

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixMultiplyTranspose(D3DXMATRIX* pout, const D3DXMATRIX* pm1, const D3DXMATRIX* pm2)
        {
            MatrixMultiply(pout, pm1, pm2);
			MatrixTranspose(pout, pout);
			return pout;
        }

		__forceinline D3DXMATRIX* MatrixInverse(D3DXMATRIX* pout, float* pdeterminant, const D3DXMATRIX* pm)
        {
            int a, i, j;
			D3DXMATRIX out;
			D3DXVECTOR4 v, vec[3];
			float det;

			det = MatrixDeterminant(pm);
			if ( !det ) return NULL;
			if ( pdeterminant ) *pdeterminant = det;
			for (i=0; i<4; i++)
			{
				for (j=0; j<4; j++)
				{
					if (j != i )
					{
						a = j;
						if ( j > i ) a = a-1;
						vec[a].x = pm->m[j][0];
						vec[a].y = pm->m[j][1];
						vec[a].z = pm->m[j][2];
						vec[a].w = pm->m[j][3];
					}
				}
				Vec4Cross(&v, &vec[0], &vec[1], &vec[2]);
				out.m[0][i] = pow(-1.0f, i) * v.x / det;
				out.m[1][i] = pow(-1.0f, i) * v.y / det;
				out.m[2][i] = pow(-1.0f, i) * v.z / det;
				out.m[3][i] = pow(-1.0f, i) * v.w / det;
			}

			*pout = out;

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixScaling(D3DXMATRIX* pout, float sx, float sy, float sz)
        {
            MatrixIdentity(pout);
			
			pout->m[0][0] = sx;
			pout->m[1][1] = sy;
			pout->m[2][2] = sz;

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixTranslation(D3DXMATRIX* pout, float x, float y, float z)
        {
            MatrixIdentity(pout);

			pout->m[3][0] = x;
			pout->m[3][1] = y;
			pout->m[3][2] = z;

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixRotationX(D3DXMATRIX* pout, float angle)
        {
            MatrixIdentity(pout);

			pout->m[1][1] = cos(angle);
			pout->m[2][2] = cos(angle);
			pout->m[1][2] = sin(angle);
			pout->m[2][1] = -sin(angle);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixRotationY(D3DXMATRIX* pout, float angle)
        {
            MatrixIdentity(pout);
			
			pout->m[0][0] = cos(angle);
			pout->m[2][2] = cos(angle);
			pout->m[0][2] = -sin(angle);
			pout->m[2][0] = sin(angle);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixRotationZ(D3DXMATRIX* pout, float angle)
        {
            MatrixIdentity(pout);
			
			pout->m[0][0] = cos(angle);
			pout->m[1][1] = cos(angle);
			pout->m[0][1] = sin(angle);
			pout->m[1][0] = -sin(angle);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixRotationAxis(D3DXMATRIX* pout, const D3DXVECTOR3* pv, float angle)
        {
            D3DXVECTOR3 v;

			Vec3Normalize(&v,pv);
			MatrixIdentity(pout);

			pout->m[0][0] = (1.0f - cos(angle)) * v.x * v.x + cos(angle);
			pout->m[1][0] = (1.0f - cos(angle)) * v.x * v.y - sin(angle) * v.z;
			pout->m[2][0] = (1.0f - cos(angle)) * v.x * v.z + sin(angle) * v.y;
			pout->m[0][1] = (1.0f - cos(angle)) * v.y * v.x + sin(angle) * v.z;
			pout->m[1][1] = (1.0f - cos(angle)) * v.y * v.y + cos(angle);
			pout->m[2][1] = (1.0f - cos(angle)) * v.y * v.z - sin(angle) * v.x;
			pout->m[0][2] = (1.0f - cos(angle)) * v.z * v.x - sin(angle) * v.y;
			pout->m[1][2] = (1.0f - cos(angle)) * v.z * v.y + sin(angle) * v.x;
			pout->m[2][2] = (1.0f - cos(angle)) * v.z * v.z + cos(angle);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixRotationQuaternion(D3DXMATRIX* pout, const D3DXQUATERNION* pq)
        {
            MatrixIdentity(pout);

			pout->m[0][0] = 1.0f - 2.0f * (pq->y * pq->y + pq->z * pq->z);
			pout->m[0][1] = 2.0f * (pq->x *pq->y + pq->z * pq->w);
			pout->m[0][2] = 2.0f * (pq->x * pq->z - pq->y * pq->w);
			pout->m[1][0] = 2.0f * (pq->x * pq->y - pq->z * pq->w);
			pout->m[1][1] = 1.0f - 2.0f * (pq->x * pq->x + pq->z * pq->z);
			pout->m[1][2] = 2.0f * (pq->y *pq->z + pq->x *pq->w);
			pout->m[2][0] = 2.0f * (pq->x * pq->z + pq->y * pq->w);
			pout->m[2][1] = 2.0f * (pq->y *pq->z - pq->x *pq->w);
			pout->m[2][2] = 1.0f - 2.0f * (pq->x * pq->x + pq->y * pq->y);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixRotationYawPitchRoll(D3DXMATRIX* pout, float yaw, float pitch, float roll)
        {
            D3DXMATRIX m;

			MatrixIdentity(pout);
			MatrixRotationZ(&m, roll);
			MatrixMultiply(pout, pout, &m);
			MatrixRotationX(&m, pitch);
			MatrixMultiply(pout, pout, &m);
			MatrixRotationY(&m, yaw);
			MatrixMultiply(pout, pout, &m);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixTransformation(D3DXMATRIX* pout, const D3DXVECTOR3* pscalingcenter, const D3DXQUATERNION* pscalingrotation, const D3DXVECTOR3* pscaling, const D3DXVECTOR3* protationcenter, const D3DXQUATERNION* protation, const D3DXVECTOR3* ptranslation)
        {
            D3DXMATRIX m1, m2, m3, m4, m5, m6, m7;
			D3DXQUATERNION prc;
			D3DXVECTOR3 psc, pt;

			if ( !pscalingcenter )
			{
				psc.x = 0.0f;
				psc.y = 0.0f;
				psc.z = 0.0f;
			}
			else
			{
				psc.x = pscalingcenter->x;
				psc.y = pscalingcenter->y;
				psc.z = pscalingcenter->z;
			}

			if ( !protationcenter )
			{
				prc.x = 0.0f;
				prc.y = 0.0f;
				prc.z = 0.0f;
			}
			else
			{
				prc.x = protationcenter->x;
				prc.y = protationcenter->y;
				prc.z = protationcenter->z;
			}

			if ( !ptranslation )
			{
				pt.x = 0.0f;
				pt.y = 0.0f;
				pt.z = 0.0f;
			}
			else
			{
				pt.x = ptranslation->x;
				pt.y = ptranslation->y;
				pt.z = ptranslation->z;
			}

			MatrixTranslation(&m1, -psc.x, -psc.y, -psc.z);

			if ( !pscalingrotation )
			{
				MatrixIdentity(&m2);
				MatrixIdentity(&m4);
			}
			else
			{
				MatrixRotationQuaternion(&m4, pscalingrotation);
				MatrixInverse(&m2, NULL, &m4);
			}

			if ( !pscaling ) MatrixIdentity(&m3);
			else MatrixScaling(&m3, pscaling->x, pscaling->y, pscaling->z);

			if ( !protation ) MatrixIdentity(&m6);
			else MatrixRotationQuaternion(&m6, protation);

			MatrixTranslation(&m5, psc.x - prc.x,  psc.y - prc.y,  psc.z - prc.z);
			MatrixTranslation(&m7, prc.x + pt.x, prc.y + pt.y, prc.z + pt.z);
			MatrixMultiply(&m1, &m1, &m2);
			MatrixMultiply(&m1, &m1, &m3);
			MatrixMultiply(&m1, &m1, &m4);
			MatrixMultiply(&m1, &m1, &m5);
			MatrixMultiply(&m1, &m1, &m6);
			MatrixMultiply(pout, &m1, &m7);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixTransformation2D(D3DXMATRIX* pout, const D3DXVECTOR2* pscalingcenter, float scalingrotation, const D3DXVECTOR2* pscaling, const D3DXVECTOR2* protationcenter, float rotation, const D3DXVECTOR2* ptranslation)
        {
            D3DXQUATERNION rot, sca_rot;
			D3DXVECTOR3 rot_center, sca, sca_center, trans;

			if ( pscalingcenter )
			{
				sca_center.x=pscalingcenter->x;
				sca_center.y=pscalingcenter->y;
				sca_center.z=0.0f;
			}
			else
			{
				sca_center.x=0.0f;
				sca_center.y=0.0f;
				sca_center.z=0.0f;
			}

			if ( pscaling )
			{
				sca.x=pscaling->x;
				sca.y=pscaling->y;
				sca.z=1.0f;
			}
			else
			{
				sca.x=1.0f;
				sca.y=1.0f;
				sca.z=1.0f;
			}

			if ( protationcenter )
			{
				rot_center.x=protationcenter->x;
				rot_center.y=protationcenter->y;
				rot_center.z=0.0f;
			}
			else
			{
				rot_center.x=0.0f;
				rot_center.y=0.0f;
				rot_center.z=0.0f;
			}

			if ( ptranslation )
			{
				trans.x=ptranslation->x;
				trans.y=ptranslation->y;
				trans.z=0.0f;
			}
			else
			{
				trans.x=0.0f;
				trans.y=0.0f;
				trans.z=0.0f;
			}

			rot.w=cos(rotation/2.0f);
			rot.x=0.0f;
			rot.y=0.0f;
			rot.z=sin(rotation/2.0f);

			sca_rot.w=cos(scalingrotation/2.0f);
			sca_rot.x=0.0f;
			sca_rot.y=0.0f;
			sca_rot.z=sin(scalingrotation/2.0f);

			MatrixTransformation(pout, &sca_center, &sca_rot, &sca, &rot_center, &rot, &trans);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixAffineTransformation(D3DXMATRIX* pout, float scaling, const D3DXVECTOR3* rotationcenter, const D3DXQUATERNION* rotation, const D3DXVECTOR3* translation)
        {
            D3DXMATRIX m1, m2, m3, m4, m5;

			MatrixScaling(&m1, scaling, scaling, scaling);

			if ( !rotationcenter )
			{
				MatrixIdentity(&m2);
				MatrixIdentity(&m4);
			}
			else
			{
				MatrixTranslation(&m2, -rotationcenter->x, -rotationcenter->y, -rotationcenter->z);
				MatrixTranslation(&m4, rotationcenter->x, rotationcenter->y, rotationcenter->z);
			}

			if ( !rotation ) MatrixIdentity(&m3);
			else MatrixRotationQuaternion(&m3, rotation);

			if ( !translation ) D3DXMatrixIdentity(&m5);
			else MatrixTranslation(&m5, translation->x, translation->y, translation->z);

			MatrixMultiply(&m1, &m1, &m2);
			MatrixMultiply(&m1, &m1, &m3);
			MatrixMultiply(&m1, &m1, &m4);
			MatrixMultiply(pout, &m1, &m5);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixAffineTransformation2D(D3DXMATRIX* pout, float scaling, const D3DXVECTOR2* protationcenter, float rotation, const D3DXVECTOR2* ptranslation)
        {
            D3DXMATRIX m1, m2, m3, m4, m5;
			D3DXQUATERNION rot;
			D3DXVECTOR3 rot_center, trans;

			rot.w=cos(rotation/2.0f);
			rot.x=0.0f;
			rot.y=0.0f;
			rot.z=sin(rotation/2.0f);

			if ( protationcenter )
			{
				rot_center.x=protationcenter->x;
				rot_center.y=protationcenter->y;
				rot_center.z=0.0f;
			}
			else
			{
				rot_center.x=0.0f;
				rot_center.y=0.0f;
				rot_center.z=0.0f;
			}

			if ( ptranslation )
			{
				trans.x=ptranslation->x;
				trans.y=ptranslation->y;
				trans.z=0.0f;
			}
			else
			{
				trans.x=0.0f;
				trans.y=0.0f;
				trans.z=0.0f;
			}

			MatrixScaling(&m1, scaling, scaling, 1.0f);
			MatrixTranslation(&m2, -rot_center.x, -rot_center.y, -rot_center.z);
			MatrixTranslation(&m4, rot_center.x, rot_center.y, rot_center.z);
			MatrixRotationQuaternion(&m3, &rot);
			MatrixTranslation(&m5, trans.x, trans.y, trans.z);

			MatrixMultiply(&m1, &m1, &m2);
			MatrixMultiply(&m1, &m1, &m3);
			MatrixMultiply(&m1, &m1, &m4);
			MatrixMultiply(pout, &m1, &m5);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixLookAtRH(D3DXMATRIX* pout, const D3DXVECTOR3* peye, const D3DXVECTOR3* pat, const D3DXVECTOR3* pup)
        {
            D3DXVECTOR3 right, rightn, up, upn, vec, vec2;

			Vec3Subtract(&vec2, pat, peye);
			Vec3Normalize(&vec, &vec2);
			Vec3Cross(&right, pup, &vec);
			Vec3Cross(&up, &vec, &right);
			Vec3Normalize(&rightn, &right);
			Vec3Normalize(&upn, &up);

			pout->m[0][0] = -rightn.x;
			pout->m[1][0] = -rightn.y;
			pout->m[2][0] = -rightn.z;
			pout->m[3][0] = Vec3Dot(&rightn,peye);

			pout->m[0][1] = upn.x;
			pout->m[1][1] = upn.y;
			pout->m[2][1] = upn.z;
			pout->m[3][1] = -Vec3Dot(&upn, peye);

			pout->m[0][2] = -vec.x;
			pout->m[1][2] = -vec.y;
			pout->m[2][2] = -vec.z;
			pout->m[3][2] = D3DXVec3Dot(&vec, peye);

			pout->m[0][3] = 0.0f;
			pout->m[1][3] = 0.0f;
			pout->m[2][3] = 0.0f;
			pout->m[3][3] = 1.0f;

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixLookAtLH(D3DXMATRIX* pout, D3DXVECTOR3* peye, D3DXVECTOR3* pat, D3DXVECTOR3* pup, D3DXVECTOR3* right)
        {
            // не удалять!!!
			D3DXVec3Normalize(pat, pat );
			D3DXVec3Cross    (pup, pat, right);
			D3DXVec3Normalize(pup, pup );
			D3DXVec3Cross    (right, pup, pat );
			D3DXVec3Normalize(right, right );

			float x = -D3DXVec3Dot(right, peye);
			float y = -D3DXVec3Dot(pup,   peye);
			float z = -D3DXVec3Dot(pat,  peye);

			(*pout)(0,0) = right->x; (*pout)(0, 1) = pup->x; (*pout)(0, 2) = pat->x; (*pout)(0, 3) = 0.0f;
			(*pout)(1,0) = right->y; (*pout)(1, 1) = pup->y; (*pout)(1, 2) = pat->y; (*pout)(1, 3) = 0.0f;
			(*pout)(2,0) = right->z; (*pout)(2, 1) = pup->z; (*pout)(2, 2) = pat->z; (*pout)(2, 3) = 0.0f;
			(*pout)(3,0) = x;        (*pout)(3, 1) = y;     (*pout)(3, 2) = z;       (*pout)(3, 3) = 1.0f;
			return pout;

			/*D3DXVECTOR3 right, rightn, up, upn, vec, vec2;

			_Vec3Subtract(&vec2, pat, peye);
			_Vec3Normalize(&vec, &vec2);
			_Vec3Cross(&right, pup, &vec);
			_Vec3Cross(&up, &vec, &right);
			_Vec3Normalize(&rightn, &right);
			_Vec3Normalize(&upn, &up);
			pout->m[0][0] = rightn.x;
			pout->m[1][0] = rightn.y;
			pout->m[2][0] = rightn.z;
			pout->m[3][0] = -_Vec3Dot(&rightn,peye);
			pout->m[0][1] = upn.x;
			pout->m[1][1] = upn.y;
			pout->m[2][1] = upn.z;
			pout->m[3][1] = -_Vec3Dot(&upn, peye);
			pout->m[0][2] = vec.x;
			pout->m[1][2] = vec.y;
			pout->m[2][2] = vec.z;
			pout->m[3][2] = -_Vec3Dot(&vec, peye);
			pout->m[0][3] = 0.0f;
			pout->m[1][3] = 0.0f;
			pout->m[2][3] = 0.0f;
			pout->m[3][3] = 1.0f;

			return pout; */
        }

		__forceinline D3DXMATRIX* MatrixPerspectiveRH(D3DXMATRIX* pout, float w, float h, float zn, float zf)
        {
            MatrixIdentity(pout);

			pout->m[0][0] = 2.0f * zn / w;
			pout->m[1][1] = 2.0f * zn / h;
			pout->m[2][2] = zf / (zn - zf);
			pout->m[3][2] = (zn * zf) / (zn - zf);
			pout->m[2][3] = -1.0f;
			pout->m[3][3] = 0.0f;

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixPerspectiveLH(D3DXMATRIX* pout, float w, float h, float zn, float zf)
        {
            MatrixIdentity(pout);

			pout->m[0][0] = 2.0f * zn / w;
			pout->m[1][1] = 2.0f * zn / h;
			pout->m[2][2] = zf / (zf - zn);
			pout->m[3][2] = (zn * zf) / (zn - zf);
			pout->m[2][3] = 1.0f;
			pout->m[3][3] = 0.0f;
			
			return pout;
        }

		__forceinline D3DXMATRIX* MatrixPerspectiveFovRH(D3DXMATRIX* pout, float fovy, float aspect, float zn, float zf)
        {
            MatrixIdentity(pout);

			pout->m[0][0] = 1.0f / (aspect * tan(fovy/2.0f));
			pout->m[1][1] = 1.0f / tan(fovy/2.0f);
			pout->m[2][2] = zf / (zn - zf);
			pout->m[2][3] = -1.0f;
			pout->m[3][2] = (zf * zn) / (zn - zf);
			pout->m[3][3] = 0.0f;
			
			return pout;
        }

		__forceinline D3DXMATRIX* MatrixPerspectiveFovLH(D3DXMATRIX* pout, float fovy, float aspect, float zn, float zf)
        {
            MatrixIdentity(pout);

			pout->m[0][0] = 1.0f / (aspect * tan(fovy/2.0f));
			pout->m[1][1] = 1.0f / tan(fovy/2.0f);
			pout->m[2][2] = zf / (zf - zn);
			pout->m[2][3] = 1.0f;
			pout->m[3][2] = (zf * zn) / (zn - zf);
			pout->m[3][3] = 0.0f;

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixPerspectiveOffCenterRH(D3DXMATRIX* pout, float l, float r, float b, float t, float zn, float zf)
        {
            MatrixIdentity(pout);

			pout->m[0][0] = 2.0f * zn / (r - l);
			pout->m[1][1] = -2.0f * zn / (b - t);
			pout->m[2][0] = 1.0f + 2.0f * l / (r - l);
			pout->m[2][1] = -1.0f -2.0f * t / (b - t);
			pout->m[2][2] = zf / (zn - zf);
			pout->m[3][2] = (zn * zf) / (zn -zf);
			pout->m[2][3] = -1.0f;
			pout->m[3][3] = 0.0f;

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixPerspectiveOffCenterLH(D3DXMATRIX* pout, float l, float r, float b, float t, float zn, float zf)
        {
            MatrixIdentity(pout);

			pout->m[0][0] = 2.0f * zn / (r - l);
			pout->m[1][1] = -2.0f * zn / (b - t);
			pout->m[2][0] = -1.0f - 2.0f * l / (r - l);
			pout->m[2][1] = 1.0f + 2.0f * t / (b - t);
			pout->m[2][2] = - zf / (zn - zf);
			pout->m[3][2] = (zn * zf) / (zn -zf);
			pout->m[2][3] = 1.0f;
			pout->m[3][3] = 0.0f;

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixOrthoRH(D3DXMATRIX* pout, float w, float h, float zn, float zf)
        {
            MatrixIdentity(pout);

			pout->m[0][0] = 2.0f / w;
			pout->m[1][1] = 2.0f / h;
			pout->m[2][2] = 1.0f / (zn - zf);
			pout->m[3][2] = zn / (zn - zf);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixOrthoLH(D3DXMATRIX* pout, float w, float h, float zn, float zf)
        {
            MatrixIdentity(pout);

			pout->m[0][0] = 2.0f / w;
			pout->m[1][1] = 2.0f / h;
			pout->m[2][2] = 1.0f / (zf - zn);
			pout->m[3][2] = zn / (zn - zf);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixOrthoOffCenterRH(D3DXMATRIX* pout, float l, float r, float b, float t, float zn, float zf)
        {
            MatrixIdentity(pout);

			pout->m[0][0] = 2.0f / (r - l);
			pout->m[1][1] = 2.0f / (t - b);
			pout->m[2][2] = 1.0f / (zn -zf);
			pout->m[3][0] = -1.0f -2.0f *l / (r - l);
			pout->m[3][1] = 1.0f + 2.0f * t / (b - t);
			pout->m[3][2] = zn / (zn -zf);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixOrthoOffCenterLH(D3DXMATRIX* pout, float l, float r, float b, float t, float zn, float zf)
        {
            MatrixIdentity(pout);

			pout->m[0][0] = 2.0f / (r - l);
			pout->m[1][1] = 2.0f / (t - b);
			pout->m[2][2] = 1.0f / (zf -zn);
			pout->m[3][0] = -1.0f -2.0f *l / (r - l);
			pout->m[3][1] = 1.0f + 2.0f * t / (b - t);
			pout->m[3][2] = zn / (zn -zf);

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixShadow(D3DXMATRIX* pout, const D3DXVECTOR4* plight, const D3DXPLANE* pplane)
        {
            D3DXPLANE Nplane;
			float dot;

			PlaneNormalize(&Nplane, pplane);

			dot = PlaneDot(&Nplane, plight);

			pout->m[0][0] = dot - Nplane.a * plight->x;
			pout->m[0][1] = -Nplane.a * plight->y;
			pout->m[0][2] = -Nplane.a * plight->z;
			pout->m[0][3] = -Nplane.a * plight->w;
			pout->m[1][0] = -Nplane.b * plight->x;
			pout->m[1][1] = dot - Nplane.b * plight->y;
			pout->m[1][2] = -Nplane.b * plight->z;
			pout->m[1][3] = -Nplane.b * plight->w;
			pout->m[2][0] = -Nplane.c * plight->x;
			pout->m[2][1] = -Nplane.c * plight->y;
			pout->m[2][2] = dot - Nplane.c * plight->z;
			pout->m[2][3] = -Nplane.c * plight->w;
			pout->m[3][0] = -Nplane.d * plight->x;
			pout->m[3][1] = -Nplane.d * plight->y;
			pout->m[3][2] = -Nplane.d * plight->z;
			pout->m[3][3] = dot - Nplane.d * plight->w;

			return pout;
        }

		__forceinline D3DXMATRIX* MatrixReflect(D3DXMATRIX* pout, const D3DXPLANE* pplane)
        {
            D3DXPLANE Nplane;

			PlaneNormalize(&Nplane, pplane);
			MatrixIdentity(pout);

			pout->m[0][0] = 1.0f - 2.0f * Nplane.a * Nplane.a;
			pout->m[0][1] = -2.0f * Nplane.a * Nplane.b;
			pout->m[0][2] = -2.0f * Nplane.a * Nplane.c;
			pout->m[1][0] = -2.0f * Nplane.a * Nplane.b;
			pout->m[1][1] = 1.0f - 2.0f * Nplane.b * Nplane.b;
			pout->m[1][2] = -2.0f * Nplane.b * Nplane.c;
			pout->m[2][0] = -2.0f * Nplane.c * Nplane.a;
			pout->m[2][1] = -2.0f * Nplane.c * Nplane.b;
			pout->m[2][2] = 1.0f - 2.0f * Nplane.c * Nplane.c;
			pout->m[3][0] = -2.0f * Nplane.d * Nplane.a;
			pout->m[3][1] = -2.0f * Nplane.d * Nplane.b;
			pout->m[3][2] = -2.0f * Nplane.d * Nplane.c;

			return pout;
        }

	} // namespace MMath

} // namespace endless
