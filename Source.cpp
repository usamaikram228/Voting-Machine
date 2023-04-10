//#define_CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>

using namespace std;
struct Candidate
{
	char name[100];
	char electionSymbol[30];
	int votes;
};
struct Time
{
	int hours;
	int minutes;
	int seconds;
};
struct Date
{
	int day;
	int month;
	int year;
};
struct VotingMachine
{
	char constituencyName[30];
	Date electionDate;
	Time startTime;
	Time endTime;
	Candidate* CandidateList;
	int noOfCandidates;
	int capacity;
};
void inputCandidate(Candidate* s)
{
	cout << "Enter the name of candidate : ";
	cin.getline(s->name, '\n');
	cout << "Enter the election symbol : ";
	cin.getline(s->electionSymbol, '\n');
	s->votes = 0;
}
void castVote(Candidate& s)
{
	s.votes++;
}
void intializeVotingMachine(VotingMachine& vm, const char* constName, Date d, Time sTime, Time eTime, int cap)
{
	strcpy_s(vm.constituencyName, constName);
	vm.electionDate = d;
	vm.startTime = sTime;
	vm.endTime = eTime;
	vm.capacity = cap;
	vm.noOfCandidates = 0;
	vm.CandidateList = new Candidate[vm.capacity];
}
bool addCandidate(VotingMachine& vm, const char* candName, const char* electSymbol)
{
	Date d = { 6,4,2020 };
	if (vm.electionDate.day < d.day)
	{
		if (vm.noOfCandidates != 0)
		{
			if (vm.noOfCandidates < vm.capacity)
			{
				for (int i = 0; i < vm.noOfCandidates; i++)
				{
					if (strcmp(vm.CandidateList[i].electionSymbol, electSymbol) == 0)
					{
						return false;
					}
				}
			}
		}
	}
	strcpy_s(vm.CandidateList[vm.noOfCandidates].electionSymbol, electSymbol);
	strcpy_s(vm.CandidateList[vm.noOfCandidates].name, candName);
	vm.noOfCandidates++;
	return true;
}
bool timeChecking(VotingMachine& vm)
{
	time_t t = time(0);
	tm curTime = *localtime(&t);
	
	int hour;
	if (curTime.tm_hour < vm.startTime.hours)
	{
		hour = 12 + curTime.tm_hour;
		if (hour < vm.endTime.hours)
		{
			return true;
		}
	}
	return false;
}
bool castVote(VotingMachine& vm, const char* elecSymbol)
{
	time_t t = time(NULL);
	tm curTime = * localtime(&t);
	
	if (vm.electionDate.day == curTime.tm_mday)
	{
		if (timeChecking(vm))
		{
			for (int i = 0; i < vm.noOfCandidates; i++)
			{
				if (strcmp(vm.CandidateList[i].electionSymbol, elecSymbol) == 0)
				{
					castVote(vm.CandidateList[i]);
					return true;
				}
			}
		}
	}
	return false;
}
int candidateReport(VotingMachine& vm, const char* elecSymbol)
{
	for (int i = 0; i < vm.noOfCandidates; i++)
	{
		if (strcmp(vm.CandidateList[i].electionSymbol, elecSymbol) == 0)
		{
			return vm.CandidateList[i].votes;
		}
	}
	return -1;
}
void freeVotingMachine(VotingMachine& vm)
{
	if (vm.CandidateList == nullptr)
	{
		return;
	}
	delete[] vm.CandidateList;
	vm.CandidateList = nullptr;
}
Candidate* electionResult(VotingMachine& vm)
{
	Candidate first, second, third;
	first = vm.CandidateList[0];
	
	for (int i = 0; i < vm.noOfCandidates; i++)
	{                                                                        //First Position
		if (vm.CandidateList[i].votes > first.votes)
		{
			first = vm.CandidateList[i];
			vm.CandidateList[0] = first;
		}
	}

	second = vm.CandidateList[1];
	for (int i = 0; i < vm.noOfCandidates; i++)                              //second position
	{
		if (vm.CandidateList[i].votes > second.votes && vm.CandidateList[i].votes < first.votes)
		{
			second = vm.CandidateList[i];
			vm.CandidateList[1] = second;
		}
	}
	third = vm.CandidateList[2];
	for (int i = 0; i < vm.noOfCandidates; i++)                                //third position
	{
		if (vm.CandidateList[i].votes > third.votes && vm.CandidateList[i].votes < second.votes)
		{
			third = vm.CandidateList[i];
			vm.CandidateList[2] = third;
		}
	}
	return vm.CandidateList;
}
int main()
{
	VotingMachine vMachine;
	Date d = { 4,4,2022 };
	Time st = { 8,0,0 };
	Time et = { 18,0,0 };

	intializeVotingMachine(vMachine, "pp-204", d, st, et, 10);

	addCandidate(vMachine, "Aslam", "Racket");
	addCandidate(vMachine, "Naeem", "kulhara");
	addCandidate(vMachine, "Ayesha", "abc");
	addCandidate(vMachine, "Rabia", "zzz");
	addCandidate(vMachine, "Aftab", "Hockey");
	addCandidate(vMachine, "Manan", "TV");

	d.day = 5;
	vMachine.electionDate = d;
	castVote(vMachine, "zzz");
	castVote(vMachine, "kulhari");
	castVote(vMachine, "zzz");
	castVote(vMachine, "zzz");
	castVote(vMachine, "Hockey");
	castVote(vMachine, "Hockey");
	castVote(vMachine, "zzz");
	castVote(vMachine, "Hockey");
	castVote(vMachine, "Hockey");

	cout << "Hockey vote count so far : " << candidateReport(vMachine, "Hockey");

	castVote(vMachine, "Hockey");
	castVote(vMachine, "TV");
	castVote(vMachine, "abc");
	castVote(vMachine, "Racket");

	Candidate* List = electionResult(vMachine);

	cout<<"\n\n///////////      Election Result      ////////////////\n\n";
	cout << "First Position : " << List[0].electionSymbol << " : " << List[0].votes << '\n';
	cout << "Second Position : " << List[1].electionSymbol << " : " << List[1].votes << '\n';
	cout << "Third Position : " << List[2].electionSymbol << " : " << List[2].votes << '\n';
	delete[] List;
	freeVotingMachine(vMachine);

	cout << "\n\n";
	return 0;
}

