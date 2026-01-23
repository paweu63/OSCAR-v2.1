class Velo {
    private: 
    int Pin;
    int ID;
    static int count;
    
    public:
    Velo(int pin);
    bool Check();
    void debug();
    
};