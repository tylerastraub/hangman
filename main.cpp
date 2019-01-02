// CSC-150 Homework 18.
// This program plays hangman.
// Written in class on November 22, 2017 by Tyler Straub.

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

void displayGame(int bodyParts, vector<int> underscores,
  vector<char> correctlyGuessedLetters, vector<char> incorrectLetters)
{
  // clear screen
  for(int i = 0; i < 15; i++)
  {
    cout << endl;
  }

  // draws a cool logo
  cout << " ---------------" << endl;
  cout << "| H A N G M A N |" << endl;
  cout << " ---------------" << endl << endl;;

  // draw guessed letters
  cout << "Guessed letters: ";

  for(int i = 0; i < incorrectLetters.size(); i++)
  {
    cout << incorrectLetters[i] << " ";
  }

  cout << endl;

  //draw hangman
  cout << "     --   " << endl;
  cout << "    |  |  " << endl;
  switch(bodyParts)
  {
    case 0: cout << "    |" << endl;
            cout << "    |" << endl;
            cout << "    |" << endl;
            cout << "    |" << endl;
            cout << "____|_____" << endl;
          break;

    case 1: cout << "    |  0" << endl;
            cout << "    |  " << endl;
            cout << "    |  " << endl;
            cout << "    |  " << endl;
            cout << "____|_____" << endl;
          break;

    case 2: cout << "    |  0" << endl;
            cout << "    |  |" << endl;
            cout << "    |  " << endl;
            cout << "    |  " << endl;
            cout << "____|_____" << endl;
          break;

    case 3: cout << "    |  0" << endl;
            cout << "    | /|" << endl;
            cout << "    |  " << endl;
            cout << "    |  " << endl;
            cout << "____|_____" << endl;
          break;

    case 4: cout << "    |  0" << endl;
            cout << "    | /|\\" << endl;
            cout << "    |  " << endl;
            cout << "    |  " << endl;
            cout << "____|_____" << endl;
          break;

    case 5: cout << "    |  0" << endl;
            cout << "    | /|\\" << endl;
            cout << "    | /" << endl;
            cout << "    |  " << endl;
            cout << "____|_____" << endl;
          break;

    case 6: cout << "    |  0" << endl;
            cout << "    | /|\\" << endl;
            cout << "    | /^" << endl;
            cout << "    |  " << endl;
            cout << "____|_____" << endl;
          break;

    case 7: cout << "    |  0" << endl;
            cout << "    | /|\\" << endl;
            cout << "    | /^\\" << endl;
            cout << "    |  " << endl;
            cout << "____|_____" << endl;
          break;

    case 8: cout << "    |  0" << endl;
            cout << "    | /|\\" << endl;
            cout << "    | /^\\" << endl;
            cout << "    | `" << endl;
            cout << "____|_____" << endl;
          break;

    case 9: cout << "    |  0" << endl;
            cout << "    | /|\\" << endl;
            cout << "    | /^\\" << endl;
            cout << "    | ` `" << endl;
            cout << "____|_____" << endl;
          break;
  }

  cout << endl << "Word:";

  // write letters
  for(int i = 0; i < underscores.size(); i++)
  {
    if(underscores[i] == 0)
    {
      cout << "_";
    }
    else
    {
      cout << correctlyGuessedLetters[i];
    }
  }

  cout << endl;
}

bool checkIfGuessIsCorrect(vector<int>& positionOfLettersGuessed, string word,
  char guess, vector<char> wrongLetters)
{
  bool letterFound = false;

  for(int i = 0; i < wrongLetters.size(); i++)
  {
    if(wrongLetters[i] == guess)
    {
      return true;
    }
  }

  for(int i = 0; i < word.length(); i++)
  {
    if(guess == word[i])
    {
      positionOfLettersGuessed[i] = 1;
      letterFound = true;
    }
  }

  return letterFound;
}

void checkGameCondition(bool& gameWon, bool& gameLost,
  vector<int> lettersGuessed, int wrongGuesses)
{
  //check if max guesses have been reached
  if(wrongGuesses >= 9)
  {
    gameLost = true;
    return;
  }

  // check if any letters have not been guessed and return if so
  for(int i = 0; i < lettersGuessed.size(); i++)
  {
    if(lettersGuessed[i] == 0)
    {
      return;
    }
  }

  // if previous two checks are fine, the game is won
  gameWon = true;
}

string getRandomWord()
{
  srand(time(0));
  vector<string> words;
  string inputData;
  int randNum;
  int numberOfWords = 0;
  ifstream inputFile;

  inputFile.open("hangman_words.txt");

  words.clear();

  while(true)
  {
    getline(inputFile, inputData);
    if(inputFile.fail()) break;

    words.push_back(inputData);
    numberOfWords++;
  }
  randNum = rand() % numberOfWords;
  inputFile.close();

  return words[randNum];
}

void init(string& word, int& wordLength, vector<int>& blankSpaces,
  vector<char>& wordVector, vector<char>& wrongLetters, int& wrongGuesses)
{
  string menuResult;

  // resets vectors and guesses
  blankSpaces.clear();
  wordVector.clear();
  wrongLetters.clear();
  wrongGuesses = 0;

  cout << "Would you like to pick a random word or enter one manually? " <<
   endl;
  cout << "1: Random word" << endl;
  cout << "2: Enter word manually" << endl;
  cin >> menuResult;

  if(menuResult == "1")
  {
    word = getRandomWord();
    wordLength = word.length();

    for(int i = 0; i < wordLength; i++)
    {
      blankSpaces.push_back(0);
      wordVector.push_back(word[i]);
    }
  }
  else
  {
    cout << "Please enter your word: ";
    cin >> word;

    wordLength = word.length();

    for(int i = 0; i < wordLength; i++)
    {
      blankSpaces.push_back(0);
      wordVector.push_back(word[i]);
    }
  }
}

int main()
{
  string userInput, userMenuInput;
  char guessedLetter;
  int wordLength;
  int wrongGuesses;
  vector<int> positionOfLettersGuessed;
  vector<char> letters, wrongLetters;
  bool gameWon, gameLost = false;

  // calls init, which passes by reference to set or clear all these variables
  init(userInput, wordLength, positionOfLettersGuessed, letters, wrongLetters,
    wrongGuesses);

  // game loop
  while(true)
  {
    displayGame(wrongGuesses, positionOfLettersGuessed, letters, wrongLetters);
    checkGameCondition(gameWon, gameLost, positionOfLettersGuessed,
      wrongGuesses);

    // check if game was won or lost and prompt a new game if so
    if(gameWon)
    {
      cout << endl << "Congratulations, you won! Play again?" << endl;
      cout << "1: Yes" << endl;
      cout << "2: No" << endl;

      cin >> userMenuInput;

      if(userMenuInput == "1")
      {
        gameWon = false;

        init(userInput, wordLength, positionOfLettersGuessed, letters,
          wrongLetters, wrongGuesses);
        displayGame(wrongGuesses, positionOfLettersGuessed, letters, wrongLetters);
        checkGameCondition(gameWon, gameLost, positionOfLettersGuessed,
          wrongGuesses);
      }
      else
      {
        break;
      }
    }
    else if(gameLost)
    {
      cout << endl << "Sorry, you lost! The word was " << userInput <<
        ". Play again? " << endl;
      cout << "1: Yes" << endl;
      cout << "2: No" << endl;

      cin >> userMenuInput;

      if(userMenuInput == "1")
      {
        gameLost = false;

        init(userInput, wordLength, positionOfLettersGuessed, letters,
          wrongLetters, wrongGuesses);
        displayGame(wrongGuesses, positionOfLettersGuessed, letters, wrongLetters);
        checkGameCondition(gameWon, gameLost, positionOfLettersGuessed,
          wrongGuesses);
      }
      else
      {
        break;
      }
    }

    // user guesses letter
    cout << endl << "Please guess a letter: ";
    cin >> guessedLetter;

    // checks user guess
    if(!checkIfGuessIsCorrect(positionOfLettersGuessed, userInput,
      guessedLetter, wrongLetters))
    {
      wrongGuesses++;
      wrongLetters.push_back(guessedLetter);
    }
  }

  return 0;
}
