#pragma once

namespace endless
{

#define MLOGGER MCore::GetMLogger()
#define LOGN(...)  MCore::GetMLogger()->LogN (__VA_ARGS__);
#define LOGND(...) MCore::GetMLogger()->LogND(__VA_ARGS__);
#define LOGW(...)  MCore::GetMLogger()->LogW (__VA_ARGS__);
#define LOGE(...)  MCore::GetMLogger()->LogE (__VA_ARGS__);

    class MLogger : public Singleton<MLogger>
    {
    public:
        
        /* Normal log */
        template<typename ... Args> MLogger* LogN ( const char* format, Args ... args );
        template<typename ... Args> MLogger* LogND( const char* format, Args ... args );

        /* Warning log */
        template<typename ... Args> MLogger* LogW( const char* format, Args ... args );

        /* Error log */
        template<typename ... Args> MLogger* LogE( const char* format, Args ... args );

        MLogger();
        virtual ~MLogger();

    private:

        std::ofstream     log_n;
        std::ofstream     log_e;
        std::ofstream     log_w;
        std::stringstream hud_buffer;

        MLogger(MLogger&);

    }; // class MLogger

} // namespace endless
