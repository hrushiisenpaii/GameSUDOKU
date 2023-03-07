#include<bits/stdc++.h>
#include<fstream>

using namespace std;

class SudokuBox{

	int sudokuBox[9][9];

	public:SudokuBox(){
		menu();
	}
	
	private:void menu(){

	        cout<<"\n";
	        cout<<"\t The Sudoku Validator\n";
	        cout<<"\n\n";

	        cout<<"Welcome to the Sudoku Validator!\n";
	        cout<<"To start, you will have to input the puzzle into this program.\n\n";
	        cout<<"You can:\n";
	        cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
	        cout<<"\t2. Input the puzzle by entering file location. (Enter 2)\n";
	        cout<<"\t3. Press any other number to exit.\n";
	        
	        int opt;
	        cin>>opt;

	        if(opt == 1){
	        	readBoxValues();
	        } 
	        else if(opt ==2){
	        	readBoxValuesFile();
	        }
	        else {
	        	cout<<"Wrong option";
	        }
        }

    private:void readBoxValues(){

        	cout<<"\nEnter the value when asked.\n";

			int rowVal, colVal;

        for(rowVal=0; rowVal<9; rowVal++){ 
            for(colVal=0; colVal<9; colVal++){

                int Value;

                cout<<"Enter value for cell ["<<rowVal+1<<"]["<<colVal+1<<"] --> ";
                cin>>Value;

                if(!(Value>=1 && Value<=9)){ 
                    while(true){

                        cout<<"Wrong value! Try again.\n";
                        cout<<"Enter value for cell ["<<rowVal+1<<"]["<<colVal+1<<"] --> ";
                        cin>>Value;

                        if(Value>=1 && Value<=9) break;
                    }
                }	

            sudokuBox[rowVal][colVal]=Value;

            }
            	cout<<"-------\n"; 
    		}
        }

    private:void readBoxValuesFile(){
		
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

			sudokuBox[rowVal][colVal]=Value;

			if(file.eof()) break;
			}
			cout<<endl;
		}
		file.close();

	}

	public:int getValue(int row, int col){
		return sudokuBox[row][col];
	}

};

class SudokuValidator{

	SudokuBox Box;
	
	public:SudokuValidator(){
		validateBox();		
	}

	private:void validateBox(){
		if(ValidRows()){
			if(ValidColumns()){
				if(ValidTTS()){
					cout<<"\nYour puzzle is valid!\n\n";
				}
				else cout<<"\nYour puzzle in invalid!\n";
			}
			else cout<<"\nYour puzzle is invalid!\n";
		}
		else cout<<"\nYour puzzle is invalid!\n";
	}
	

	private:bool ValidRows(){
		
		int rowVal, colVal, value;

		for(rowVal=0; rowVal<9; rowVal++){ 
			for(value=1; value<=9; value++){ 

				if(inRow(rowVal,value)==false)
					return false;
			} 
		} 
		return true;
	}

	private:bool inRow(int row, int value){
		int colVal;
		for(colVal=0; colVal<9; colVal++){
			if(Box.getValue(row,colVal)==value)
				return true;
		}
		return false;
	}

	private:bool ValidColumns(){
		
		int rowVal, colVal, value;
		
		for(colVal=0; colVal<9; colVal++){ 
			for(value=1; value<=9; value++){
				
				if(inCol(colVal,value)==false)
					return false;
			}
		} 
		return true;
	}

	private:bool inCol(int col, int value){
		int rowVal=0;
		for(rowVal=0; rowVal<9; rowVal++){
			if(Box.getValue(rowVal,col)==value)
				return true;
		}
		return false;
	}
	

	private:bool ValidTTS(){
		
		int squareVal, value;

		for(squareVal=0; squareVal<9; squareVal++){ 
			for(value=1; value<=9; value++){ 

				if(inSquare(squareVal,value)==false)
					return false;
			} 
		}
		return true;
	}

	private:bool inSquare(int squareNum, int value){
		int rowS=(squareNum/3)*3;
		int rowE=rowS+2;
		
		int colS=(squareNum%3)*3;
		int colE=colS+2;

		int rowVal, colVal;

		for(rowVal=rowS; rowVal<=rowE; rowVal++){
			for(colVal=colS; colVal<=colE; colVal++){
				if(Box.getValue(rowVal,colVal)==value)
					return true;
			}
		}
		return false;
	}

};


int main(){
	SudokuValidator() ;
	return 0;
}