#pragma once

namespace endless
{
    class MScripts : public Singleton<MScripts>
    {
    public:

        int         GetI(const char* name);
        double      GetD(const char* name);
        float       GetF(const char* name);
        std::string GetC(const char* str_script);
        bool        GetB(const char* name);
        
        void DoString( std::string str );
        void DoString( const char* str );
        void DoString( duk_context* context, std::string str );
        void DoString( duk_context* context, const char* str );

        void DoFile( std::string filename );
        void DoFile( const char* filename );

        void CallFunc( const char* );

        void Setup() throw(std::exception);

        void GetPropString( duk_context* context, const char* prop, std::string& dest );
        void GetPropFloat ( duk_context* context, const char* prop, float& dest );
        void GetPropLong  ( duk_context* context, const char* prop, long& dest );

        static void duk_fatal_handle( void* udata, const char* msg );
        
        MScripts();
        ~MScripts();
        
    private:

        duk_context* context = nullptr;
        _CFG         cfg_def = {};

        MScripts(MScripts&);

    }; // class MScripts

} // endless
