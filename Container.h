#ifndef CONTAINER_H
#define CONTAINER_H
#include "Core.h"
#include <vector>
#include <stdio.h>
#include <string>
#include "stringconnector.h"
#include <boost/tokenizer.hpp>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace boost;


class Container : public Core {
    protected:
    
    vector <string> charVector;
    vector <stringconnector*> Parsedlist;
    //vector <string> operands;
    
    
    //vector <char* const> Charlist;
    public:
    //constructor
    Container(){};
    ~Container(){};
    
    void read() {
        
        cout << "$ "; 
        getline(cin,userinput);
        //cout << userinput;
        //getline(cin, userinput);
        //charVector.at(i).at(charVector.at(i).size
        
    }
    void parse() { 
    //\"embedded quote\",    
    string sep1("");
    string sep2(" ");
    string sep3(""); 

    escaped_list_separator<char> els(sep1,sep2,sep3);
    tokenizer<escaped_list_separator<char> > tok(userinput, els);
       
        for(tokenizer<escaped_list_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
        charVector.push_back(*beg);
        }
       
        //for test purposes, not essential
        // for (int i = 0; i < charVector.size(); ++i) {
        //     cout << charVector.at(i) << endl;
        // }
        
        vector <stringconnector*> Parsedlist;
    
        int j = 0;
        for (int i = 0; i < charVector.size(); ++i) {
            
            if (charVector.at(i) == "&&" || charVector.at(i) == "||") {
            stringconnector* temp = new stringconnector(charVector.at(j),charVector.at(j+1),charVector.at(i));
            for (j = j + 2; j < i; ++j) {
                temp->pushback(charVector.at(j));
            }
            j = j + 1;
            Parsedlist.push_back(temp);
            }
            
            else if(charVector.at(i).at(charVector.at(i).size() - 1) == ';') {
            stringconnector* temp = new stringconnector(charVector.at(j),";");
            //string tempcolon = charVector.at(i);
            charVector.at(i).erase(charVector.at(i).size()-1 , 1);
            //inital pushback case
            temp->specialpushback(charVector.at(j+1));
            for (j= j + 2; j <= i; ++j) {
                temp->pushback(charVector.at(j));
            }
        //    j = j + 1;
            Parsedlist.push_back(temp);
            }
            
            else if (i == charVector.size() - 1) {
               
            if (j == i) {
                stringconnector* temp = new stringconnector(charVector.at(j), "", "X");
                
                Parsedlist.push_back(temp);                 
            }  
            else { 
            stringconnector* temp = new stringconnector(charVector.at(j), charVector.at(j+1), "X");
            for (j = j + 2; j <= i; ++j) {
                temp->pushback(charVector.at(j));
            }
              Parsedlist.push_back(temp);
            }
          }
        }
        
        //test that outputs the list that we have parsed
        for (int k = 0; k < Parsedlist.size(); ++k) {
            Parsedlist.at(k)->output(k+1);
        }
     
          
         //array of array of cstrings 
         char** FinalArray[9999];
         
         for (int z = 0; z < Parsedlist.size(); ++z) {
             int aa = Parsedlist.at(z)->executable.size(); 
             //cstring of executable
             char xnum[aa + 1];
             xnum[aa] = '\0';
             for (int ab = 0; ab < aa; ++ab) {
                 xnum[ab] = Parsedlist.at(z)->executable.at(ab);
             }
    
             //cstring of argument
             int ac = Parsedlist.at(z)->argument.size();
             char anum[ac + 1];
             anum[ac] = '\0';
             for (int ad = 0; ad < ac; ++ad) {
                 anum[ad] = Parsedlist.at(z)->argument.at(ad);
             }

             //cstring of connector
             int ae = Parsedlist.at(z)->connector.size();
             char cnum[ae + 1];
             cnum[ae] = '\0';
             for (int af = 0; af < ae; ++af) {
                 cnum[af] = Parsedlist.at(z)->connector.at(af);
             }
            
            //array of cstrings
             char* aoc[4];
             aoc[0] = xnum;
             aoc[1] = anum;
             aoc[2] = NULL;
             aoc[3] = '\0';
             
             
            // for(int c = 0; c < 2; ++c) {
            //     cout << aoc[c] << endl;
            // }
             
             
            //cout << execvp(aoc[0], aoc); 
    
            // FinalArray[z] = aoc;
             //to add the operand
            // FinalArray[z+1] =  
         }
         
        // cout << FinalArray[0][0];    
            
            
    }
    
    void execute() {
        //char *execArgs[] = { "echo", "Hello, World!", NULL };
        // for(int i = 0; i < Parsedlist.size(); ++i) {
        //     Charlist.push_back(Parsedlist.at(i));
        // }
        
        // for(int j = 0; j < Charlist.size(); ++j) {
        //     cout << "elem: " << Charlist.at(j);
        // }
        
        // pid_t child;
        // int status;
        
        // child = fork();
        
        // if(child == -1){
        //     cout << "error";
        // }
        // if(child == 0){
        //     execvp("/bin", Charlist);
        // }
        // else {
        //     cout << "uhh fail?";
        
        // }
        
          
            
    }
};

#endif
