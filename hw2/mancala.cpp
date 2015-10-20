#include<iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void MoveTestModule();


class Board
{
public:
    void printBoard(ofstream& outfile);
    Board(int pit_count);
    void modify();
    Board(const Board &obj);
    bool MakeMove(int player, int pit);
    void setPit(int side, int pit, int val);

private:
    int pit_count;
    int *pits_t;
    int *pits_b;


};

Board::Board(const Board &obj)
{
    pit_count = obj.pit_count;
    pits_t = new int[pit_count];
    pits_b = new int[pit_count];
    for(int i=0; i<pit_count; i++)
    {

        pits_t[i] = obj.pits_t[i];
        pits_b[i] = obj.pits_b[i];
    }
}


Board::Board(int p)
{
    pit_count = p;
    pits_t = new int[pit_count];
    pits_b = new int[pit_count];
    for(int i=0; i<pit_count; i++)
    {
        pits_t[i] = 0;
        pits_b[i] = 0;

    }
}

void Board::modify()
{
    //pits[1] = 20;
}

void Board::setPit(int side, int pit, int val)
{
    if(side == 1)
    {
        pits_b[pit] = val;
    }
    else
    {
        pits_t[pit] = val;
    }
}

void Board::printBoard(ofstream& outfile)
{
    outfile << pit_count << endl;
    for(int i=2; i<pit_count-1; i++)
    {
        outfile << pits_t[i] <<  " " ;
    }
    outfile << endl;
    for(int i=2; i<pit_count-1; i++)
    {
        outfile << pits_b[i] <<  " " ;
    }
    outfile << endl;
    outfile << pits_t[1] << endl;
    outfile << pits_b[pit_count-1] << endl;

}

bool Board::MakeMove(int player, int pit)
{
    int stones = 0;
    int lastpit = pit;
    if(player == 1)
    {
        stones = pits_b[pit];
        pits_b[pit] = 0;

    }
    else
    {
        stones = pits_t[pit];
        pits_t[pit] = 0;

    }
    int curside = player;
    int curpit = 0;
    while (stones > 0)
    {
        if(curside == 1)
        {
            curpit = lastpit + 1;

            if(curpit == (pit_count-1))
            {
                if(player==1)
                {
                    stones--;
                    pits_b[curpit]++;
                    lastpit = curpit;
                    curside = 2;
                }
                else
                {
                    lastpit = curpit;
                    curside = 2;
                    continue;
                }
            }
            else
            {
                stones--;
                pits_b[curpit]++;
                lastpit = curpit;


            }

        }
        else
        {
            curpit = lastpit - 1;

            if(curpit == 1)
            {
                if(player==2)
                {
                    stones--;
                    pits_t[curpit]++;
                    lastpit = curpit;
                    curside = 1;
                }
                else
                {
                    lastpit = curpit;
                    curside = 1;
                    continue;
                }
            }
            else
            {
                stones--;
                pits_t[curpit]++;
                lastpit = curpit;


            }

        }
    }

    if(player==1)
    {
        if(lastpit==(pit_count-1))
        {
            return true;
        }
        else if(curside==1 and pits_b[lastpit]==1)
        {
            pits_b[pit_count-1] += pits_t[lastpit];
            pits_t[lastpit] = 0;
            pits_b[pit_count-1]++;
            pits_b[lastpit] = 0;
            return false;
        }
    }
    else
    {
        if(lastpit==1)
        {
            return true;
        }
        else if(curside==2 and pits_t[lastpit]==1)
        {
            pits_t[1] += pits_b[lastpit];
            pits_b[lastpit] = 0;
            pits_t[1]++;
            pits_t[lastpit] = 0;
            return false;
        }
    }

}



void testFunction(Board b)
{
    b.modify();
    //b.getBoard();

}


int main()
{

    //Board b(5);
    //testFunction(b);
    //b.getBoard();
    MoveTestModule();
    return 0;
}

void MoveTestModule()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");


    string line;
    int arr[15];
    getline(infile, line);
    istringstream iss(line);
    int n;
    int i = 0;
    while (iss >> n)
    {
        arr[i] = n;
        i++;
    }
    Board b(i+3);
    for(int j=0; j<i; j++)
    {
            b.setPit(2, j+2, arr[j]);
    }
    getline(infile, line);
    istringstream iss2(line);
    int j = 0;
    while(iss2 >> n)
    {
        //cout << n << endl;
        b.setPit(1, j+2, n);
        j++;
    }
    infile >> n;
    b.setPit(2,1,n);
    infile >> n;
    b.setPit(1, i+2, n);
    int player = 0;
    int pit = 0;
    b.printBoard(outfile);

    infile >> player;
    infile >> pit;
    cout << b.MakeMove(player, pit) << endl;
    b.printBoard(outfile);

}
