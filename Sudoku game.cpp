#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <time.h>
using namespace std;
//  ri is random input string put when enter is expected so that other inputs dont get jumbled
string ri;
//  function to copy one sudoku to another for functionality
void copy(int b[9][9],int a[9][9])
{
	int i, j;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			b[i][j]= a[i][j];
		}
	}
}
class Sudoku
{
	private:
		int grid[9][9],sol[9][9];
		int n;
		vector < vector <int> > pos;
	public:
		Sudoku(int n);
		void display();
		void display(int ad[9][9]);
		bool checkpos(int x,int y);
		int check(int ac[9][9],int num,int x,int y);
		bool fill(int a[9][9],bool disp);
		bool unique(int grid[9][9]);
		void generate_solution();
		void generate_puzzle();
		int branchDifficultyScore();
		int calculateDifficulty();
		void backtrack();
		int user();
		
};
Sudoku :: Sudoku(int n)
{
	this->n = n;
}
// display function is used to display the grid formed and the other function is used to diasplaya ny grid
void Sudoku :: display()
{
	display(this->grid);
}
//  display function to display the given 9X9 array
void Sudoku :: display(int ad[9][9])
{
	system("cls");
	int i, j;
	cout<<"  Y -->"<<endl;
	cout<<"X    __ __ __  __ __ __  __ __ __  \n";
	for(i = 0; i < 9; i++)
	{	
		if(!i)
			cout<<"|  ||";
		else
			cout<<"   ||";
		for(j=0;j<9;j++)
		{	
			if(ad[i][j]!=0)
				cout<<ad[i][j]<<" |";
			else if(ad[i][j]==0)
				cout<<"  |";
			if((j+1)%3 == 0) 
				cout<<"|";
		}
		if(!i)
			cout<<"\nv  ||";
		else
			cout<<"\n   ||";
		for(j=0;j<9;j++)
		{	
			if((j+1)%3 == 0 && (i+1)%3)
				cout<<"--||";
			else if((j+1)%3 == 0)
				cout<<"__||";
			else if((i+1)%3)
				cout<<"--|";
			else
				cout<<"__|";			
		}
		cout<<endl;
	}
}
bool Sudoku::checkpos(int x,int y)
{
	int i;
	for(i = 0; i < this->pos.size(); i++)
	{
		if(x == this->pos[i][0] && y == this->pos[i][1])
			return false;
	}
	return true;
}
//  funciton checks if the number entered is neither in row,column nor grid
int Sudoku :: check(int ac[9][9],int num,int x,int y)
{
	int i, j, p, q;
	if(num==0)
	{
		return(1);
	}
	for(i = 0; i < 9; i++)
	{
		if(num==ac[x][i] || num==ac[i][y])
		{
			return(0);
		}
	}
//  dividng by 3 return int => 0,1,2 therefor multiplying by 3 gives the start of the three grids
	p = ((x)/3) * 3;
	q = ((y)/3) * 3;
	for(i = p; i < p+3; i++)
		{
			for(j = q; j < q+3; j++)
			{
				if(num==ac[i][j])
					return(0);
			}
		}
	return(1);
}
// function which uses backtracking to solve a given sudoku puzzle
// takes in parameter disp which determines if the steps of backtrakcinjg will be displayed  or 
// if the final solutoion will just be shown or updated
// disp = false is faster
bool Sudoku :: fill(int a[9][9],bool disp)
{
	int i, j, k;
	for	(i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if(a[i][j] == 0 )
			{	
				for (k = 1; k <= 9; k++)
				{
					if(check(a, k, i, j))
					{
						a[i][j]=k;
						if(disp)
						display(a);
						if(fill(a,disp))
							return true;
						a[i][j]=0;
					}
				}
				return false;
			}
		}
	}
	return true;
}
// checks whether the give sudoku puzzle has unique solution or not
// returns false if more than 1 solutions exist
bool Sudoku :: unique(int grid[9][9])
{
//	c stores solution of a so it does not put a value in any square that already has a solution
//  other solutions with same value in a place will be found by checking the values that are different
//  b stores a copy in which insertion is done and solutions are checked if they exist because arrays passed in functions are updated automatically
	int c[9][9];
	int b[9][9];
	copy(b,grid);
	copy(c,grid);
	if(!fill(c,false))
	return false;
	int i,j,k,count = 0;
	for	(i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if(b[i][j] == 0 )
			{	
				for (k = 1; k <= 9; k++)
				{
					if(!check(grid, k, i, j) || c[i][j] == k)
						continue;
					b[i][j] = k;
					if(fill(b,false))
						return false;
					copy(b,grid);
				}
			}
		}
	}
	return true;
}
// generate function generates a sudoku puzzle with 33 digits which has a unique solution
// 33 becuase i fount 33 to be comparitively faster to form
// it then updates the array passes with the solutoion of the 33 digit sudoku puzzle formed
void Sudoku :: generate_solution()
{
	srand(time(0));
	int i, j, x, y, num;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			this->grid[i][j] = 0;
		}
	}
	bool unsolvable;
	// using b to find correct solution and then storing it in q
	int b[9][9];
	while(true)
	{
		copy(b, grid);
		unsolvable = false;
		for(i=0; i < 33; i++)
		{
			// runs until it finds an empty cell
			while(true)
			{
				// finds an empty cell
				x = rand() % 9;
				y = rand() % 9;
				if(b[x][y] == 0)
					break;
			}
			int c = 0;
			while(true){
				// finds if any value can be filled in empty cell
				num = (rand() % 9) + 1;
				if(check(b,num,x,y))
				{
					break;
				}
				// condition to check if its unsolvable
				// if over 30 iteration no num fits => cannot fill that position
				// 97.07% chance each number will be tried in 30 iterations
				// if no number can be filled => unsolvable
				// and set unsolvable = true
				c++;
				if(c > 30)
				{
					unsolvable = true;
					break;
				}
			}
			// if unsolvable => breaks
			if(unsolvable)
				break;
			b[x][y] = num;
		}
		// if unsolvable puzzle is set to 0s
		if(unsolvable)
			continue;
		// if puzzle returned can be solved and has unique solution it updates question to puzzle
		if(unique(b))
			break;
	}
	copy(grid,b);
	// solve the formed ques
	fill(grid,false);
}
// this generates a puzzle from random solution formed by generate_solution
void Sudoku :: generate_puzzle()
{
	system("cls");
	srand(time(0));
	// b and c are copies of grid
	// b is used to set single digit to 0 and check whether it has unique solution
	// if it does changes are made to c
	// when loop is over it sets those changes to grid
	int b[9][9],c[9][9];
	bool solvable = false;
	generate_solution();
	copy(this->sol,this->grid);
	int i,j,x,y;
	while(true){
		copy(c,this->grid);
		for(i = 0;i < (81-this->n) ;i++)
		{
			system("cls");
			cout<<"Please wait Generating Puzzle";
			for(int j = 0; j < i%4; j++)
			{
				cout<<".";
			}
			int count = 0;
			while(true)
			{
				copy(b,c);
				x = rand() % 9;
				y = rand() % 9;
				if(b[x][y] == 0)
				{
					continue;
				}	
				b[x][y] = 0;
				if(unique(b)){
					solvable = true;
					break;
				}
				else{
					copy(b,this->grid);
				}
				count++;
				if(count>40)
				{
					solvable = false;
					break;
				}
			}
			if(!solvable)
				break;
			c[x][y]=0;
		}
		if(solvable)
			break;
	}

	copy(this->grid,b);
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			if(this->grid[i][j] != 0)
			{
				vector<int> pair {i,j};
				this->pos.push_back(pair);
			}
		}
	}
	system("cls");
}
// calculates branch difficult score by finding cell with least number of vlaues to be filled
// and adding the square of that (value-1) and filing that cell and moving to next
int Sudoku::branchDifficultyScore()
{
    int emptyPositions = -1;
    int tempGrid[9][9];
	int sum=0;

	copy(tempGrid,this->grid);

    while(emptyPositions!=0)
	{
    	vector<vector<int> > empty;
    	for(int i=0;i<81;i++)
		{
        	if(tempGrid[(i/9)][(i%9)] == 0)
			{
       	  		vector<int> temp;
	  			temp.push_back(i);
	  			for(int num=1;num<=9;num++)
				{
				    if(check(tempGrid,num,i/9,i%9))
					{
			    	  	temp.push_back(num);
					}
				}
	  		empty.push_back(temp);
    	}
    }
    // returns 0 if no places are empty
	if(empty.size() == 0)
	{ 
		return sum;
	} 
    int minIndex = 0;

	    int check = empty.size();
	    for(int i=0;i<check;i++)
		{
	    	if(empty[i].size() < empty[minIndex].size())
				minIndex = i;
	    }

	    int branchFactor=empty[minIndex].size();
	    int rowIndex = empty[minIndex][0]/9;
	    int colIndex = empty[minIndex][0]%9;
	    tempGrid[rowIndex][colIndex] = this->sol[rowIndex][colIndex];
	    sum = sum + ((branchFactor-2) * (branchFactor-2)) ;
	    emptyPositions = empty.size() - 1;
	}

	return sum;
}
// calls branch diff score which returns sum of square of all min possible values when >1 and adds number of empty cells to it
int Sudoku::calculateDifficulty()
{
    int B = branchDifficultyScore();
    int emptyCells = 0;
    for(int i=0;i<9;i++)
    {
		for(int j=0;j<9;j++)
		{
			if(this->grid[i][j] == 0)
				emptyCells++;
		}
	}
	return B*100 + emptyCells;
}
void Sudoku::backtrack()
{
	fill(this->grid,true);
}
int Sudoku :: user(){
	int i, j, guess=0, x, y, num;
	// taking input in string so program doesnt throw error when a wrong input is made and continues
	string x_s,y_s,num_s;
	for(i=0; i<81-this->n; i++)
	{
		while(true)
		{
			while(true){
				system("cls");
				display();
				cout<<"Enter Position:\n";
				cout<<"Enter x : ";
				getline(cin,x_s);
				x = (int)x_s[0] - '0';
				if(x_s.size()>1 || x>9 || x<1)
				{
					cout<<"Enter valid cell location\nPress Enter to Continue\n";
					getline(cin,ri);
					continue;
				}
				cout<<"Enter y : ";
				getline(cin,y_s);
				y = (int)y_s[0] - '0';
				if(y_s.size()>1 || y>9 || y<1)
				{
					cout<<"Enter valid cell location\nPress Enter to Continue\n";
					getline(cin,ri);
					continue;
				}
				x--,y--;
				if(checkpos(x,y))
				break;
				cout<<"Cannot change question\n";
				getline(cin,ri);
			}
			system("cls");
			display();
			cout<<"( Enter 0 to go back to cell selection or delete input )\nEnter Number to fill at ("<<x+1<<","<<y+1<<") : ";
			getline(cin,num_s); 
			num = (int)num_s[0] - '0';
			if(num_s.size() > 1 || num > 9 || num < 0){
				cout<<"Enter number between 0 and 9\n";
				getline(cin,ri);
				continue;
			}
			if(num == 0 || num == this->sol[x][y])
			{
				this->grid[x][y] = num;
				break;
			}
			cout<<"Wrong Number\n";
			guess++;
			cout<<"Guesses left before solution shown : "<<3-guess<<endl;
			system("pause");
			if(guess == 3){
				display(this->sol);
				cout<<"Game Over\n";
				return 0;
			}
		}
	}
	display();
	cout<<"You win\n";
	return 0;
}
// main menu returns the number of digits the question will have and the choice made
void main_menu(int result[2])
{
	srand(time(0));
	int mod,digit,choice;
	system("cls");
	string inp = "";
	while(true){
		system("cls");
		cout<<"Choose Difficulty - \n";
		cout<<"1. Easy\n";
		cout<<"2. Medium\n";
		cout<<"3. Hard (takes a good amount to generate)\n";
		cout<<"4. Backtracking showcase on randomly generated sudoku\n";
		cout<<"Type quit to exit\n";
		cout<<"Enter choice : ";
		getline(cin,inp);
		if(inp=="q" || inp == "Quit" || inp == "quit"|| inp=="QUIT")
		{
			system("cls");
			cout<<"Exiting\n";
			exit(0);
		}
		choice = (int)inp[0] - '0';
		if(inp == "Easy"|| inp == "easy" || inp=="EASY" || choice == 1)
		{
			mod = 10;
			digit = 33;
			choice = 1;
		}
		if(inp == "Medium"|| inp == "medium" || inp=="MEDIUM" || choice == 2)
		{
			mod = 8;
			digit = 27;
			choice = 2;
		}
		if(inp == "Hard"|| inp == "hard" || inp=="HARD" || choice == 3)
		{
			mod = 4;
			digit =	23;
			choice = 3;
		}
		if(choice == 4){
			mod = 1;
			digit = 41;	
		}
		if(choice>4 || choice<1){
			cout<<"Invalid Choice Input Again\n";
			system("pause");
			continue;
		}
		break;
	}
	digit += rand()%mod;
	result[0] = digit;
	result[1] = choice;
}

int main()
{
	cout<<"\n\n\n\t\t\t\t\t      Welcome to Sudoku Puzzle\n";
	cout<<"\n\t\t\t\t\t\tPress Enter To Play\n";
	getline(cin,ri);
	while(true){
		int n[2],difficulty,i,j,re;
		main_menu(n);
		Sudoku ques(n[0]);
		
		while(true){
			ques.generate_puzzle();
			int min_score = 0;
			if(n[1]==1 || n[1]==4)
				min_score = 0;
			else if(n[1]==2)
				min_score = 180;
			else
				min_score = 500;
			difficulty = ques.calculateDifficulty();
			if(difficulty >= min_score)
				break;
		}
		ques.display();
		cout<<"Difficulty Score = "<<difficulty<<endl;
		system("pause");
		
		if (n[1] == 4)
			ques.backtrack();
		else
			ques.user();
		system("pause");
		system("cls");
		cout<<"Restart?\n";
		cout<<"1. Yes\n2. No\n";
		cin>>re;
		getline(cin,ri);
		if(re == 1){
			continue;
		}
		break;
	}
	return 0;
}
