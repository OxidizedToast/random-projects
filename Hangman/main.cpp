#include <algorithm>
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <vector>


void check_if_gamemode_number_allowed(int number){
  if (number != 1 && number != 2 && number !=3) {
    std::cout << "Only use given options" << std::endl;
    exit(1);
  }
}

std::string lower_case(std::string word){
  std::transform(word.begin(), word.end(), word.begin(), ::tolower);
  return word;
}

std::string gamemode_file_choser(std::string gamemode){
  std::string file_name = lower_case(gamemode);
  std::string file_path = "modes/" + file_name + ".txt";
  std::ifstream file(file_path);
  if (!file){
    std::cerr << "Could not open file " << file_path << std::endl;
    exit(1);
  }

  srand(time(0));
  int random_line_number = (rand() % 30) + 1;
  std::string line;
  for (int current_line = 1; std::getline(file, line); ++current_line){
     if (current_line == random_line_number) {
            // 'line' is the variable for the word chosen
            system("clear");
            std::cout << "Time to start guessing..." << std::endl;
            sleep(1);
            break;
      }
  }

  file.close();
  return line;
}

// void guessing was edited by ai due to my code not working, see Hangman/snip/guessing to see original unfinished part
void guessing(std::string answer_to_game) {
    system("clear");
    std::cout << "The word is " << answer_to_game.length() << " letters long" << std::endl;
    std::cout << "Start guessing!" << std::endl;

    int lifes = 7;
    char guess;
    std::vector<char> wrong_letters;  // Store incorrect guesses
    std::vector<char> correct_letters; // Store correct guesses

    while (lifes > 0) {
        std::cout << "\nCurrent progress: ";
        for (size_t i = 0; i < answer_to_game.length(); i++) {
            bool guessed = false;
            for (char c : correct_letters) {
                if (answer_to_game[i] == c) {
                    guessed = true;
                    break;
                }
            }
            if (guessed) {
                std::cout << answer_to_game[i] << " ";  // Show correct guesses
            } else {
                std::cout << "_ ";  // Show underscore for unguessed letters
            }
        }
        std::cout << std::endl;

        std::cin >> guess;

        // Check if the guess is already made
        if (std::find(correct_letters.begin(), correct_letters.end(), guess) != correct_letters.end()) {
            std::cout << "You've already guessed '" << guess << "'! Try a different letter." << std::endl;
            continue; // Skip the rest of the loop and ask for a new guess
        }

        bool found = false;
        // Check for correct guesses
        for (int i = 0; i < answer_to_game.length(); i++) {
            // Prevent guessing the same letter more than once
            if (std::find(correct_letters.begin(), correct_letters.end(), guess) != correct_letters.end()) {
                std::cout << "You've already guessed '" << guess << "'!" << std::endl;
                break;  // Exit the loop if the guess was already made
            }

            if (guess == answer_to_game[i]) {
                found = true;
                correct_letters.push_back(guess); // Add the correct guess
                std::cout << guess << " was found in: " << i << std::endl;
            }
        }

        // Handle wrong guess
        if (!found) {
            std::cout << guess << " isn't found in the word" << std::endl;
            lifes--;
            std::cout << "You have " << lifes << " lifes remaining" << std::endl;
            wrong_letters.push_back(guess);
        }

        // Print incorrect guesses
        std::cout << "Incorrect guesses: ";
        for (char wrong : wrong_letters) {
            std::cout << wrong << " ";
        }
        std::cout << std::endl;

        // Check if the word is fully guessed
        bool won = true;
        for (size_t i = 0; i < answer_to_game.length(); i++) {
            bool guessed = false;
            for (char c : correct_letters) {
                if (answer_to_game[i] == c) {
                    guessed = true;
                    break;
                }
            }
            if (!guessed) {
                won = false;
                break;
            }
        }

        if (won) {
            std::cout << "Congratulations! You guessed the word: " << answer_to_game << std::endl;
            return;
        }
    }

    std::cout << "Game over! The word was: " << answer_to_game << std::endl;
}

int main(){

  system("clear");
  std::cout << "Welcome to hangman!" << std::endl;
  std::cout << "Would you like to play:" << std::endl;
  std::cout << "Easy[1], Medium[2], Hard[3]" << std::endl;
  int game_difficutly;
  std::cin >> game_difficutly;
  check_if_gamemode_number_allowed(game_difficutly);
  std::string selected_gamemode;
  switch(game_difficutly){
    case 1:
      selected_gamemode = "Easy";
      break;
    case 2:
      selected_gamemode = "Medium";
      break;
    case 3:
      selected_gamemode = "Hard";
      break;
  }
  std::cout << "You chose " + selected_gamemode << std::endl;
  gamemode_file_choser(selected_gamemode);
  
  const std::string answer = gamemode_file_choser(selected_gamemode);
  guessing(answer);
  return 0;
}
