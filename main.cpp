#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const char *name = "dictionary.txt";

string getWord(const char *filename)
{
    vector<string> wordList;
    ifstream file(filename);

    if(file.is_open())
    {
        string word;
        while(file>>word)
        {
            wordList.push_back(word);
        }
    }

    file.close();
    if(wordList.size()>0) {
        int randomIdx=rand()%wordList.size();
        return wordList[randomIdx];
    }
    else return "";
}

int main()
{
    srand(time(0));
    cout<<getWord(name);
    return 0;
}
