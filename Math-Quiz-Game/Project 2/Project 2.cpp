#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

enum enQuestionsLevel
{
    EasyLevel = 1,
    MedLevel = 2,
    HardLevel = 3,
    Mix = 4
};

enum enOperationType
{
    Add = 1,
    Sub = 2,
    Mult = 3,
    Div = 4,
    MixOp = 5
};

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;

    enOperationType OperationType;
    enQuestionsLevel QuestionLevel;

    int CorrectAnswer = 0;
    int PlayerAnswer = 0;

    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[100];

    short NumberOfQuestions = 0;

    enQuestionsLevel QuestionsLevel;
    enOperationType OpType;

    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;

    bool isPass = false;
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short ReadHowManyQuestions()
{
    short NumberOfQuestions;

    do
    {
        cout << "How Many Questions do you want to answer ? ";
        cin >> NumberOfQuestions;

    } while (NumberOfQuestions < 1 || NumberOfQuestions > 100);

    return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
    short QuestionLevel;

    do
    {
        cout << "Enter Questions Level "
            << "[1] Easy, [2] Med, [3] Hard, [4] Mix ? ";

        cin >> QuestionLevel;

    } while (QuestionLevel < 1 || QuestionLevel > 4);

    return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
    short OpType;

    do
    {
        cout << "Enter Operation Type "
            << "[1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";

        cin >> OpType;

    } while (OpType < 1 || OpType > 5);

    return (enOperationType)OpType;
}

enOperationType GetRandomOperationType()
{
    return (enOperationType)RandomNumber(1, 4);
}

string GetOpTypeSymbol(enOperationType OpType)
{
    string arrOpType[5] =
    {
        "+",
        "-",
        "x",
        "/",
        "Mix"
    };

    return arrOpType[OpType - 1];
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
    string arrQuestionLevelText[4] =
    {
        "Easy",
        "Med",
        "Hard",
        "Mix"
    };

    return arrQuestionLevelText[QuestionLevel - 1];
}

int SimpleCalculator(int Number1,
    int Number2,
    enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return Number1 + Number2;

    case enOperationType::Sub:
        return Number1 - Number2;

    case enOperationType::Mult:
        return Number1 * Number2;

    case enOperationType::Div:
        return Number1 / Number2;
    }

    return Number1 + Number2;
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel,
    enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
    {
        QuestionLevel =
            (enQuestionsLevel)RandomNumber(1, 3);
    }

    if (OpType == enOperationType::MixOp)
    {
        OpType = GetRandomOperationType();
    }

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionsLevel::EasyLevel:

        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        break;

    case enQuestionsLevel::MedLevel:

        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        break;

    case enQuestionsLevel::HardLevel:

        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        break;
    }

    Question.CorrectAnswer =
        SimpleCalculator(
            Question.Number1,
            Question.Number2,
            Question.OperationType
        );

    Question.QuestionLevel = QuestionLevel;

    return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short Question = 0;
        Question < Quizz.NumberOfQuestions;
        Question++)
    {
        Quizz.QuestionList[Question] =
            GenerateQuestion(
                Quizz.QuestionsLevel,
                Quizz.OpType
            );
    }
}

void PrintQuestion(stQuizz& Quizz,
    short QuestionNumber)
{
    cout << "\n";
    cout << "Question ["
        << QuestionNumber + 1
        << "/"
        << Quizz.NumberOfQuestions
        << "]\n\n";

    cout << Quizz.QuestionList[QuestionNumber].Number1
        << endl;

    cout << Quizz.QuestionList[QuestionNumber].Number2
        << " "
        << GetOpTypeSymbol(
            Quizz.QuestionList[QuestionNumber].OperationType)
        << endl;

    cout << "____________\n";
}

void SetScreenColor(bool Right)
{
    if (Right)
    {
        system("color 2F");
    }
    else
    {
        system("color 4F");
        cout << "\a";
    }
}

void CorrectQuestionAnswer(stQuizz& Quizz,
    short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer !=
        Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;

        Quizz.NumberOfWrongAnswers++;

        cout << "Worng Answer :-(\n";

        cout << "The right answer is: "
            << Quizz.QuestionList[QuestionNumber].CorrectAnswer
            << endl;

        SetScreenColor(false);
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;

        Quizz.NumberOfRightAnswers++;

        cout << "Right Answer :-)\n";

        SetScreenColor(true);
    }
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0;
        QuestionNumber < Quizz.NumberOfQuestions;
        QuestionNumber++)
    {
        PrintQuestion(Quizz, QuestionNumber);

        cin >> Quizz.QuestionList[QuestionNumber].PlayerAnswer;

        CorrectQuestionAnswer(
            Quizz,
            QuestionNumber
        );
    }

    Quizz.isPass =
        Quizz.NumberOfRightAnswers >=
        Quizz.NumberOfWrongAnswers;
}

string GetFinalResultsText(bool Pass)
{
    if (Pass)
        return "PASS :-)";

    return "FAIL :-(";
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "______________________________\n\n";

    cout << "Final Results is "
        << GetFinalResultsText(Quizz.isPass)
        << endl;

    cout << "______________________________\n\n";

    cout << "Number of Questions: "
        << Quizz.NumberOfQuestions
        << endl;

    cout << "Questions Level    : "
        << GetQuestionLevelText(
            Quizz.QuestionsLevel)
        << endl;

    cout << "OpType             : "
        << GetOpTypeSymbol(
            Quizz.OpType)
        << endl;

    cout << "Number of Right Answers: "
        << Quizz.NumberOfRightAnswers
        << endl;

    cout << "Number of Wrong Answers: "
        << Quizz.NumberOfWrongAnswers
        << endl;

    cout << "______________________________\n";

    SetScreenColor(Quizz.isPass);
}

void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestions =
        ReadHowManyQuestions();

    Quizz.QuestionsLevel =
        ReadQuestionsLevel();

    Quizz.OpType =
        ReadOpType();

    GenerateQuizzQuestions(Quizz);

    AskAndCorrectQuestionListAnswers(Quizz);

    PrintQuizzResults(Quizz);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();

        PlayMathGame();

        cout << "\nDo you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' ||
        PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}