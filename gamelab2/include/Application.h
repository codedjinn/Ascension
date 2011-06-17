#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

class Application {

public :
    Application(){this->_running = false;}

    virtual ~Application() {
    }

    int runApp()
    {
        if (initialize()) {
            while(_running)
            {
                interact();
                process();
            }
            cleanup();
        }
        return terminate();
    }

    unsigned int exit_code;

protected :
    virtual void cleanup() = 0;
    virtual int terminate() = 0;
    virtual void interact() = 0;
    virtual bool initialize() = 0;
    virtual void process() = 0;
    bool _running;
};

#endif // APPLICATION_H_INCLUDED
