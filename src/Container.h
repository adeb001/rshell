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
    char** FinalArray[9999];
    char* aoc[3];     
    
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
    
        int j = 0;
        for (int i = 0; i < charVector.size(); ++i) {
            
            if (charVector.at(i) == "&&" || charVector.at(i) == "||") {
            stringconnector* temp = new stringconnector(charVector.at(j),charVector.at(i));
        
            for (j = j + 1; j < i; ++j) {
                temp->specialpushback(charVector.at(j));
            }
            
             for (j = j + 2; j < i; ++j) {
                temp->pushback(charVector.at(j));
            }
            j = i + 1;
            Parsedlist.push_back(temp);
            }
            
            else if(charVector.at(i).at(charVector.at(i).size() - 1) == ';') {
           // stringconnector* temp = new stringconnector(charVector.at(j),";");
            //string tempcolon = charVector.at(i);
            charVector.at(i).erase(charVector.at(i).size()-1 , 1);
            stringconnector* temp = new stringconnector(charVector.at(j),";");
            //inital pushback case
            //temp->specialpushback(charVector.at(j+1));
            for (j= j + 1; j <= i; ++j) {
                temp->specialpushback(charVector.at(j));
            }
            
            for (j= j + 2; j <= i; ++j) {
                temp->pushback(charVector.at(j));
            }
            
            
        j = i + 1;
            Parsedlist.push_back(temp);
            }
            
            else if (i == charVector.size() - 1) {
               
            if (j == i) {
                stringconnector* temp = new stringconnector(charVector.at(j),  "X");
                
                Parsedlist.push_back(temp);                 
            }  
            else { 
            stringconnector* temp = new stringconnector(charVector.at(j), "X");
        
        
            // if (j + 1 <= i) {
            //     temp->specialpushback(charVector.at(j));
            // }
        
            // for (j = j + 1; j <= i; ++j) {
            //     temp->specialpushback(charVector.at(j));
            // }
            
            
             temp->specialpushback(charVector.at(j))
            
             for (j = j + 1; j <= i; ++j) {
                temp->pushback(charVector.at(j));
            }
            
              Parsedlist.push_back(temp);
            }
          }
        }
        
        //test that outputs the list that we have parsed
        // for (int k = 0; k < Parsedlist.size(); ++k) {
        //     Parsedlist.at(k)->output(k+1);
        // }
        
            
    }
    
    void execute() {
        
      //   cout << Parsedlist.at(0)->argument << endl;
        
          bool didcommandexecute = false;
        
            string prevcon = "Start";
            bool prevtruth = true;
             bool doexecute = true;
             
             //this for loop loops for each position in the parsed list
             //it creates
            for (int z = 0; z < Parsedlist.size(); z = z + 1) {
            // cout << "testing this" << endl;
             doexecute = true;
             int aa = Parsedlist.at(z)->executable.size(); 
             //cstring of executable
             //char* xnum = new char[aa+1];
             char xnum[aa + 1];
             xnum[aa] = '\0';
             for (int ab = 0; ab < aa; ++ab) {
                 xnum[ab] = Parsedlist.at(z)->executable.at(ab);
             } //for int ab
             //cstring of argument
             int ac = Parsedlist.at(z)->argument.size();
             //char* anum = new char[ac+1];
             char anum[ac + 1];
             anum[ac] = '\0';
             
             for (int ad = 0; ad < ac; ++ad) {
                 anum[ad] = Parsedlist.at(z)->argument.at(ad);
             } //for int ad

             //cstring of connector
             int ae = Parsedlist.at(z)->connector.size();
             //char* cnum = new char[ae+1];
             char cnum[ae + 1];
             cnum[ae] = '\0';
             for (int af = 0; af < ae; ++af) {
                 cnum[af] = Parsedlist.at(z)->connector.at(af);
             } // for intt af
            //array of cstrings
             //char* aoc[4];
             aoc[0] = xnum;
             aoc[1] = anum;
             aoc[2] = NULL;
               
            cout << aoc[0] << " " << aoc[1] << endl; 
               
                //cnum = connector
            
        //    cout << aoc[0] << " " << aoc[1] << endl;
            // if (prevcon == "Start" ) {
            //       bool doexecute = true;
                
            // }
            
            // else if (prevcon == "&&") {
            //     if (prevtruth == true) {
            //         doexecute = true;
            //     }
            //     //truth = false
            //     else {
            //         doexecute = false;
            //     }
            // }
            
            // else if (prevcon == "||") {
                
            //     if (prevtruth == true) {
            //         doexecute = false;
            //     }
            //     else {
            //         doexecute = true;
            //     }
                
            // }
            
            // else if (prevcon == ";") {
            //     doexecute == true;
            // }
            
            // else if (prevcon == "X") {
            //     doexecute = true;
            // }
            
            // WE ONLY ATTEMPT AN EXECUTE IF DOEXECUTE IS TRUE
            //if (doexecute == true) {
   

                
       
   
            //}
            
            
            //here we assign the truth

            //this i sjust placeholder bool... need a way to see if command executed
            
            // i set this iteration of fr loop to not execute the command (only with && and || special cases)
            // if (doexecute == false) {
            // //   (  false && (?) ) is always false. (?) is never executed
            // if (prevcon == "&&") {
            //     prevtruth = false;
            // }
            // //   (true || (?) ) is always true. (?) is never exeuted
            // else if (prevcon == "||") {
            //     prevtruth = true;
            // }
        
            // }
            // //doexecite = true, in this case there was an attempt to execute
            // else {
            // if (prevcon == "START") {
            //     //if our command did execute properly
            //     if (didcommandexecute == true) {
            //     prevtruth = true;    
            //     }
            //     else {
            //     prevtruth = false;
            //     }
            // }
            // else if (prevcon == "&&") {
            //     //command executed properly
            //     // (true && true) = true
            //     if (didcommandexecute == true) {
            //     prevtruth = true;    
            //     }
            //     //comand did not execute properly
            //     // (true && false) = false
            //     else {
            //     prevtruth = false;
            //     }
            // }
            
            // else if (prevcon == "||") {
            
            // //command executed properly
            // //(false || true) = true
            // if (didcommandexecute == true) {
            //     prevtruth = true;
            // }
            // // (false || false) = false
            // else {
            //     prevtruth = false;
            // }
            // }
            // else if (prevcon == ";") {
            //  //this is almost like starting from the start.
            //  prevtruth = true;   
            // }
            // else if (prevcon == "X") {
            //     //i dont think anything needs to go here really
            //     prevtruth = true;
            // }
            
            // }//bracket for else
            
            //assign prevcon here so we know it for the next loop
            //truth values and connectors reset if we reach a ;
            
            //prevcon = Parsedlist.at(z)->connector;
            
            
             }// for int z
  
    }
};

#endif
