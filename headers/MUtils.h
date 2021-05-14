#pragma once

namespace endless
{
    class MUtils
    {
    public:

        static int rand( int min, int max )
        {
            std::srand( (ulong)GetTickCount64() );
            return min + std::rand() % (max - min);

        } // rand

        static void FormatDateTime( std::string& out )
        {
            struct tm* _ptime;
            time_t     _ctime;
            time(&_ctime);
            _ptime = localtime( &_ctime );

            out = string_format( "%04d.%02d.%02d %02d:%02d:%02d",
                                _ptime->tm_year + 1900,
                                _ptime->tm_mon  + 1,
                                _ptime->tm_mday,
                                _ptime->tm_hour,
                                _ptime->tm_min,
                                _ptime->tm_sec );

        } // FormatDateTime

        //#pragma warning(disable : 4996)
        template<typename ... Args> static std::string string_format( const char* format, Args ... args )
        {
            size_t size = snprintf( nullptr, 0, format, args ... ) + 1; // Extra space for '\0'
            unique_ptr<char[]> buf( new char[ size ] );
            snprintf( buf.get(), size, format, args ... );
            return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
        }

        /* Convert Multi-Bite to Wide */
        static void LtoW( const char* in, std::wstring& out )
        {
            int wchars_num =  MultiByteToWideChar( CP_UTF8, 0, in, -1, NULL, 0 );
            wchar_t* wstr = new wchar_t[wchars_num];
            MultiByteToWideChar( CP_UTF8, 0, in, -1, wstr, wchars_num );
            out = std::wstring(wstr);

            /*
            //1
std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
std::string str = converter.to_bytes(L"Hello world");
std::wstring wstr = converter.from_bytes("Hello world");

//2
std::string str("Hello world!!!");
std::wstring wstr(str.begin(), str.end());
            */

        } // LtoW

        /* Convert Wide to Multi-Bite */
        static void WtoL( wchar_t* in, std::string& out )
        {
            int chars_num = WideCharToMultiByte( CP_ACP, 0, in, -1, 0, 0, NULL, NULL );
            char* str = new char[chars_num];
            WideCharToMultiByte( CP_ACP, 0, in, -1, str, 0, NULL, NULL );
            out = std::string(str);

        } // WtoL

        static std::string& TranslateLastError(std::string& out)
	    { 
		    LPTSTR msgbuff = 0;
		    ulong  dword   = GetLastError();
            char   err_buffer[4048];
            
            ZeroMemory( err_buffer, sizeof(err_buffer) );

		    FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM, NULL, dword, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), (LPTSTR)&msgbuff, 0, NULL );
		    
            sprintf_s( err_buffer, sizeof(err_buffer), "%d: %s", dword, msgbuff);

		    LocalFree(msgbuff);

            out = err_buffer;

            return out;

	    } // GetLastError

		/* преобразует градусы в радианы */
		static inline float FOVDegreeToRadian(float degree)
		{
			return (float)( degree*(XM_PI / 180.0f) );
		}

		/* преобразует радианы в градусы (float)1->90 */
		static inline float FOVRadianToDegree(float radian)
		{
			return (float)(radian*(180.0f / XM_PI));
		}

        static float XMVector3Distance( const XMVECTOR& veca, const XMVECTOR& vecb )
        {
            XMFLOAT3 ponta;
            XMFLOAT3 pontb;
            XMStoreFloat3( &ponta, veca );
            XMStoreFloat3( &pontb, vecb );

            return sqrt( (ponta.x - pontb.x) * (ponta.x - pontb.x) +
                         (ponta.y - pontb.y) * (ponta.y - pontb.y) +
                         (ponta.z - pontb.z) * (ponta.z - pontb.z) );

        } // XMVector3Distance

        static HRESULT CompileShaderFromFile( const char* filename, const char* entry_name, const char* version, ID3DBlob** blob_out )
        {
            HRESULT      hr           = S_OK;
            ID3DBlob*    blob_error   = nullptr;
            std::wstring wstr         = L"";
            DWORD        shader_flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
            shader_flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
            MUtils::LtoW( filename, wstr );

            hr = D3DCompileFromFile( wstr.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry_name, version, shader_flags, 0, blob_out, &blob_error );
            
            if( FAILED(hr) )
            {
                if( blob_error )
                {
                    OutputDebugStringA( reinterpret_cast<const char*>( blob_error->GetBufferPointer() ) );
                    blob_error->Release();
                }
                return hr;
            }
            if( blob_error ) blob_error->Release();

            return S_OK;

        } // CompileShaderFromFile

        static std::string GetCurDir()
        {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            auto p = converter.to_bytes( fs::current_path() );
            std::replace( p.begin(), p.end(), '\\', '/' );

            return std::string(p);

        } // GetCurDir

        static bool FileExists( const char* path )
        {
            std::ifstream file(path);
            bool ret = false;
            ret = !file ? false : true;
            file.close();
            return ret;
            
        } // FileExists

        static void FileLoadBuffer( const char* path, std::stringstream& buffer )
        {
            std::ifstream file( path );
            if( !file ) return;
            buffer << file.rdbuf();
            file.close();

        } // FileLoadBuffer

        static void FileLoadBufferW( const char* path, std::wstringstream& buffer )
        {
            std::ifstream file( path );
            if( !file ) return;
            buffer << file.rdbuf();
            file.close();

        } // FileLoadBufferW

        static const unsigned long FileSize( std::ifstream& file )
        {
            if( !file.is_open() ) return -1;

            file.seekg( 0, std::ifstream::end );
            ulong size = (ulong)file.tellg();
            file.seekg( 0, std::ifstream::beg );

            return size;

        } // FileSize

        static const unsigned long FileSize( FILE* f )
        {
            if(f == NULL) return -1;
            int size = -1;

            fseek(f,0,SEEK_END);
            size = ftell(f);
            rewind(f);

            return size;

        } // FileSize

        static void alert( const char* msg, const char* title = "alert" )
        {
            MessageBox( NULL, msg, title, MB_OK );

        } // alert

        static void alert( std::string msg, std::string title = "alert" )
        {
            MessageBox( NULL, msg.c_str(), title.c_str(), MB_OK );

        } // alert

        static std::vector<std::string> split( const std::string& s, char delimiter )
        {
            std::vector<std::string> tokens;
            std::string              token;
            std::istringstream       tokenStream(s);

            while( std::getline(tokenStream, token, delimiter) )
                tokens.push_back(token);

            return tokens;
        }

        static std::string ltrim( const std::string& str )
        {
            return str.substr( str.find_first_not_of( " \f\n\r\t\v" ) );
        }

        static std::string rtrim( const std::string& str )
        {
            return str.substr( 0, str.find_last_not_of( " \f\n\r\t\v" ) + 1 );
        }

        static std::string trim( const std::string& str )
        {
            return ltrim( rtrim( str ) );
        }

    }; // class MUtils

} // namespace endless
