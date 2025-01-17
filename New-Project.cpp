#include <iostream>
#include <string>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct  stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds= 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner ;
    string WinnerName = "";

};


int RandNumber(int from, int to)
{
    int randN = rand() % (to - from + 1) + from;


    return  randN;
}


string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "player1","computer","no winner" };
    return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }
    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;

        }
        break;

    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;

    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;
    }
    return enWinner::Player;
}



string ChoiceName(enGameChoice Choice)
{
    string arrGameChoice[3] = { "Stone","Paper", "Scissors" };
    return arrGameChoice[Choice - 1];
}


void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2f"); //turn screen Green
        break;
    case enWinner::Computer:
        system("color 4f");  //turn screen Red
        break;

    default:
        system("color 6f"); //turn screen Yellow
        break;
    }
}


void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n-----------Round[" << RoundInfo.RoundNumber << "]----------\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";



    SetWinnerScreenColor(RoundInfo.Winner);
    cout << endl;
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enWinner::Player;

    else if (ComputerWinTimes > Player1WinTimes)

        return enWinner::Computer;

    else
        return enWinner::Draw;

}


stGameResults  FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;
    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

enGameChoice ReadPlayer1Choice()
{
    short Choice = 1;

    do
    {

        cout << "\nYur Choice [1]:Stone, [2]:Paper. [3]:Scissors ? ";
        cin >> Choice;

    } while (Choice < 1 || Choice >3);

    return (enGameChoice)Choice;

}


enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandNumber(1, 3);
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins: \n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        //Increase Win/Draw counter
        if (RoundInfo.Winner == enWinner::Player)
            Player1WinTimes++;

        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;
        PrintRoundResults(RoundInfo);
    }

    return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);

}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}


void ShowGameOverScreen()
{
    cout << Tabs(2) << "__________________________________________________________\n\n";
    cout << Tabs(2) << "                 +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "__________________________________________________________\n\n";

}


void ShowFinalGameResults(stGameResults GameResults)
{


    cout << Tabs(2) << "_____________________ [Game Results]_____________________\n\n";
    cout << Tabs(2) << "Game Rounds        :" <<
        GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player Won Times   :" <<
        GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer Won Times :" <<
        GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Drow Times :" <<
        GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner :" <<
        GameResults.WinnerName << endl;
    cout << Tabs(2) <<
     "___________________________________________________________\n";


    SetWinnerScreenColor(GameResults.GameWinner);
}

short ReadHowManyRounds()
{ 
    short GameRounds = 1; 
    
    do 
    { cout << "How Many Rounds 1 to 10 ? \n";     
    cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds >10);
    
    
    return GameRounds; 
}



void ResetScreen()
{ 
    system("cls");
    system("color 0F"); 
}



void StartGame()
{
    char playAgain = 'Y';

    do
    {
        ResetScreen(); 
        stGameResults GameResults = PlayGame(ReadHowManyRounds());         
        ShowGameOverScreen();  
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
        cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'x');

}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();
    return 0;
}
