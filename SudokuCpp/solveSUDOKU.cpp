#include <bits/stdc++.h>
#include<fstream>

using namespace std;

#define N 9

void print(int arr[N][N])
{   
	cout<< endl <<"The solved Sudoku is:" << endl;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << arr[i][j] << " ";
			cout << endl;
	}
}

bool isSafe(int Box[N][N], int row, int col, int num)
{
	
	//checks row
	for (int x = 0; x <= 8; x++)
		if (Box[row][x] == num)
			return false;

	//checks column
	for (int x = 0; x <= 8; x++)
		if (Box[x][col] == num)
			return false;

	//checks 3*3 grid
	int startRow = row - row % 3;
	int startCol = col - col % 3;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (Box[i + startRow][j + startCol] == num)
				return false;

	return true;
}


bool solveSudoku(int Box[N][N], int row, int col)
{
	//check if reached 8th row and 9th column
	if (row == N - 1 && col == N)
		return true;

	//next row jump, if column is 9th
	if (col == N) {
		row++;
		col = 0;
	}

	//if non-empty cell go to next column
	if (Box[row][col] > 0)
		return solveSudoku(Box, row, col + 1);

	//start
	for (int num = 1; num <= N; num++)
	{
		
		// Check if it is safe to place the num (1-9)
		if (isSafe(Box, row, col, num))
		{
		/* If safe assigning the num in the current (row,col) */
			Box[row][col] = num;
		
			// Checking for next possibility with next column
			if (solveSudoku(Box, row, col + 1))
				return true;
		}
	
		// Removing the assigned num ,since our assumption was wrong, inserting new num value
		// Backtrack
		Box[row][col] = 0;
	}
	return false;
}

void ReadBoxValues(){

	int Box[N][N];
	int Value;

	cout<<"\nEnter the value when asked.\n";

	for(int row=0 ; row < N ; row++){
		for(int col=0 ; col < N ; col++)
		{
			cout<<"Enter value for cell ["<<row+1<<"]["<<col+1<<"] -->";
			cin>>Value;

			if(!(Value>=0 && Value<=9)){ 
                while(true){

                    cout<<"Wrong value! Try again.\n";
                    cout<<"Enter value for cell ["<<row+1<<"]["<<col+1<<"] --> ";
                    cin>>Value;

                    if(Value>=1 && Value<=9) break;
                }
            }	
			Box[row][col]=Value;
		}
		cout<<"<------------>\n";
	}
		
	if (solveSudoku(Box, 0, 0))
		print(Box);
	else
		cout << "No solution exists for given Sudoku"<< endl;

}

void ReadBoxValuesFile(){

	int Box[N][N];
		
	int rowVal, colVal;
	char filename[30];

	ifstream file;
	
	cout<<"\nEnter the name of the file which contains the puzzle --> "<<endl;
	cin>>filename;

	file.open(filename,ios::in);

	for(rowVal=0; rowVal<9; rowVal++){
		for(colVal=0; colVal<9; colVal++){

			int Value;

			file>>Value;
			cout<<Value<<" ";

			Box[rowVal][colVal]=Value;

			if(file.eof()) break;
		}
		cout<<endl;
	}
	file.close();

	if (solveSudoku(Box, 0, 0))
		print(Box);
	else
		cout << "No solution exists for given Sudoku"<< endl;
}



int mainMenu(){
	cout<<"\n";
    cout<<"\t The Sudoku Solver\n";
    cout<<"\n\n";

    cout<<"Welcome to the Sudoku Solver!\n";
    cout<<"To start, you will have to input the puzzle into this program.\n\n";
    cout<<"You can:\n";
    cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
    cout<<"\t2. Input the puzzle by entering file location. (Enter 2)\n";
    cout<<"\t3. Press any other number to exit.\n"; 

    int opt;
    cin>>opt;

    if(opt==1) ReadBoxValues();
    else if(opt==2) ReadBoxValuesFile();
    else{
    	cout<<"\nExit confirmed";
    	return 0;
    }
}

int main()
{
	mainMenu();
	return 0;	
}
