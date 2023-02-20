#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

class OS
{
private:
    char M[100][4];
    char IR[4];
    int SI;
    int IC;
    bool C;
    char R[4];
    char buffer[40];

public:
    void init();
    void load();
    void executeUserProg();
    void MOS();

    fstream fin, fout;
};

void OS::init()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = 0;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        IR[i] = R[i] = 0;
    }

    C = false;
}

void OS::MOS()
{
    if (SI == 1)
    {
        for (int i = 0; i < 40; i++)
        {
            buffer[i] = '\0';
        }
        fin.getline(buffer, 40);

        int k = 0;
        int i = IR[2] - 48;
        i = i * 10;

        for (int r = 0; r < 10; ++r)
        {
            for (int j = 0; j < 4; ++j)
            {
                M[i][j] = buffer[k];
                k++;
            }
            if (k == 10)
            {
                break;
            }
            i++;
        }
    }

    else if (SI == 2)
    {
        for (int i = 0; i <= 39; i++)
            buffer[i] = '\0';

        int k = 0;
        int i = IR[2] - 48;
        i = i * 10;

        for (int l = 0; l < 10; ++l)
        {
            for (int j = 0; j < 4; ++j)
            {
                buffer[k] = M[i][j];
                fout << buffer[k];

                k++;
            }
            if (k == 40)
            {
                break;
            }
            i++;
        }

        fout << "\n";
    }
    else if (SI == 3)
    {

        fout << "\n";
        fout << "\n";
    }
}

void OS::executeUserProg()
{
    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            IR[i] = M[IC][i];
        }
        IC++;

        if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            MOS();
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            MOS();
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            int i = IR[2] - 48;
            i = i * 10 + (IR[3] - 48);
            for (int j = 0; j < 4; j++)
            {
                R[j] = M[i][j];
            }
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            int i = IR[2] - 48;
            i = i * 10 + (IR[3] - 48);

            for (int j = 0; j < 4; j++)
                M[i][j] = R[j];
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            int i = IR[2] - 48;
            i = i * 10 + (IR[3] - 48);

            char arr[4];

            for (int j = 0; j < 4; j++)
            {
                arr[j] = M[i][j];
            }

            int res = strcmp(arr, R);
            if (res == 0)
            {
                C = true;
            }
            else
            {
                C = false;
            }
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            if (C == true)
            {
                int i = IR[2] - 48;
                i = i * 10 + (IR[3] - 48);

                IC = i;
            }
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            MOS();
            break;
        }
    }
}

void OS::load()
{
    int x = 0;
    do
    {
        for (int i = 0; i <= 39; i++)
            buffer[i] = '\0';
        fin.getline(buffer, 40);

        if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
        {
            init();
            cout << "Registers Initialized" << endl;
        }
        else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
        {
            IC = 0;
            executeUserProg();
            cout << "Job Executed successfully" << endl;
        }
        else if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
        {
            x = 0;
            continue;
        }
        else
        {
            int k = 0;

            for (; x < 100; ++x)
            {
                for (int j = 0; j < 4; ++j)
                {
                    M[x][j] = buffer[k];
                    if (buffer[k] == 'H')
                    {
                        M[x][++j] = ' ';
                        M[x][++j] = ' ';
                        M[x][++j] = ' ';
                    }
                    k++;
                }

                if (k == 40 || buffer[k] == ' ' || buffer[k] == '\n')
                {
                    break;
                }
            }
        }
    } while (!fin.eof());
}

int main()
{
    OS os;
    os.fin.open("input.txt", ios::in);
    os.fout.open("output.txt", ios::out);

    if (!os.fin)
    {
        cout << "Error Occured : File Does not Exists !!!" << endl;
    }
    else
    {
        os.load();
    }

    return 0;
}