#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const char *name = "dictionary.txt";

struct Wordle
{
    string input; string answer;
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


    void checkWord(string input, string answer)
    {
        int check=0;
        for(int i=0; i<5; i++){
            if(answer[i]==input[i]) {
                cout<<"Letter "<<input[i]<<" is in right position\n";
                check++;
            }
            else if(answer.find(input[i])!=string::npos) {
                cout<<"Letter "<<input[i]<<" is in wrong position\n";
            }
            else {
                cout<<"Letter "<<input[i]<<" is not in the word\n";
            }
        }
        if(check==5) cout<<"Congratulations\n";
    }
};


int main()
{
    srand(time(0));
    Wordle w;
    w.answer=w.getWord(name);
    int cnt=0, maxguess=5;
    while(cnt<maxguess) {
        cin>>w.input;
        w.checkWord(w.input, w.answer);
        cnt++;
    }
    cout<<"The correct word was "<<w.answer;
    return 0;
}
