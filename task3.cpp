#include<iostream>
#include<fstream>
#include<string>
#include<queue>
using namespace std;

template <class T>
void showQueue(queue <T> gq) 
{ 
    queue <T> g = gq; 
    while (!g.empty()) 
    { 
        cout << g.front()<<"\n"; 
        g.pop(); 
    } 
    cout << '\n'; 
} 
void emptyFile()
{
	ofstream file("readylist.txt", ios::trunc);
}
void sortInDescOrder(int count_of_processes,queue<string>&queueList,queue<int>&exeTimeList )
{
	int* arrNum=new int[count_of_processes];
	string* arrString=new string[count_of_processes];

	for (int i = 0; i < count_of_processes; i++)
	{
		arrNum[i]=exeTimeList.front();
		exeTimeList.pop();

		arrString[i]=queueList.front();
		queueList.pop();

	}

	for (int i = 0; i < count_of_processes-1; i++)
	{
		for(int j=0;j< count_of_processes-i-1 ;j++)  
		{
			if(arrNum[j]<arrNum[j+1])
			{
				int tempNum=arrNum[j];
				arrNum[j]=arrNum[j+1];
				arrNum[j+1]=tempNum;

				string tempString=arrString[j];
				arrString[j]=arrString[j+1];
				arrString[j+1]=tempString;
			}
		}
	}
	for (int i = 0; i < count_of_processes; i++)
	{
		exeTimeList.push(arrNum[i]);
		queueList.push(arrString[i]);
	}

	delete []arrNum;delete []arrString;
}
int readFile(queue<string>&queueList, queue<int>&exeTimeList ,int &sum)
{
	int count_of_processes=0;
	string str;
	int var=0;
	ifstream infile;
	infile.open("readylist.txt");

	if(!infile)
		cout<<"File Creation Failed ";
	else
	{
		while(!infile.eof())
		{
			getline(infile,str);
			count_of_processes++;
			queueList.push(str);

			ofstream outf("sample.txt");
			outf<<str;
			outf.close();

			ifstream inf("sample.txt");
			if(inf.is_open())
			{
				while(!inf.eof())
				{
					inf.ignore(30,',');
					inf>>var;
					sum=sum+var;
					exeTimeList.push(var);
				}
			}
			inf.close();
		}
	}
	infile.close();
	return count_of_processes;
}
int main()
{
	queue<string> queueList;
	queue<int>	exeTimeList;
	int sum=0;
	int count_of_processes=0;
	
	//=======READ FROM FILE AND MAKE IT EMPTY
	count_of_processes=readFile(queueList,exeTimeList,sum);
	emptyFile();

	//++++++++++++SHOW INITIALLY LISTS

	//showQueue(queueList); showQueue(exeTimeList);

	//========SORT IN DESENDING ORDER
	sortInDescOrder(count_of_processes,queueList,exeTimeList);
	showQueue(queueList);


	//=======DEFINE OUR UNIT  (1 unit=10 iterations)

	int unit=0	, arrivalTime=0		,turnaroundTime=0	,waitingTime=0	,count=0;
	int executionTime=exeTimeList.front();
	int executionStartTime=0	,executionEndTime=exeTimeList.front();
	int total=sum*10;int var1=0;
	int avgWaitTime=0	,avgTurnAroundTime=0;

	cout<<"ExecutionTime"<<"\t"<<"WaitingTime"<<"\t"<<"TurnaroundTime"<<"\n";

	for(int i=0; i<=(total) ;i++,var1++)
	{
		count++;
		if(count%10==0)
			unit++;

		if(var1==(executionTime*10))
		{
			waitingTime=executionStartTime-arrivalTime;
			avgWaitTime=avgWaitTime+waitingTime;

			turnaroundTime=executionEndTime-arrivalTime;
			avgTurnAroundTime=avgTurnAroundTime+turnaroundTime;

			cout<<executionTime<<"\t\t"<<waitingTime<<"\t\t"<<turnaroundTime<<"\n";
			exeTimeList.pop();
			queueList.pop();
			var1=0;
			executionTime=0;
			executionStartTime=turnaroundTime;
			if(!exeTimeList.empty())
			{
				executionTime=exeTimeList.front();
			}
			executionEndTime=executionStartTime+executionTime;	
		}

		if(unit==15)
		{
			cout<<"\nPresses <ENTER> to continue\n";
			getchar();
			unit=0;
		
			string str15;	int var15=0;

			ifstream infile;
			infile.open("readylist.txt");
			
			if(infile.is_open())
			{
				infile.seekg (0, ios::end);
				int length = infile.tellg();
				infile.close();
				if (length == 0)
				{
					continue;
				}
				else
				{
					ifstream inputfile;
					inputfile.open("readylist.txt");
					while(!inputfile.eof())
					{
						getline(inputfile,str15);
						count_of_processes++;
						queueList.push(str15);
						
						ofstream outf("sample.txt");
						outf<<str15;
						outf.close();
						ifstream inf("sample.txt");
						if(inf.is_open())
						{
							while(!inf.eof())
							{
								inf.ignore(30,',');
								inf>>var15;
								sum=sum+var15;
								exeTimeList.push(var15);
							}
						}
						inf.close();
					}
					total=sum*10;
					emptyFile();

					sortInDescOrder(count_of_processes,queueList,exeTimeList);
					executionTime=exeTimeList.front();
					inputfile.close();
				}
		}
	}
}
	cout<<"\nAverage Waiting Time = "<<(avgWaitTime/count_of_processes)<<endl;
	cout<<"\nAverage Turn Around Time = "<<(avgTurnAroundTime/count_of_processes)<<endl;;
return 0;
}