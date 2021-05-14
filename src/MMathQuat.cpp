
namespace endless
{
    namespace MMath
    {
		__forceinline float QuaternionLength(const D3DXQUATERNION* q)
        {
            return D3DXQuaternionLength(q);
        }

		__forceinline float QuaternionLengthSq(const D3DXQUATERNION* q)
        {
            return D3DXQuaternionLengthSq(q);
        }

		__forceinline float QuaternionDot(const D3DXQUATERNION* q1, const D3DXQUATERNION* q2)
        {
            return D3DXQuaternionDot(q1, q2);
        }

		__forceinline D3DXQUATERNION* QuaternionIdentity(D3DXQUATERNION* q)
        {
            return D3DXQuaternionIdentity(q);
        }

		__forceinline bool QuaternionIsIdentity(const D3DXQUATERNION* q)
        {
            return D3DXQuaternionIsIdentity(q) == 1 ? true : false;
        }

		__forceinline D3DXQUATERNION* QuaternionConjugate(D3DXQUATERNION* out, const D3DXQUATERNION* q)
        {
            return D3DXQuaternionConjugate(out, q);
        }

		__forceinline void QuaternionToAxisAngle(const D3DXQUATERNION* pq, D3DXVECTOR3* paxis, FLOAT* pangle)
        {
            paxis->x = pq->x;
			paxis->y = pq->y;
			paxis->z = pq->z;
			*pangle  = 2.0f * acos(pq->w);
        }

		__forceinline D3DXQUATERNION* QuaternionRotationMatrix(D3DXQUATERNION* pout, const D3DXMATRIX* pm)
        {
            int i, maxi;
			FLOAT maxdiag, S, trace;

			trace = pm->m[0][0] + pm->m[1][1] + pm->m[2][2] + 1.0f;
			if ( trace > 1.0f)
			{
				pout->x = ( pm->m[1][2] - pm->m[2][1] ) / ( 2.0f * sqrt(trace) );
				pout->y = ( pm->m[2][0] - pm->m[0][2] ) / ( 2.0f * sqrt(trace) );
				pout->z = ( pm->m[0][1] - pm->m[1][0] ) / ( 2.0f * sqrt(trace) );
				pout->w = sqrt(trace) / 2.0f;
				return pout;
			}
			maxi    = 0;
			maxdiag = pm->m[0][0];
			for (i=1; i<3; i++)
			{
				if ( pm->m[i][i] > maxdiag )
				{
					maxi    = i;
					maxdiag = pm->m[i][i];
				}
			}
			switch( maxi )
			{
			case 0:
				S = 2.0f * sqrt(1.0f + pm->m[0][0] - pm->m[1][1] - pm->m[2][2]);
				pout->x = 0.25f * S;
				pout->y = ( pm->m[0][1] + pm->m[1][0] ) / S;
				pout->z = ( pm->m[0][2] + pm->m[2][0] ) / S;
				pout->w = ( pm->m[1][2] - pm->m[2][1] ) / S;
				break;
			case 1:
				S = 2.0f * sqrt(1.0f + pm->m[1][1] - pm->m[0][0] - pm->m[2][2]);
				pout->x = ( pm->m[0][1] + pm->m[1][0] ) / S;
				pout->y = 0.25f * S;
				pout->z = ( pm->m[1][2] + pm->m[2][1] ) / S;
				pout->w = ( pm->m[2][0] - pm->m[0][2] ) / S;
				break;
			case 2:
				S = 2.0f * sqrt(1.0f + pm->m[2][2] - pm->m[0][0] - pm->m[1][1]);
				pout->x = ( pm->m[0][2] + pm->m[2][0] ) / S;
				pout->y = ( pm->m[1][2] + pm->m[2][1] ) / S;
				pout->z = 0.25f * S;
				pout->w = ( pm->m[0][1] - pm->m[1][0] ) / S;
				break;
			}

			return pout;
        }

		__forceinline D3DXQUATERNION* QuaternionRotationAxis(D3DXQUATERNION* pout, const D3DXVECTOR3* pv, FLOAT angle)
        {
            D3DXVECTOR3 temp;

			Vec3Normalize(&temp, pv);
			
			pout->x = sin( angle / 2.0f ) * temp.x;
			pout->y = sin( angle / 2.0f ) * temp.y;
			pout->z = sin( angle / 2.0f ) * temp.z;
			pout->w = cos( angle / 2.0f );
			
			return pout;
        }

		__forceinline D3DXQUATERNION* QuaternionRotationYawPitchRoll(D3DXQUATERNION* pout, FLOAT yaw, FLOAT pitch, FLOAT roll)
        {
            pout->x = sin( yaw / 2.0f) * cos(pitch / 2.0f) * sin(roll / 2.0f) + cos(yaw / 2.0f) * sin(pitch / 2.0f) * cos(roll / 2.0f);
			pout->y = sin( yaw / 2.0f) * cos(pitch / 2.0f) * cos(roll / 2.0f) - cos(yaw / 2.0f) * sin(pitch / 2.0f) * sin(roll / 2.0f);
			pout->z = cos(yaw / 2.0f) * cos(pitch / 2.0f) * sin(roll / 2.0f) - sin( yaw / 2.0f) * sin(pitch / 2.0f) * cos(roll / 2.0f);
			pout->w = cos( yaw / 2.0f) * cos(pitch / 2.0f) * cos(roll / 2.0f) + sin(yaw / 2.0f) * sin(pitch / 2.0f) * sin(roll / 2.0f);
			
			return pout;
        }

		__forceinline D3DXQUATERNION* QuaternionMultiply(D3DXQUATERNION* pout, const D3DXQUATERNION* pq1, const D3DXQUATERNION* pq2)
        {
            D3DXQUATERNION out;
			
			out.x = pq2->w * pq1->x + pq2->x * pq1->w + pq2->y * pq1->z - pq2->z * pq1->y;
			out.y = pq2->w * pq1->y - pq2->x * pq1->z + pq2->y * pq1->w + pq2->z * pq1->x;
			out.z = pq2->w * pq1->z + pq2->x * pq1->y - pq2->y * pq1->x + pq2->z * pq1->w;
			out.w = pq2->w * pq1->w - pq2->x * pq1->x - pq2->y * pq1->y - pq2->z * pq1->z;
			*pout = out;
			
			return pout;
        }

		__forceinline D3DXQUATERNION* QuaternionNormalize(D3DXQUATERNION* pout, const D3DXQUATERNION* pq)
        {
            D3DXQUATERNION out;
			FLOAT          norm;

			norm = QuaternionLength(pq);

			out.x = pq->x / norm;
			out.y = pq->y / norm;
			out.z = pq->z / norm;
			out.w = pq->w / norm;

			*pout = out;

			return pout;
        }

		__forceinline D3DXQUATERNION* QuaternionInverse(D3DXQUATERNION* pout, const D3DXQUATERNION* pq)
        {
            D3DXQUATERNION out;
			FLOAT norm;

			norm = QuaternionLengthSq(pq);

			out.x = -pq->x / norm;
			out.y = -pq->y / norm;
			out.z = -pq->z / norm;
			out.w = pq->w / norm;

			*pout = out;
			
			return pout;
        }

		__forceinline D3DXQUATERNION* QuaternionLn(D3DXQUATERNION* pout, const D3DXQUATERNION* pq)
        {
            FLOAT norm, normvec, theta;

			norm = QuaternionLengthSq(pq);

			if ( norm > 1.0001f )
			{
				pout->x = pq->x;
				pout->y = pq->y;
				pout->z = pq->z;
				pout->w = 0.0f;
			}
			else if( norm > 0.99999f)
			{
				normvec = sqrt( pq->x * pq->x + pq->y * pq->y + pq->z * pq->z );
				theta   = atan2(normvec, pq->w) / normvec;
				pout->x = theta * pq->x;
				pout->y = theta * pq->y;
				pout->z = theta * pq->z;
				pout->w = 0.0f;
			}

			return pout;
        }

		__forceinline D3DXQUATERNION* QuaternionExp(D3DXQUATERNION* pout, const D3DXQUATERNION* pq)
        {
            FLOAT norm;

			norm = sqrt(pq->x * pq->x + pq->y * pq->y + pq->z * pq->z);
			if (norm )
			{
				pout->x = sin(norm) * pq->x / norm;
				pout->y = sin(norm) * pq->y / norm;
				pout->z = sin(norm) * pq->z / norm;
				pout->w = cos(norm);
			}
			else
			{
				pout->x = 0.0f;
				pout->y = 0.0f;
				pout->z = 0.0f;
				pout->w = 1.0f;
			}
			
			return pout;
        }

		__forceinline D3DXQUATERNION* QuaternionSlerp(D3DXQUATERNION* pout, const D3DXQUATERNION* pq1, const D3DXQUATERNION* pq2, FLOAT t)
        {
            FLOAT dot, epsilon, temp, theta, u;

			epsilon = 1.0f;
			temp    = 1.0f - t;
			u       = t;

			dot = QuaternionDot(pq1, pq2);

			if ( dot < 0.0f )
			{
				epsilon = -1.0f;
				dot     = -dot;
			}
			if( 1.0f - dot > 0.001f )
			{
				theta = acos(dot);
				temp  = sin(theta * temp) / sin(theta);
				u     = sin(theta * u) / sin(theta);
			}
			pout->x = temp * pq1->x + epsilon * u * pq2->x;
			pout->y = temp * pq1->y + epsilon * u * pq2->y;
			pout->z = temp * pq1->z + epsilon * u * pq2->z;
			pout->w = temp * pq1->w + epsilon * u * pq2->w;
			
			return pout;
        }

		__forceinline D3DXQUATERNION* QuaternionSquad(D3DXQUATERNION* pout, const D3DXQUATERNION* pq1, const D3DXQUATERNION* pq2, const D3DXQUATERNION* pq3, const D3DXQUATERNION* pq4, FLOAT t)
        {
            D3DXQUATERNION temp1, temp2;

			QuaternionSlerp(pout, QuaternionSlerp(&temp1, pq1, pq4, t), QuaternionSlerp(&temp2, pq2, pq3, t), 2.0f * t * (1.0f - t));
			
			return pout;
        }

		__forceinline void QuaternionSquadSetup(D3DXQUATERNION* aout, D3DXQUATERNION* bout, D3DXQUATERNION* cout, const D3DXQUATERNION* q0, const D3DXQUATERNION* q1, const D3DXQUATERNION* q2, const D3DXQUATERNION* q3)
        {
            D3DXQuaternionSquadSetup(aout, bout, cout, q0, q1, q2, q3);
        }

		__forceinline D3DXQUATERNION* QuaternionBaryCentric(D3DXQUATERNION* pout, const D3DXQUATERNION* pq1, const D3DXQUATERNION* pq2, const D3DXQUATERNION* pq3, FLOAT f, FLOAT g)
        {
            D3DXQUATERNION temp1, temp2;
			QuaternionSlerp(pout, QuaternionSlerp(&temp1, pq1, pq2, f + g), QuaternionSlerp(&temp2, pq1, pq3, f+g), g / (f + g));
			
			return pout;
        }

    } // namespace MMath

} // namespace endless
