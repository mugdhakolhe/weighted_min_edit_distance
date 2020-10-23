/*
																	Programming Assignment No. 2
																				
Calculate the weighted minimum edit distance between two strings.
 Back trace your solution. 
 The confusion matrix for spelling errors is given below.
=============================================================================================================================================================
Approach:

1. Read the confusin matrix from file
2. Build the cost matrix and save the pointers.
3. Backtrace your solution.
===============================================================================================================================================================

Made by

Author: Mugdha Satish Kolhe
Enrollment No: BT17CSE043
Course Code: CSL-436
Course: Information Retrieval
================================================================================================================================================================

*/
#include <bits/stdc++.h> 
#include <algorithm>

enum direction{lft, up, diag} ;	//enum used to save space in backtracking

using namespace std;


int min(int x, int y, int z) 
{ 
	return min(min(x, y), z); 
} 

int main() 
{
	int conf[26][26];
	ifstream is("conf_mat.txt");
	for(int i=0;i<26;i++)
	{
		for(int j=0;j<26;j++)		//reading the confusion matrix
		{
			is >> conf[i][j];
			//cout<<conf[i][j]<< " ";
		}
		//cout<<endl;
	}
	is.close();
	ofstream fout;
	fout.open("ir_output_1.txt");
	string str1, str2;	//declaration of vars
	int m, n, j, i, insert=0, deletes=0, replace=0; 
	
	cout<<"Enter string 1(incorrect): ";	//input misprinted string
	cin>>str1;
	transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
	fout<<str1;
	fout<<endl;
	cout<<"Enter string 2(correct): ";	//enter the correct string
	cin>>str2;
	transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
	fout<<str2;
	fout<<endl;
	
	fout<<endl;
	m=str1.length();	
	n=str2.length();
	
	int dp[m + 1][n + 1];
	enum direction ptr[m + 1][n + 1];
	
	//Initialization
	dp[0][0]=0;
	for(i=1; i<=m; i++)
	{
		dp[i][0]=dp[i-1][0] + 1;//del[x[i]];
		ptr[i][0]=up;
	}  
	for(j=1; j<=n; j++)
	{
		dp[0][j]=dp[0][j-1] + 1;//ins[y[j]];
		ptr[0][j]=lft;
	}
	
	//Building the cost matrix
	for (int i = 1; i <= m; i++) 
	{ 
		for (int j = 1; j <= n; j++) 
		{
			int add=0; 
			if(str1[i-1]==str2[j-1])
			{
				dp[i][j]=dp[i-1][j-1];	//Retain
				ptr[i][j]=diag;
			}
			else
			{
				add=conf[str1[i-1]-'a'][str2[j-1]-'a']; //sub[x[i][y[j]];		//Replace
				dp[i][j] =  min(
								(dp[i][j - 1]+ 1),//ins[y[j]]), 		// Insert 
								(dp[i - 1][j]+ 1),//del[x[i]]), 		// Remove 
								(dp[i - 1][j - 1]+ add)					// Replace
							);
							
				if(dp[i][j]==dp[i][j - 1]+ 1)//ins[y[j]] ) //Saving the pointers for baktracting
				{
					ptr[i][j]=lft;
				}
				else if(dp[i][j]==dp[i - 1][j]+ 1)//del[x[i]] )
				{
					ptr[i][j]=up;
				}
				else if(dp[i][j]==dp[i-1][j-1]+add)
				{
					ptr[i][j]=diag;	
				}
				
			}
		} 
	}
	cout<<"    ";	//printing of cost matrix
	fout<<"    ";
	for(i=0; i<=n; i++)
	{
		cout<<str2[i]<<" ";
		fout<<str2[i]<<" ";
	}
	cout<<endl;
	fout<<endl;
	for(i=0; i<=m; i++)
	{
		if(i>0)
		{
			cout<<str1[i-1]<<" ";
			fout<<str1[i-1]<<" ";
		}
		else
		{
			cout<<"  ";
			fout<<"  ";
		}
		for(j=0; j<=n; j++)
		{
			cout<< dp[i][j]<<" ";
			fout<< dp[i][j]<<" ";
		}
		cout<<endl;
		fout<<endl;
	}
	

	
	cout<<endl;
	cout<<"Weighted edit distance between "<<str1<<" and "<<str2<<" is: "<<dp[m][n]<<endl;
	fout<<endl;
	fout<<"Weighted edit distance between "<<str1<<" and "<<str2<<" is: "<<dp[m][n]<<endl;
	i=m; j=n;
	cout<<endl;
	fout<<endl;
	cout<<" To convert str1 to str2 (Reverse order): "<<endl<<endl;
	fout<<" To convert str1 to str2 (Reverse order): "<<endl<<endl;
	int cost=0;
	
	while(!(i==0 && j==0))	//backtracting
	{
		//cout<<"i: "<<i<<"  j: "<<j<<endl;
		if(ptr[i][j]==up)	//Delete
		{
			cout<<"Delete "<< str1[i-1]<< "          cost: "<<1<<endl;
			fout<<"Delete "<< str1[i-1]<< "          cost: "<<1<<endl;
			deletes++;
			i--;
		}
		else if(ptr[i][j]==lft)	//Insert
		{
			cout<<"Insert "<< str2[j-1]<< "          cost: "<<1<<endl;
			fout<<"Insert "<< str2[j-1] << "         cost: "<<1<<endl;
			insert++;
			j--;
		}
		else if(ptr[i][j]==diag)
		{
			if(dp[i][j]==dp[i-1][j-1] && str1[i-1]==str2[j-1])	//Retain
			{
				cout<<"Retain "<< str1[i-1]<< "          cost: "<<0<<endl;
				fout<<"Retain "<< str1[i-1]<< "          cost: "<<0<<endl;
			}
			else	//Replace
			{
				cout<<"Replace "<< str1[i-1] << " with "<< str2[j-1] <<"  cost: "<< dp[i][j]-dp[i-1][j-1]<<endl;
				fout<<"Replace "<< str1[i-1] << "with "<< str2[j-1] <<"  cost: "<< dp[i][j]-dp[i-1][j-1]<<endl;
				replace++;
			}
			i--;
			j--;
		}
	}
	cout<<endl;
	cout<<"==========================================================================="<<endl;
	cout<<"Total no. of insertions: "<<insert<<endl;
	cout<<"Total no. of deletions: "<<deletes<<endl;
	cout<<"Total no. of replacements: "<<replace<<endl;
	cout<<endl;
	fout<<endl;
	fout<<"==========================================================================="<<endl;
	fout<<"Total no. of insertions: "<<insert<<endl;
	fout<<"Total no. of deletions: "<<deletes<<endl;
	fout<<"Total no. of replacements: "<<replace<<endl;
	fout<<endl;
	fout.close();
	return 0; 
} 


