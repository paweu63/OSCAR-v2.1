class Pump {
    private: 
    int Pin;
    
    public:
    Pump(int pin);
    void start(int);
    void stop();
    void venting();
    
};