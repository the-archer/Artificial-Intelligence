#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>


using namespace std;

bool traverse_log = true;
bool alpha_beta = false;
fstream fs;

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
void MiniMaxDecision(Board b, int player, int max_depth);
pair<int, Node*> MaxValue(Board b, int player, int depth, int max_depth, int prev_player, int prev_move, int alpha, int beta);
pair<int, Node*> MinValue(Board b, int player, int depth, int max_depth,int prev_player, int prev_move, int alpha, int beta);
void addTraverseLog(int player, int pit, int depth, int val, int alpha, int beta);


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
        //cout << pits_b[pit_count-1] - pits_t[1] << endl;
        return pits_b[pit_count-1] - pits_t[1];
    }
    else
    {

        //cout << pits_t[1] - pits_b[pit_count-1] << endl;
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



    }
    if(count1!=0 && count2!=0)
    {
        return false;
    }
    if(count1 == 0)
    {
        pits_t[1] += count2;
    }
    else if(count2 == 0)
    {
        pits_b[pit_count-1] += count1;
    }
    for(int i=2; i<pit_count-1; i++)
    {
        pits_b[i] = 0;
        pits_t[i] = 0;
    }
    //cout << "Game End" << endl;
    return true;
}

int Board::getPitCount()
{
    return pit_count;
}

void Board::printBoard(ofstream& outfile)
{
    //outfile << pit_count << endl;
    for(int i=2; i<pit_count-2; i++)
    {
        outfile << pits_t[i] <<  " " ;
    }
    outfile << pits_t[pit_count-2];
    outfile << endl;
    for(int i=2; i<pit_count-2; i++)
    {
        outfile << pits_b[i] <<  " " ;
    }
    outfile << pits_b[pit_count-2];
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
    return false;

}





int main(int argc,char *argv[])
{

    //Board b(5);
    //testFunction(b);
    //b.getBoard();
   // MoveTestModule();

    ifstream infile(argv[2]); // Change it to take input file name from command line -> IMPORTANT
    int algo, player, max_depth;
    infile >> algo;
    infile >> player;
    infile >> max_depth;
    //cout << "here" << endl;
    string line;
    int arr[15];
    infile.ignore(255, '\n');
    getline(infile, line);
    //cout << line << endl;
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
    if (algo == 1)
    {
        //greedy
        traverse_log = false;
        alpha_beta = false;
        MiniMaxDecision(b, player, 1);

    }
    else if(algo == 2)
    {
        traverse_log = true;
        alpha_beta = false;
        //fstream fs;
        fs.open("traverse_log.txt", ios_base::out); // NOTE: OPen file at the start to overwrite any previous logs and insert heading
        fs << "Node,Depth,Value" << endl;
        //fs.close();

        MiniMaxDecision(b, player, max_depth);
        fs.close();
    }
    else if(algo == 3)
    {
        traverse_log = true;
        alpha_beta = true;
        //fstream fs;
        fs.open("traverse_log.txt", ios_base::out); // NOTE: OPen file at the start to overwrite any previous logs and insert heading
        fs << "Node,Depth,Value,Alpha,Beta" << endl;
        //fs.close();

        MiniMaxDecision(b, player, max_depth);
        fs.close();
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

    bool ans = b.MakeMove(player, pit) ;
    cout << ans << endl;
    cout << "what" << endl;
    b.printBoard(outfile);

}

void MiniMaxDecision(Board b, int player, int max_depth)
{

    pair<int, Node*> res = MaxValue(b, player, 0, max_depth, 0, 0, INT_MIN, INT_MAX);
    Node* cur = res.second;
    ofstream outfile("next_state.txt");
    //cout << res.first << endl;
    while(cur!=NULL)
    {
        //cout << "Action" << cur->action << endl;
        if(cur->action!=0)
        {

            b.MakeMove(player, cur->action);
            //b.printBoard(outfile);
        }
        cur = cur->next;
    }
    b.EndGameTest();

    b.printBoard(outfile);


}

pair<int, Node*> MaxValue(Board b, int player, int depth, int max_depth, int prev_player, int prev_move, int alpha, int beta)
{
    int newdepth = depth;
    if (player!=prev_player)
    {
        newdepth++;
    }
    if(b.EndGameTest())
    {
        Node* node = new Node(0, 0);
        int val = b.Utility(player);
        addTraverseLog(prev_player, prev_move, depth, val, alpha, beta);
        return make_pair(val, node);
    }
    if(newdepth > max_depth)
    {
        Node* node = new Node(0, 0);
        int val = b.Utility(player);
        addTraverseLog(prev_player, prev_move, depth, val, alpha, beta);
        return make_pair(val, node);
    }
    int val = INT_MIN;
    pair<int, Node*> res;
    int action = 0;
    Node* future_actions;


    addTraverseLog(prev_player, prev_move, depth, val, alpha, beta);
    for(int i=2; i<(b.getPitCount()-1); i++)
    {
        if(b.getPit(player, i)!=0)
        {
            Board c = b;
            if(c.MakeMove(player, i))
            {
                res = MaxValue(c, player, newdepth, max_depth, player, i, alpha, beta);


            }
            else
            {
                res = MinValue(c, (player%2)+1, newdepth, max_depth, player, i, alpha, beta);
            }
            if(res.first > val)
            {
                val = res.first;
                action = i;
                future_actions = res.second;
            }
            if(alpha_beta)
            {
                if(val >= beta)
                {
                    addTraverseLog(prev_player, prev_move, depth, val, alpha, beta);
                    break;
                }
                if(val > alpha)
                {
                    alpha = val;
                }
            }
            addTraverseLog(prev_player, prev_move, depth, val, alpha, beta);

        }

    }
    //cout << val << endl;
    if(newdepth==1)
    {
        Node* node = new Node(val, action);
        node->next = future_actions;
        return make_pair(val, node);
    }
    return make_pair(val, res.second);
}

pair<int, Node*> MinValue(Board b, int player, int depth, int max_depth, int prev_player, int prev_move, int alpha, int beta)
{
    int newdepth = depth;

    if (player!=prev_player)
    {
        newdepth++;
    }


    if(b.EndGameTest())
    {
        Node* node = new Node(0, 0);
        int val = b.Utility((player%2)+1);
        addTraverseLog(prev_player, prev_move, depth, val, alpha, beta);
        return make_pair(val, node);
    }
    if(newdepth > max_depth)
    {
        Node* node = new Node(0, 0);
        int val = b.Utility((player%2)+1);
        addTraverseLog(prev_player, prev_move, depth, val, alpha, beta);
        return make_pair(val, node);
    }
    int val = INT_MAX;
    pair<int, Node*> res;

    addTraverseLog(prev_player, prev_move, depth, val, alpha, beta);


    for(int i=2; i<(b.getPitCount()-1); i++)
    {
        if(b.getPit(player, i)!=0)
        {
            Board c = b;

            if(c.MakeMove(player, i))
            {
                res = MinValue(c, player, newdepth, max_depth, player, i, alpha, beta);

            }
            else
            {
                res = MaxValue(c, (player%2)+1, newdepth, max_depth, player, i, alpha, beta);
            }
            if(res.first < val)
            {
                val = res.first;
            }
            if(alpha_beta)
            {
                if(val <= alpha)
                {
                    addTraverseLog(prev_player, prev_move, depth, val, alpha, beta);
                    break;
                }
                if(val < beta)
                {
                    beta = val;
                }
            }
            addTraverseLog(prev_player, prev_move, depth, val, alpha, beta);


        }

    }
    //cout << val << endl;
    return make_pair(val, res.second);
}

void addTraverseLog(int player, int pit, int depth, int val, int alpha, int beta)
{
    if(!traverse_log)
        return;
    //ofstream fs;
    //fs.open("traverse_log.txt", ios_base::app); // NOTE: OPen file at the start to overwrite any previous logs and insert heading

    //fs << "simrat " << endl;
    if(player==0)
    {
        fs << "root,";
    }
    else
    {
        if(player==1)
        {
            fs << "B";
        }
        else
        {
            fs << "A";
        }
        fs<<pit << "," ;
    }
    fs << depth << "," ;
    if(val==INT_MAX)
    {
        fs << "Infinity";

    }
    else if(val==INT_MIN)
    {
        fs << "-Infinity" ;
    }
    else
    {
        fs << val;
    }
    if(alpha_beta)
    {
        fs << ",";
        if(alpha==INT_MAX)
        {
            fs << "Infinity";

        }
        else if(alpha==INT_MIN)
        {
            fs << "-Infinity";
        }
        else
        {
            fs << alpha;
        }
        fs << ",";
        if(beta==INT_MAX)
        {
            fs << "Infinity" ;

        }
        else if(beta==INT_MIN)
        {
            fs << "-Infinity";
        }
        else
        {
            fs << beta;
        }
    }
    fs << endl;
    //fs.close();
    //cout << "here" << endl;
    return;


}
