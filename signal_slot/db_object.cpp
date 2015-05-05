    #include "object.h"  
    static const char sig_names[] = "sig1/n";  
    static const char slts_names[] = "slot1/n";  
    MetaObject Object::meta = {sig_names, slts_names};  
    void Object::sig1()  
    {  
        MetaObject::active(this, 0);  
    }  
    void Object::metacall(int idx)  
    {  
        switch (idx) {  
            case 0:  
                slot1();  
                break;  
            default:  
                break;  
        };  
    }  
