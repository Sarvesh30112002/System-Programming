#include <bits/stdc++.h>
using namespace std;

struct macroname
{
    int index;
    string name;
    int mdtIndex;
    macroname(int index,string name, int mdtIndex){
        this->index = index;
        this->name = name;
        this->mdtIndex = mdtIndex;
    }
};

struct macrodef
{
    int index;
    string line;
    macrodef(int index, string line){
        this->index = index;
        this->line = line;
    }
};

struct arguments
{
    string macroname;
    int postion;
    string name;
    arguments(string macroname, int postion, string name){
        this->macroname = macroname;
        this->postion = postion;
        this->name = name;
    }
};

int mdtIndex = 100;
int mntIndex = 10;

void Extract_Arguments(string line,string name,vector<arguments> &args)
{

    string para = "";
    int i = -1,pos = 1;
    do
    {
        i++;
        if (line[i] == ',' || line[i] == '\0')
        {
            string argname = para;
            args.push_back(arguments(name, pos, argname));
            para = "";
            pos++;
        }
        else
        {
            para += line[i];
        }
    } while (line[i] != '\0');

}


void pass1(ifstream &fin, vector<macroname> &mnt, vector<macrodef> &mdt, vector<arguments> &args)
{
    string word;
    while (fin >> word)
    {

        if (word == "macro")
        {
            fin >> word;

            string mname = word;
            macroname *mstruct = new macroname(mntIndex++,mname,mdtIndex);
            mnt.push_back(*mstruct);

            streampos pos = fin.tellg();
            fin >> word;
            if (word[0]=='&'){
                Extract_Arguments(word,mname,args);
            }else{
                fin.seekg(pos);
            }

            do
            {
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
    vector<arguments> argumentsList;

    fin.seekg(0);
    if (fin.is_open())
    {
        pass1(fin, mnt, mdt, argumentsList);
    }

    cout << "\nMacro Name Table\n";
    cout << "Index\tMacro\tMDTIndex\n";
    for (auto i : mnt)
    {
        cout << i.index << "\t" << i.name << "\t" << i.mdtIndex << "\n";
    }
    cout << endl;
    cout << "Macro Def Table\n";
    cout << "Index\tCode\n";
    for (auto j : mdt)
    {
        cout << j.index << "\t" << j.line << "\n";
    }
    cout << endl;

    cout << "Arguments List\n";
    cout << "Macroname Position Name\n";
    for (auto k : argumentsList)
    {
        cout << k.macroname << "\t  " << k.postion << "\t  " << k.name << "\n";
    }

    fin.close();
    return 0;
}