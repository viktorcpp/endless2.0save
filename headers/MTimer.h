#pragma once

namespace endless
{

    class MTimer
    {
    public:

        /* microseconds */
        long long DeltaTime();
        /* microseconds */
        long long TimeLocal();
        
        void RemTimeRun();
        void RemTimeFrameBegin();
        void RemTimeFrameEnd();

        void Setup();

        MTimer();
        virtual ~MTimer();

    private:

        std::chrono::time_point<std::chrono::steady_clock> time_run;
        std::chrono::time_point<std::chrono::steady_clock> time_frame_begin;
        std::chrono::time_point<std::chrono::steady_clock> time_frame_end;

        long long delta_time = 1L;

        MTimer(MTimer&);

    }; // class MTimer

} // namespace endless
