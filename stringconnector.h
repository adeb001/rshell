#ifndef stringconnector_H
#define stringconnector_H


class stringconnector {
    private:
    
    
    
    public:
    string connector;
    string executable;
    string argument;
    
    // stringconnector(string a, string b, string c) {
    // executable = a;
    // argument = b;
    // connector = c;
    
    // }
    //special constructor for the ; case
    stringconnector(string a, string c) {
        executable = a;
        connector = c;
        argument = "";
    }
    
    void specialpushback(string b) {
        argument.append(b);
    }
    
    void pushback(string a) {
        argument.push_back(' ');
        argument.append(a);
        
    }
    
    void output(int u) {
        cout << "Executable" << u << ": " << executable << endl;
        cout << "Argument" << u <<   ": " << argument << endl;
        cout << "Connector" << u << ": " << connector << endl;
    }
    
    int getsize() {
        return argument.size();
    }
    
    
    
};



#endif
