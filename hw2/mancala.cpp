#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>


using namespace std;


struct Node
{
    int val;
    int action;
    Node* next;
    Node(int x, int y) : val(x), action(y), next(NULL) {}
};

class Board
{
public:
    void printBoard(ofstream& outfile);
    Board(int pit_count);

    Board(const Board &obj);
    bool MakeMove(int player, int pit);
    void setPit(int side, int pit, int val);
    int getPit(int side, int pit);
    int Utility(int player);
    bool EndGameTest();
    int getPitCount();

private:
    int pit_count;
    int *pits_t;
    int *pits_b;


};


void MoveTestModule();
int MaxValue(Board b, int player, int depth, int max_depth);
int MinValue(Board b, int player, int depth, int max_depth);

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

int Board::getPit(int side, int pit)
{
    if(side == 1)
    {
        return pits_b[pit];
    }
    else
    {
        return pits_t[pit];
    }
}

int Board::Utility(int player)
{
    if(player == 1)
    {
        return pits_b[pit_count-1] - pits_t[1];
    }
    else
    {
        return pits_t[1] - pits_b[pit_count-1];

    }
}

bool Board::EndGameTest()
{
    int count1 = 0;
    int count2 = 0;
    for(int i=2; i<pit_count-1; i++)
    {
        count2 += pits_t[i];
        count1 += pits_b[i];

        if(pits_t[i]!=0 || pits_b[i]!=0)
        {
            return false;

        }


    }
    if(count1 == 0)
    {
        pits_t[1] += count2;
    }
    if(count2 == 0)
    {
        pits_b[pit_count-1] += count1;
    }
    return true;
}

int Board::getPitCount()
{
    return pit_count;
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





int main()
{

    //Board b(5);
    //testFunction(b);
    //b.getBoard();
    //MoveTestModule();
    ifstream infile("input_2.txt"); // Change it to take input file name from command line -> IMPORTANT
    int algo, player, max_depth;
    infile >> algo;
    infile >> player;
    infile >> max_depth;
    cout << "here" << endl;
    string line;
    int arr[15];
    infile.ignore(255, '\n');
    getline(infile, line);
    cout << line << endl;
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
    ofstream outfile("output.txt");

    b.printBoard(outfile);
    if(algo == 2)
    {

    }

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

void MiniMaxDecision(Board b, int player, int max_depth)
{
    int val = INT_MIN;
    int res = 0;
    for(int i=2; i<(b.getPitCount()-1); i++)
    {
        if(b.getPit(player, i)!=0)
        {
            if(b.MakeMove(player, i))
            {
                res = MaxValue(b, player, 0, max_depth);

            }
            else
            {
                res = MinValue(b, (player%2)+1, 1, max_depth);
            }
            if(res > val)
            {
                val = res;
            }

        }
    }
}

pair<int, Node> MaxValue(Board b, int player, int depth, int max_depth)
{
    if(b.EndGameTest())
    {
        return b.Utility(player);
    }
    if(depth > max_depth)
    {
        return b.Utility(player);
    }
    int val = INT_MIN;
    int res = 0;
    int action = 0;
    for(int i=2; i<(b.getPitCount()-1); i++)
    {
        if(b.getPit(player, i)!=0)
        {
            if(b.MakeMove(player, i))
            {
                res = MaxValue(b, player, depth, max_depth);

            }
            else
            {
                res = MinValue(b, (player%2)+1, depth+1, max_depth);
            }
            if(res > val)
            {
                val = res;
                action = i;
            }

        }
    }
    return val;
}

pair<int, Node> MinValue(Board b, int player, int depth, int max_depth)
{
    if(b.EndGameTest())
    {
        return make_pair(b.Utility((player%2)+1), Node(0, 0));
    }
    if(depth > max_depth)
    {
        return make_pair(b.Utility((player%2)+1), Node(0, 0));
    }
    int val = INT_MAX;
    pair<int, Node> res;
    for(int i=2; i<(b.getPitCount()-1); i++)
    {
        if(b.getPit(player, i)!=0)
        {
            if(b.MakeMove(player, i))
            {
                res = MinValue(b, player, depth, max_depth);

            }
            else
            {
                res = MaxValue(b, (player%2)+1, depth+1, max_depth);
            }
            if(res < val)
            {
                val = res;
            }

        }
    }
    return val;
}
