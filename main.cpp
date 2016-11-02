#include <iostream>
using namespace std;
#include <vector>
#include "Core.h"
#include "Connector.h"
#include "Container.h"
#include <string>
#include <stdio.h>
#include "stringconnector.h"
#include <boost/tokenizer.hpp>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace boost;


int main() {
    
    int run = 1;
      
    
    
    do {
        Container *contain = new Container();
        contain->read();
    
        if(contain->userinput == "exit") {
        //cout << endl;
        run = 0;
        } 
        else {
        contain->parse();
        contain->execute();
        }
        
    }
    while(run != 0);
        
        

    
    
    
    
    
    
    return 0;
}