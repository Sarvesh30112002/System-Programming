#include <bits/stdc++.h>
using namespace std;

int mdtIndex = 100;
int mntIndex = 10;

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
    string value;
    arguments(string macroname, int postion, string name){
        this->macroname = macroname;
        this->postion = postion;
        this->name = name;
    }
    void set(string value){
        this->value = value;
    }
};

void init(vector<macroname> &mnt, vector<macrodef> &mdt, vector<arguments> &args) {
    // Initialize Macro Name Table
    mnt.push_back(macroname(10, "ABC", 100));
    mnt.push_back(macroname(11, "XYZ", 103));

    // Initialize Macro Def Table
    mdt.push_back(macrodef(100, "load &a"));
    mdt.push_back(macrodef(101, "add &b"));
    mdt.push_back(macrodef(102, "mend"));
    mdt.push_back(macrodef(103, "load x"));
    mdt.push_back(macrodef(104, "add &a"));
    mdt.push_back(macrodef(105, "sub &b"));
    mdt.push_back(macrodef(106, "mult y"));
    mdt.push_back(macrodef(107, "store &c"));
    mdt.push_back(macrodef(108, "mend"));

    // Initialize Arguments List
    args.push_back(arguments("ABC", 1, "&a"));
    args.push_back(arguments("ABC", 2, "&b"));
    args.push_back(arguments("XYZ", 1, "&a"));
    args.push_back(arguments("XYZ", 2, "&b"));
    args.push_back(arguments("XYZ", 3, "&c"));
}

int mntFind(vector<macroname> &mnt, string mname) {
    for (int i = 0; i < mnt.size(); i++) {
        if (mnt[i].name == mname) {
            return i;
        }
    }
    return -1;
}

int mdtFind(vector<macrodef> &mdt, int index) {
    for (int i = 0; i < mdt.size(); i++) {
        if (mdt[i].index == index) {
            return i;
        }
    }
    return -1;
}

int argsFind(vector<arguments> &args, string mname, int pos) {
    for (int i = 0; i < args.size(); i++) {
        if (args[i].macroname == mname && args[i].postion == pos) {
            return i;
        }
    }
    return -1;
}

void Arguments(string line,string name,vector<arguments> &args)
{

    string para = "";
    int i = -1,pos = 1;
    do
    {
        i++;
        if (line[i] == ',' || line[i] == '\0')
        {
            string argname = para;
            int idx = argsFind(args, name, pos);
            args[idx].set(argname);
            para = "";
            pos++;
        }
        else
        {
            para += line[i];
        }
    } while (line[i] != '\0');

}

void pass2(ifstream &fin,ofstream &fout,vector<macroname> &mnt, vector<macrodef> &mdt, vector<arguments> &args)              
{
    string word;
    fin >> word;
    fout << word << "\n";
    while (fin >> word)
    {
        int idx = mntFind(mnt,word); 
        if (idx != -1)
        {
            streampos pos = fin.tellg();
            fin >> word;
            if (argsFind(args,mnt[idx].name,1) != -1){
                Arguments(word,mnt[idx].name,args);
            }else{
                fin.seekg(pos);
            }

            int index = mnt[idx].mdtIndex;
            index = mdtFind(mdt,index);
            int argspos = 1;
            do
            {
                string code = mdt[index].line;
                int pos = code.find("&");
                if (pos != string::npos)
                {
                    code.erase(code.begin() + pos , code.end());
                    code += args[argsFind(args, mnt[idx].name, argspos++)].value;
                }
                fout << code << "\n";
                index++;
            }while (mdt[index].line != "mend");
            fout << flush;
        }
        else if (word == "endp")
        {
            fout << word << "\n";
            break;
        }
        else
        {
            fout << word << " ";
            fin >> word;
            fout << word << "\n";
        }
        
    }
}

int main()
{
    string inputfile = "input.txt";
    string outputfile = "output.txt";

    ifstream fin;
    fin.open(inputfile);

    ofstream fout;
    fout.open(outputfile);

    vector<macroname> mnt;
    vector<macrodef> mdt;
    vector<arguments> argumentsList;

    init(mnt, mdt, argumentsList);
    fin.seekg(0);
    if (fin.is_open())
    {
        pass2(fin, fout ,mnt, mdt, argumentsList);
    }

    cout << "\nArguments List Array with Actual Value\n";
    cout << "Macroname Position Name Value\n";
    for (auto k : argumentsList)
    {
        cout << k.macroname << "\t    " << k.postion << "\t    " << k.name << "\t  " << k.value << "\n";
    }

    fin.close();
    return 0;
}