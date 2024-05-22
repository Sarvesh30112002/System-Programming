#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    int memptr = 0;
    int memory;
    int N;

    cout << "Enter the memory size (in bytes): ";
    cin >> memory;
    cout << endl;

    cout << "Enter no. of files: ";
    cin >> N;
    cout << endl;

    while (N--)
    {
        // Get the file path and check the size
        string file_path;
        cout << "Enter the file path: ";
        cin >> file_path;
        cout << endl;

        ifstream file(file_path, ios::binary | ios::ate);

        // Check if the file was successfully opened
        if (!file.is_open())
        {
            cout << "Error: Unable to open file." << endl;
            continue; // Skip to the next iteration of the loop
        }

        long file_size = file.tellg();
        file.close();

        // If file is empty then continue to next file
        if (file_size == 0)
        {
            cout << "File is empty" << endl;
            continue;
        }

        cout << "File size is: " << file_size << " bytes" << endl;

        if (file_size <= memory - memptr)
        {
            cout << "File is loaded in memory at location " << memptr << " to " << memptr + file_size << endl;
            memptr += file_size;
        }
        else
        {
            cout << "Memory is full" << endl;
            break;
        }
    }

    return 0;
}