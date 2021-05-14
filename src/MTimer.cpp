
namespace endless
{

using namespace std::chrono;

    long long MTimer::DeltaTime()
    {
        return __max( delta_time, 1L );

    } // DeltaTime

    long long MTimer::TimeLocal()
    {
        return duration_cast<std::chrono::microseconds>(time_frame_end - time_run).count();

    } // TimeLocal

    void MTimer::RemTimeRun()
    {
        time_run = high_resolution_clock::now();

    } // RemTimeRun

    void MTimer::RemTimeFrameBegin()
    {
        time_frame_begin = high_resolution_clock::now();

    } // RemTimeFrameBegin

    void MTimer::RemTimeFrameEnd()
    {
        time_frame_end = high_resolution_clock::now();
        delta_time     = duration_cast<std::chrono::microseconds>(time_frame_end - time_frame_begin).count();

    } // RemTimeFrameEnd

    void MTimer::Setup()
    {}

    MTimer::MTimer():
        time_run(),
        time_frame_begin(),
        time_frame_end(),
        delta_time(1L)
    {}

    MTimer::MTimer(MTimer&)
    {}

    MTimer::~MTimer()
    {}

} // namespace endless
