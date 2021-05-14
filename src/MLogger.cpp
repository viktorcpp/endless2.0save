
namespace endless
{
    template<typename ... Args> MLogger* MLogger::LogN( const char* format, Args ... args )
    {
        std::lock_guard<std::recursive_mutex> locker( MCore::GetMutex() );
        std::string out = MUtils::string_format( format, args... );

        log_n << out.c_str() << std::flush;

        if( MCore::GetMHud() )
        {
            MCore::GetMHud()->LogConsoleN( out.c_str() );
        }

        return this;

    } // LogN

    template<typename ... Args> MLogger* MLogger::LogND( const char* format, Args ... args )
    {
        log_n << MUtils::string_format( format, args... ).c_str() << std::flush;
        return this;

    } // LogD

    template<typename ... Args> MLogger* MLogger::LogW( const char* format, Args ... args )
    {
        std::string out = MUtils::string_format( format, args... );
        log_w << out.c_str() << std::flush;

        return this;

    } // LogW

    template<typename ... Args> MLogger* MLogger::LogE( const char* format, Args ... args )
    {
        std::string out = MUtils::string_format( format, args... );

        log_e << out.c_str() << std::flush;

        return this;

    } // LogE

    MLogger::MLogger()
    {
        std::experimental::filesystem::create_directory("logs/");
        
        log_n.open("logs/log-normal.txt", std::ios::out);
        log_e.open("logs/log-error.txt",  std::ios::out);
        log_w.open("logs/log-warn.txt",   std::ios::out);

        hud_buffer.str("");
        hud_buffer.clear();

        std::string date;
        MUtils::FormatDateTime(date);

        log_n << "++++++++++++++++++++++++++++++++ " << date.c_str() << " ++++++++++++++++++++++++++++++++\n";
        log_n << "Logger is ready.\n";
        log_n << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";

    } // MLogger

    MLogger::MLogger(MLogger&)
    {}

    MLogger::~MLogger()
    {
        log_n.close();
        log_w.close();
        log_e.close();
    }

    template<> MLogger* Singleton<MLogger>::_instance  = 0;

} // namespace endless
