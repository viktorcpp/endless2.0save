#pragma once

namespace endless
{

#define MWINDOW MWindow::Ref()

    class MWindow : public Singleton<MWindow>
    {

    public:
        
        void Setup() throw(std::exception);
        void SetVisible(bool vis);
        void MoveCenter(int width, int height);
        void Resize(int w, int h);
        HWND GetHandle(){ return hWnd; }
        bool IsActive(){ return is_active; }
        void Activate(bool activate);

        MWindow();
        virtual ~MWindow();

    private:

        HWND hWnd        = nullptr;
        bool is_centered = false;
        bool is_active   = false;

    }; // MWindow

} // namespace endless
