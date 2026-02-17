class Velo {
    private: 
    int Pin;
    int ID;
    static int count;
    int led_pin;
    
    public:
    Velo(int pin, int l_pin);
    bool Check();
    void debug();
    
};