#ifndef TIMER_H
#define TIMER_H
class timer
    {
    public:
        timer();
        timer(bool running);
        ~timer();
        double read();
        void reset();
        void pause();
        void resume();
        void toggle();
		bool running();
    private:
        bool is_running;
        double time;
    };
#endif
