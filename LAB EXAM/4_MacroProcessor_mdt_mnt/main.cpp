#include <bits/stdc++.h>
using namespace std;

struct macroname
{
    int index;
    string name;
    int mdtIndex;
    macroname(int index,string name,int mdtIndex) {
        this->index = index;
        this->name = name;
        this->mdtIndex = mdtIndex;
    }
};

struct macrodef
{
    int index;
    string code;
    macrodef(int index, string code) {
        this->index = index;
        this->code = code;
    }
};

int mdtIndex = 100;
int mntIndex = 10;

void pass1(ifstream &fin, vector<macroname> &mnt, vector<macrodef> &mdt)
{
    string word;
    while (fin >> word)
    {
        if (word == "macro")
        {
            fin >> word;
            // To Push in MacroName Table
            macroname mstruct = macroname(mntIndex++,word,mdtIndex);
            mnt.push_back(mstruct);

            do
            {
                //To Push in Macro Definition Table
                fin >> word;
                string code = word;
                if (word != "mend")
                {
                    fin >> word;
                    code += " " + word;
                } 
                macrodef mdef = macrodef(mdtIndex++,code);
                mdt.push_back(mdef);

            } while (word != "mend");
        }
    }
}

int main()
{
    string inputfile = "input.txt";
    ifstream fin;
    fin.open(inputfile);

    vector<macroname> mnt;
    vector<macrodef> mdt;

    if (fin.is_open())
    {
        pass1(fin, mnt, mdt);
    }
    cout << "Index\tMacro\tMDTIndex\n";
    for (auto i : mnt)
    {
        cout << i.index << "\t" << i.name << "\t" << i.mdtIndex << "\n";
    }
    cout << "\nIndex\tCode\n";
    for (auto j : mdt)
    {
        cout << j.index << "\t" << j.code << "\n";
    }
    cout << endl;

    fin.close();
    return 0;
}