/* main.cpp
    Wordle Reload is a game that allows you to guess either a 3 letter word or 5 letter word.
    You have a set amount of time to guess a word.  At the conlusion of game play
    you will be provided stats on your overall game play.

    Author: Juan Cruz & Martin Michel
    Date: 02/28/2022
    Class: CS 141, Spring 2022, UIC
    System: Replit
*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector> 
#include <cassert> 
#include <cctype> 
#include <string>
#include <ctime>
using namespace std;

void gameDisplayInstructions(){
    cout << "Program 3: Wordle Reload \n"
        << "CS 141, Spring 2022, UIC \n"
        << " \n"
        << "The objective of this game is to guess the randomly selected \n"
        << "word within a given number of attempts. You can select either \n"
        << "a three or five word board. \n"
        << "At the conlusion of the game, stats will be displayed.  \n"
        << "Indicators will be given if characters of the user entered \n"
        << "word are reflected in the guessed word. \n"
        << "  - If the character is in the correct position, the character \n"
        << "    will display as an uppercase value.\n"
        << "  - If the character is within the random word, the character \n"
        << "    will display as a lowercase value.\n"
        << "  - If you enter a character that is not in the word, an asterisk '*' \n"
        << "    will display."
        << " \n"
        << endl;
}
//---------------------------------------------
void readWordsIntoDictionary(vector<string>& listOfWords){ // takes the text document and adds it to a vector
  ifstream inStream;  
  inStream.open( "wordlewords.txt"); 
  assert( inStream.fail() == false );  

  listOfWords.clear();
  string newWord;

  while( inStream >> newWord) {
    listOfWords.push_back(newWord);
  }
  inStream.close(); 
}
//---------------------------------------------
void modifyCharacters(string guessedWord,string ogWord,string board[5],int numIt){ //adds the edited characters to the board
  char letter[5];
  int winner = 0;
  for(int i = 0; i < numIt; i++){
    letter[i] = guessedWord[i];
  }
  for (int i = 0; i < numIt; i++){
    if(letter[i] == ogWord[i]){
      board[i] = toupper(letter[i]);
      winner++;
    }
    else if(ogWord[0] == guessedWord[i] || ogWord[1] == guessedWord[i] || ogWord[2] == guessedWord[i] || ogWord[3] == guessedWord[i] || ogWord[4] == guessedWord[i]){
      board[i] = letter[i];
    }
    else{
      board[i] = "*";
    }
  }
}
//---------------------------------------------
void modifyCharacters3(string guessedWord,string ogWord,string board[5],int numIt){ //adds the edited characters to the board
  char letter[3];
  int winner = 0;
  for(int i = 0; i < numIt; i++){
    letter[i] = guessedWord[i];
  }
  for (int i = 0; i < numIt; i++){
    if(letter[i] == ogWord[i]){
      board[i] = toupper(letter[i]);
      winner++;
    }
    else if(ogWord[0] == guessedWord[i] || ogWord[1] == guessedWord[i] || ogWord[2] == guessedWord[i]){
      board[i] = letter[i];
    }
    else{
      board[i] = "*";
    }
  }
}
//---------------------------------------------
void addBrackets(int numIt, string board[5]){ //outputs the boards with brackets around the cahracters
  for (int i = 0; i < numIt; i++){
    cout << " [ " << board[i] << " ] ";
  }
}

//---------------------------------------------
int binarySearch(string searchWord,vector<string> dictionary){ //checks to make sure the userinput is a valid word from the list
  int mid;
  int low;
  int high;
   
  low = 0;
  high = dictionary.size() - 1;
   
  while (high >= low) {
    mid = (high + low) / 2;
    int searchResult = searchWord.compare(dictionary[mid]);
    if (searchResult == 0) {
      return mid;
    }
    else if (searchResult < 0) {
      high = mid - 1;
    }
    else {
      low = mid + 1;
    }
  }
  return -1; // not found
}
//---------------------------------------------
void addLettersToBoard(int numIt,string board[5],int numB,vector<string> temp1,string guessedWord,string ogWord, int numLetter){ //makes sure that the boards stack on top of each other
  string tempBoard[5]; string tempBoard2[5]; string tempBoard3[5]; string tempBoard4[5]; string tempBoard5[5];
  for(int i = 0; i < numLetter; i++){  
    board[i] = guessedWord[i];
  }
  modifyCharacters(guessedWord,ogWord,board,numLetter);
  if(numB < 6){ // all these if statements are used to output the previous boards
    for(int i = 0; i < numLetter; i++){  
      tempBoard[i] = temp1[0][i];
    }
    modifyCharacters(temp1[0],ogWord,tempBoard,numLetter);
    addBrackets(numLetter,tempBoard);
    if(numB < 5){
      for(int i = 0; i < numLetter; i++){  
      tempBoard2[i] = temp1[1][i];
      }
      cout<<endl;
      modifyCharacters(temp1[1],ogWord,tempBoard2,numLetter);
      addBrackets(numLetter,tempBoard2);
      if (numB < 4){
        for(int i = 0; i < numLetter; i++){
          tempBoard3[i] = temp1[2][i];
        }
        cout << endl;
        modifyCharacters(temp1[2],ogWord,tempBoard3,numLetter);
        addBrackets(numLetter,tempBoard3);
        if (numB < 3){
          for(int i = 0; i < numLetter; i++){
          tempBoard4[i] = temp1[3][i];
          }
          cout << endl;
          modifyCharacters(temp1[3],ogWord,tempBoard4,numLetter);
          addBrackets(numLetter,tempBoard4);
          if (numB < 2){
            for(int i = 0; i < numLetter; i++){
            tempBoard5[i] = temp1[4][i];
            }
            cout << endl;
            modifyCharacters(temp1[4],ogWord,tempBoard5,numLetter);
            addBrackets(numLetter,tempBoard5);
          }
        }
      }
    }
  }
  cout << endl;
  addBrackets(numIt,board);
  cout << endl;
}
//---------------------------------------------
void addLettersToBoard3(int numIt,string board[3],int numB,vector<string> temp1,string guessedWord,string ogWord, int numLetter){ //makes sure that the boards stack on top of each other
  string tempBoard[3]; string tempBoard2[3]; string tempBoard3[3];
  for(int i = 0; i < numLetter; i++){  
    board[i] = guessedWord[i];
  }
  modifyCharacters(guessedWord,ogWord,board,numLetter);
  if(numB < 4){ // all these if statements are used to output the previous boards
    for(int i = 0; i < numLetter; i++){  
      tempBoard[i] = temp1[0][i];
    }
    modifyCharacters(temp1[0],ogWord,tempBoard,numLetter);
    addBrackets(numLetter,tempBoard);
    if(numB < 3){
      for(int i = 0; i < numLetter; i++){  
      tempBoard2[i] = temp1[1][i];
      }
      cout<<endl;
      modifyCharacters(temp1[1],ogWord,tempBoard2,numLetter);
      addBrackets(numLetter,tempBoard2);
      if (numB < 2){
        for(int i = 0; i < numLetter; i++){
          tempBoard3[i] = temp1[2][i];
        }
        cout << endl;
        modifyCharacters(temp1[2],ogWord,tempBoard3,numLetter);
        addBrackets(numLetter,tempBoard3);
      }
    }
  }
  cout << endl;
  addBrackets(numIt,board);
  cout << endl;
}
//---------------------------------------------
int main() {
  srand(1);
  vector<int> longestStreak;
  vector<string> temp1;
  vector<string> listOfWords;
  vector<string> threeLetterWord;
  vector<string> fiveLetterWord;
  string guessedWord;
  int gameOption;
  string threeLetterBoard[3];  
  string fiveLetterBoard[5];  
  int tries1 = 4;
  int result;
  int tries2 = 6;
  vector<int>timeTotal;
  int numWins = 0;
  int numLetter;
  int streak = 0;
  
  readWordsIntoDictionary(listOfWords); //calls the function to read the words on the txt file named wordlwords
  gameDisplayInstructions(); // calls the function to display the instruction for the game

  //creates array filled with five letter words
  for(int i = 0; i < listOfWords.size();i++){ 
    if(listOfWords[i].length() == 5){
      fiveLetterWord.push_back(listOfWords[i]);
    }
  }
  //creates array filled with three letter words
  for(int i = 0; i < listOfWords.size();i++){ 
    if(listOfWords[i].length() == 3){
      threeLetterWord.push_back(listOfWords[i]);
    }
  }
  //string ogWord = threeLetterWord[rand() % 1065];
  time_t startTime = time( NULL); //for timer
  int elapsedSeconds = 0;

  while (gameOption != 3){
    cout << "Select a menu option: \n"
         << "   1. To play Wordle Reload 3 letter play \n"
         << "   2. To play Wordle Reload 5 letter play \n"
         << "   3. Exit the program \n"
         << "Your choice --> ";
    cin >> gameOption;
    temp1.clear();
    int numB = 6;
    int numB2 = 4;
    int tries1 = 4;
    int tries2 = 6;
//---------------------------------------------
    if(gameOption == 1){
      numLetter = 3;
      int ranWord = rand() % threeLetterWord.size();
      string ogWord = threeLetterWord[ranWord];
        cout << endl;
        cout << "To get started, enter your first 3 letter word.\n"
             << "You have 4 attempts to guess the random word.\n"
             << "The timer will start after your first word entry.\n"
             << "Try to guess the word within 20 seconds."
             << endl;
      while (tries1 != 0){
        time_t startTime = time( NULL); //for timer
        cout << endl;
        cout << "Please enter word -->  ";
        cin >> guessedWord;
        transform(guessedWord.begin(), guessedWord.end(), guessedWord.begin(),[](unsigned char c){ return std::tolower(c); }); //lowercase
        cout << endl;
        if(guessedWord.length() < 3 || guessedWord.length() > 3){
          cout << "Invalid word entry - please enter a word that is 3 characters long." << endl;
        }
        else{
          sort(listOfWords.begin(),listOfWords.end());
          result = binarySearch(guessedWord,listOfWords);
          if (result == -1){
            cout << "Not a playable word, please select another word." << endl;
            }
          else{
            temp1.push_back(guessedWord);
            addLettersToBoard3(numLetter,threeLetterBoard,numB2,temp1,guessedWord,ogWord,3);
            numB2--;
            tries1--;
            if (guessedWord == ogWord){ //this is the win checker
              elapsedSeconds = difftime( time( NULL), startTime);
              timeTotal.push_back(elapsedSeconds);
              numWins++;
              cout << endl;
              cout << "Nice Work!  You guessed the correct word\n"
                   << "  -You completed the board in: " << elapsedSeconds << " seconds.\n"
                   << "  - It took you " << 4-tries1 << "/4 attempts."
                   << endl;
              cout << endl;
              tries1 = 4;
              streak++;
              break;
            }
          }
        }
      }
    }
//---------------------------------------------
    if(gameOption == 2){
      int randNum2 = rand() % fiveLetterWord.size();
      string ogWord2 = fiveLetterWord[randNum2];
      tries2 = 6;
      numLetter = 5;
          cout << endl;
          cout << "To get started, enter your first 5 letter word.\n"
               << "You have 6 attempts to guess the random word.\n"
               << "The timer will start after your first word entry.\n"
               << "Try to guess the word within 40 seconds.\n"
               << endl;
      while (tries2 != 0){
        time_t startTime = time( NULL); //for timer
        cout << endl;
        cout << "Please enter word -->  ";
        cin >> guessedWord;
        cout << endl;
        transform(guessedWord.begin(), guessedWord.end(), guessedWord.begin(),[](unsigned char c){ return std::tolower(c); }); //lowercase
        if(guessedWord.length() < 5 || guessedWord.length() > 5){
          cout << "Invalid word entry - please enter a word that is 5 characters long." << endl;
        }
        else{
          sort(listOfWords.begin(),listOfWords.end());
          result = binarySearch(guessedWord,listOfWords);
          if (result == -1){
            cout << "Not a playable word, please select another word." << endl;
            }
          else{
            temp1.push_back(guessedWord);
            addLettersToBoard(numLetter,fiveLetterBoard,numB,temp1,guessedWord,ogWord2,5);
            numB--;
            tries2--;
            if (guessedWord == ogWord2){
              elapsedSeconds = difftime( time( NULL), startTime);
              cout << endl;
              cout << "Nice Work!  You guessed the correct word\n"
                   << "  -You completed the board in: " << elapsedSeconds << " seconds.\n"
                   << "  - It took you " << 6-tries2 << "/6 attempts."
                   << endl;
              cout << endl;
              numWins++;
              streak++;
              break;
            }
          }
        }
      }
    }
      if (tries1 == 0){ //lose thingy      //remember to add back tries 2
        elapsedSeconds = difftime( time( NULL), startTime);
        if (elapsedSeconds > 20){
          cout << endl;
          cout << "Your time has expired.  Try again.\n"
               << "  - You are " << elapsedSeconds-20 << " seconds over the 20 second time limit." << endl;
          //cout << endl;
        }
        else{
          longestStreak.push_back(streak);
          streak = 0;
          cout << endl;
          cout << "Maximum amount of attempts have been reached. Try again." << endl;
          cout << endl;
        }
      }
      if(tries2 == 0){
        elapsedSeconds = difftime( time( NULL), startTime);
        if (elapsedSeconds > 40){
          cout << endl;
          cout << "Your time has expired.  Try again.\n"
               << "  - You are " << elapsedSeconds-40 << " seconds over the 20 second time limit." << endl;
          //cout << endl;
        }
        else{
        longestStreak.push_back(streak);
          streak = 0;
          cout << endl;
          cout << "Maximum amount of attempts have been reached. Try again." << endl;
          cout << endl;
        }
      }
  }
//---------------------------------------------
  int averageTime;
  int total = 0;
  int max = 0;
  longestStreak.push_back(streak);
  for(int i=0; i < timeTotal.size(); i++){
    total += timeTotal[i];
    if(numWins != 0){ 
      averageTime = (total / numWins);
    }
  }
  for (int i = 0; i < longestStreak.size();i++){ //max algorithm
    if (longestStreak[i] > max){
      max = longestStreak[i];
    }
  }
  if (max == 0){ //check to see if never pushed back into a vector
    max = numWins;
  }
  // loop to exit the game and to see the overall stats of the game
  if(gameOption == 3){
    cout << endl;
    cout << "Overall Stats: \n"
         << "  - You guessed: " << numWins << endl
         << "  - Your longest streak is: " << max << endl;
    if (numWins == 0){
      cout << "  - Average word completion time: N/A" << endl;
    }  
    else{
      cout << "  - Average word completion time: " << averageTime << endl;
    }
      cout << "Exiting program";
    }
  cout << endl;
   return 0;
}