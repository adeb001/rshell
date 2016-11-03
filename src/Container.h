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
#include <sys/mman.h>

using namespace boost;


class Container : public Core {
    protected:
    
    vector <string> charVector;
    vector <stringconnector*> Parsedlist;
    char** FinalArray[9999];
    char* aoc[3];     
    
    public:
    //constructor
    Container(){};
    ~Container(){};
    
    void read() {
        cout << "$ "; 
        getline(cin,userinput);
    }
    void parse() { 
    
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
    
        //implements comment functionality
        
        for (unsigned int k = 0; k < charVector.size(); ++k) {
            
            if (charVector.at(k).at(0) == '#') {
                charVector.resize(k);
                
            }
            else if (charVector.at(k) == "#") {
                charVector.resize(k);
                
            }
        }
        
        //reused variable j
        unsigned int j = 0;
        for (unsigned int i = 0; i < charVector.size(); ++i) {
           
            // if i goes to the last list element 
            if (i == charVector.size() - 1) {
                
                
            //if in the last element holds a ; need to get rid of it
            if(charVector.at(i).at(charVector.at(i).size() - 1) == ';') {
                charVector.at(i).erase(charVector.at(i).size()-1 , 1);
            }    
                
               
            if (j == i) {
                stringconnector* temp = new stringconnector(charVector.at(j),  "X");
                Parsedlist.push_back(temp);                 
            }  
            
            else {
                stringconnector* temp = new stringconnector(charVector.at(j), "X");
                j = j + 1;
                temp->specialpushback(charVector.at(j));
                
                for (j = j + 1; j <= i; ++j) {
                    temp->pushback(charVector.at(j));
                }
                
                Parsedlist.push_back(temp);
            }
                
            } // if last
            
            else if (charVector.at(i) == "&&" || charVector.at(i) == "||") {
                stringconnector* temp = new stringconnector(charVector.at(j),charVector.at(i));
                
                j = j + 1;
                temp->specialpushback(charVector.at(j));
                
                for (j = j + 1; j < i; ++j) {
                temp->pushback(charVector.at(j));
                }
                
                j = i + 1;
                Parsedlist.push_back(temp);
            } // if && or ||
            
          
            //if i reaches a semicolon
            else if(charVector.at(i).at(charVector.at(i).size() - 1) == ';') {
            // stringconnector* temp = new stringconnector(charVector.at(j),";");
            //string tempcolon = charVector.at(i);
            charVector.at(i).erase(charVector.at(i).size()-1 , 1);
            stringconnector* temp = new stringconnector(charVector.at(j),";");
            //inital pushback case
            //temp->specialpushback(charVector.at(j+1));
            
            j = j + 1;
            temp->specialpushback(charVector.at(j));
            
            // for (j= j + 1; j <= i; ++j) {
            //     temp->specialpushback(charVector.at(j));
            // }
            
            for (j= j + 2; j <= i; ++j) {
                temp->pushback(charVector.at(j));
            }
            
            j = i + 1;
            Parsedlist.push_back(temp);
            }//if ;
            
        }
        
    }
    
    
    void execute() {
        //   cout << Parsedlist.at(0)->argument << endl;
        bool didcommandexecute = false;
        string prevcon = "Start";
        bool prevtruth = true;
        bool doexecute = true;
             
            //this for loop loops for each position in the parsed list
            //it creates
        for (unsigned int z = 0; z < Parsedlist.size(); z = z + 1) {
            didcommandexecute = true;
            // cout << "testing this" << endl;
            //doexecute = true;
            int aa = Parsedlist.at(z)->executable.size(); 
            //cstring of executable
            //char* xnum = new char[aa+1];
            //char xnum[aa + 1];
            char* xnum = new char[aa + 1];
            xnum[aa] = '\0';
            for (int ab = 0; ab < aa; ++ab) {
                xnum[ab] = Parsedlist.at(z)->executable.at(ab);
            } //for int ab
            //cstring of argument
            int ac = Parsedlist.at(z)->argument.size();
            //char* anum = new char[ac+1];
            //char anum[ac + 1];
            char* anum = new char[ac + 1];
            anum[ac] = '\0';
             
            for (int ad = 0; ad < ac; ++ad) {
                anum[ad] = Parsedlist.at(z)->argument.at(ad);
            } //for int ad

        
            aoc[0] = xnum;
            aoc[1] = anum;
            aoc[2] = NULL;
               
            //  cout << aoc[0] << " : " << aoc[1] << endl; 
               
            if (prevcon == "Start" ) {
                doexecute = true;
            }
            
            else if (prevcon == "&&") {
                if (prevtruth == true) {
                    doexecute = true;
                }
                //truth = false
                else {
                    doexecute = false;
                }
            }
            
            else if (prevcon == "||") {
                if (prevtruth == true) {
                    doexecute = false;
                }
                else {
                    doexecute = true;
                }
                
            }
            
            else if (prevcon == ";") {
                doexecute = true;
            }
            
            // WE ONLY ATTEMPT AN EXECUTE IF DOEXECUTE IS TRUE
            if (doexecute == true) {
                
                
                pid_t pid;  // the child process that the execution runs inside of.
                int stat;      // exit status of child process.
                pid = fork();
                if (pid == -1)
                { //A problem has occured with the forking call.
                    perror("fork");
                }
                else if (pid == 0){
                    //execvp executes the command stored in aoc[0] over aoc    
                    execvp(aoc[0], aoc);
                    perror("exec");
                    exit(-1);
                }
                //pid > 1, thus we are in the parent's process
                else {
                    if( waitpid( pid, &stat, 0 ) == -1 ) {
                        perror( "waitpid" );
                    }
                    else if( WIFEXITED(stat) && WEXITSTATUS(stat) != 0 ) {
                        //if it reaches this branch the child fails
                        didcommandexecute = false;
                    }
                }
            } //if doexecute = true
            
            //here we assign the truth values
            // i set this iteration of fr loop to not execute the command (only with && and || special cases)
            if (doexecute == false) {
            //   (  false && (?) ) is always false. (?) is never executed
            if (prevcon == "&&") {
                prevtruth = false;
            }
            //   (true || (?) ) is always true. (?) is never exeuted
            else if (prevcon == "||") {
                prevtruth = true;
            }
            }
            //doexecite = true, in this case there was an attempt to execute
            else {
            if (prevcon == "START") {
                //if our command did execute properly
                if (didcommandexecute == true) {
                prevtruth = true;    
                }
                else {
                prevtruth = false;
                }
            }
            
            // (T && (?) )
            else if (prevcon == "&&") {
                //command executed properly
                // (true && true) = true
                if (didcommandexecute == true) {
                prevtruth = true;    
                }
                //comand did not execute properly
                // (true && false) = false
                else {
                prevtruth = false;
                }
            }
            //F || (?)
            else if (prevcon == "||") {
            
            //command executed properly
            //(false || true) = true
            if (didcommandexecute == true) {
                prevtruth = true;
            }
            // (false || false) = false
            else {
                prevtruth = false;
            }
            }
            else if (prevcon == ";") {
             //this is almost like starting from the start.
             prevtruth = true;   
            }
        
            
            }//bracket for else
            
            //assign prevcon here so we know it for the next loop
            //truth values and connectors reset if we reach a ;
		
            prevcon = Parsedlist.at(z)->connector;
	delete[] anum;
	delete[] xnum;
              }// for int z
  
    }
};

#endif
