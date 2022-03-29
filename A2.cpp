#include <iostream>
#include <string.h>
#include"inord_list.h"
#include <fstream>
#include <sstream>
using namespace std;

inord_list alphalist;

bool readFiles(string filename,int& totalwordscount) // read the file and returns the number of words in the file
{

    ifstream txtfile;
    txtfile.open(filename);
    if (!txtfile.is_open()) return false;  //check if is still open (retrun error)

    //string word;
    string line;
    int line_n = 0;    // this is the line count of a word in the file
    int word_n = 0;    //this is the word count in the file

    while (getline(txtfile, line))  // separate file into lines
    {
        line_n++;
        int linelen = line.length();
        string word;
        for (int i = 0; i <= linelen - 1; i++)
        {
            if ((line[i] == ',') || (line[i] == '\'') || (line[i] == '?') || (line[i] == '!') || (line[i] == ';') || (line[i] == ':') || (line[i] == '`') || (line[i] == '&') || (line[i] == '"') || (line[i] == '[') || (line[i] == ']') || (line[i] == '{') || (line[i] == '}') || (line[i] == '(') || (line[i] == ')') || (line[i] == '.'))
            {
                line[i] = ' ';
            }
            line[i] = tolower(line[i]);
        }

        stringstream streamline(line);
        while (streamline >> word) // separate lines into words (separated by whitespaces and endlines)
        {
            word_n++;
            alphalist.insert(word, word_n, line_n);
        }

    }
    totalwordscount = word_n;
    txtfile.close();
    return true;
}



int charcount(string filename) //returns the number of characters in the file (including spaces and newlines/carriage return)
{

    int allchars = 0;  //this is the count of all chars in thw whole file including spaces

    string line;
    ifstream txtfile;
    txtfile.open(filename);
    if (!txtfile.is_open()) return 0;  //check if is still open (retrun error)

    while (getline(txtfile, line))
    {
       
        allchars = allchars + line.length();
        allchars++;
        
    }
  
    txtfile.close();
    return allchars;
   
}



int main(int argc, char **argv)
{
    bool first = true;
    if (argc != 3)
    {
        cout << "Incorrect number of arguments";
        return 0;
    }

    bool valid = true;
    int totalwordscount = 0; //words count in te file;
    valid = readFiles(argv[1],totalwordscount);
    if (!valid)
    {
        cout << "File not found";
        return 0;
    }

    ifstream txtfile;
    txtfile.open(argv[2]);
    if (!txtfile.is_open())
    {
        cout << "File not found";
        return 0;
    }

    string line;
    while (getline(txtfile, line)) // loop that reads commands lines, line by line
    {
        string word;
        string command;
        string myword;
        stringstream element(line);
        int count = 0;

        while (element >> word) // check that each line has at most 2 words
        {
            count++;
        }
        stringstream element2(line);    //to reset the line to element variable to be tested;
        element2 >> command;
        if ((command !="wordCount" ) && (command != "distWords") && (command != "charCount") && (command != "frequentWord") && (command != "countWord") && (command != "starting") && (command != "containing") && (command != "search"))
        {
            if (first)
            {
                cout << "Undefined command";
                first = false;
                continue;
            }
            else
            {
                cout << endl <<"Undefined command";
                continue;
            }
        }
        else
        {
            if (count > 2)
            {
                if (first)
                {
                    cout << "Incorrect number of arguments";
                    first = false;
                    continue;
                }
                else
                {
                    cout << endl << "Incorrect number of arguments";
                    continue;
                }
            }
        }
        if (command == "wordCount")
        {
            if (count != 1)   /// check that this command has the valid number of arguments
            {
                if (first)
                {
                    cout << "Incorrect number of arguments";
                    first = false;
                }
                else
                {
                    cout << endl << "Incorrect number of arguments";
                }
            }

            else  // the arguments number are correct
            {
                if (first)
                {
                    cout << totalwordscount << " words";
                    first = false;
                }
                else
                {
                    cout << endl << totalwordscount<<" words";
                }
            }
        }
///////////////////////////////////////////////////////////////////////////////////
        else if (command == "distWords")
        {
            if (count != 1)   /// check that this command has the valid number of arguments
            {
                if (first)
                {
                    cout << "Incorrect number of arguments";
                    first = false;
                }
                else
                {
                    cout << endl << "Incorrect number of arguments";
                }
            }

            else  // the arguments number are correct
            {
                int distinctcount = alphalist.distinct();
                if (first)
                {
                    cout << distinctcount << " distinct words";
                    first = false;
                }
                else
                {
                    cout << endl << distinctcount << " distinct words";
                }
            }
        }
/// ////////////////////////////////////////////////////////////////////////

        else if (command == "charCount")
        {
            if (count != 1)   /// check that this command has the valid number of arguments
            {
                if (first)
                {
                    cout << "Incorrect number of arguments";
                    first = false;
                }
                else
                {
                    cout << endl << "Incorrect number of arguments";
                }
            }

            else  // the arguments number are correct
            {
                int chars = charcount(argv[1]);
                if (first)
                {
                    cout << chars << " characters";
                    first = false;
                }
                else
                {
                    cout << endl << chars << " characters";
                }
            }
        }
////////////////////////////////////////////////////////////////////////////////////
        else if (command == "frequentWord")
        {
            if (count != 1)   /// check that this command has the valid number of arguments
            {
                if (first)
                {
                    cout << "Incorrect number of arguments";
                    first = false;
                }
                else
                {
                    cout << endl << "Incorrect number of arguments";
                }
            }

            else  // the arguments number are correct
            {
                string chars = alphalist.freq();
                if (first)
                {
                    cout <<"Most frequent word is: "<<chars;
                    first = false;
                }
                else
                {
                    cout << endl<< "Most frequent word is: " << chars;
                }
            }
        }
////////////////////////////////////////////////////////////////////////////////////
        else if (command == "countWord")
        {
         element2 >> myword;
         if (count != 2)   /// check that this command has the valid number of arguments
            {
                if (first)
                {
                    cout << "Incorrect number of arguments";
                    first = false;
                }
                else
                {
                    cout << endl << "Incorrect number of arguments";
                }
            }

            else  // the arguments number are correct
            {
             int chars = alphalist.countcertain(myword, totalwordscount);
                if (first)
                {
                    if (chars == 0)
                    {
                        cout << "Word not found";
                            first = false;
                    }
                    else
                    {  
                        cout << myword << " " << "is repeated " << chars << " times";
                        first = false;
                    }
                }
                else
                {
                    if (chars == 0)
                    {
                        cout <<endl<<"Word not found"; 
                    }
                    else
                    {
                        cout <<endl<<myword << " " << "is repeated " << chars << " times";
                    }
                }
            }
        }
////////////////////////////////////////////////////////////////////////////////////
        else if (command == "starting")
        {
         element2 >> myword;
         if (count != 2)   /// check that this command has the valid number of arguments
            {
                if (first)
                {
                    cout << "Incorrect number of arguments";
                    first = false;
                }
                else
                {
                    cout << endl << "Incorrect number of arguments";
                }
            }

            else  // the arguments number are correct
            {
                if (first)
                {
                    if (!alphalist.startingwith(myword, totalwordscount))
                    {
                        cout << "Word not found";
                            first = false;
                    }
                    else
                    {  
                        //nothing as the function already perforemed in the if condition
                        first = false;
                    }
                }
                else
                {
                    cout << endl;

                    if (!alphalist.startingwith(myword, totalwordscount))
                    {
                        cout <<"Word not found"; 
                    }
                    else
                    {
                        //nothing as the function already perforemed in the if condition
                    }
                }
            }

        }
////////////////////////////////////////////////////////////////////////////////////
        else if (command == "containing")
        {
         element2 >> myword;
         if (count != 2)   /// check that this command has the valid number of arguments
            {
                if (first)
                {
                    cout << "Incorrect number of arguments";
                    first = false;
                }
                else
                {
                    cout << endl << "Incorrect number of arguments";
                }
            }

            else  // the arguments number are correct
            {
                if (first)
                {
                    if (!alphalist.containing(myword, totalwordscount))
                    {
                        cout << "Word not found";
                            first = false;
                    }
                    else
                    {  
                        //nothing as the function already perforemed in the if condition
                        first = false;
                    }
                }
                else
                {
                    cout << endl;
                    if (!alphalist.containing(myword, totalwordscount))
                    {
                        cout <<"Word not found"; 
                    }
                    else
                    {
                        //nothing as the function already perforemed in the if condition
                    }
                }
            }
        }
////////////////////////////////////////////////////////////////////////////////////
        else if (command == "search")
        {
        element2 >> myword;
         if (count != 2)   /// check that this command has the valid number of arguments
            {
                if (first)
                {
                    cout << "Incorrect number of arguments";
                    first = false;
                }
                else
                {
                    cout << endl << "Incorrect number of arguments";
                }
            }

            else  // the arguments number are correct
            {
                if (first)
                {
                    if (!alphalist.search(myword, totalwordscount))
                    {
                        cout << "Word not found";
                            first = false;
                    }
                    else
                    {  
                        //nothing as the function already perforemed in the if condition
                        first = false;
                    }
                }
                else
                {
                    cout << endl;
                    if (!alphalist.search(myword, totalwordscount))
                    {
                        cout <<"Word not found"; 
                    }
                    else
                    {
                        //nothing as the function already perforemed in the if condition
                    }
                }
            }
        }
////////////////////////////////////////////////////////////////////////////////////
        else
        {
                if (first)
                {
                    cout << "Undefined command";
                    first = false;
                }
                else
                {
                    cout << endl<<"Undefined command";
                }
        }

  
    }
    return 0;
}


