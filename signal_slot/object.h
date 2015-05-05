    #ifndef DB_OBJECT  
    #define DB_OBJECT  
    #include <map>  
    # define db_slots  
    # define db_signals protected  
    # define db_emit  
    class Object;  
    struct MetaObject  
    {  
        const char * sig_names;  
        const char * slts_names;  
        static void active(Object * sender, int idx);  
    };  
    struct Connection  
    {  
        Object * receiver;  
        int method;  
    };  
    typedef std::multimap<int, Connection> ConnectionMap;  
    typedef std::multimap<int, Connection>::iterator ConnectionMapIt;  
    class Object  
    {  
        static MetaObject meta;  
        void metacall(int idx);  
    public:  
        Object();  
        virtual ~Object();  
        static void db_connect(Object*, const char*, Object*, const char*);  
        void testSignal();  
    db_signals:  
        void sig1();  
    public db_slots:  
        void slot1();  
    friend class MetaObject;  
    private:  
         ConnectionMap connections;  
    };  
    #endif  
