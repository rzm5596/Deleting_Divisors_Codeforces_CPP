/**
 * The deleting divisors problem from Codeforces
 * If both players play optimally, who will win?
 * Taking turns, each player must choose a factor of the given number that is not 1 or itself
 * That number is then sutracted from the given number, and that is the new number
 * If the number can no longer be factored besides 1 and itself, the current player loses
 * @author Ryan Mayes
 */



#include <io.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h> 
#include "deleting_divisors.h"



int main(int argc, char const* argv[]) {

    // Opening file for use
    std::fstream new_file;
    new_file.open("dd_input.txt",std::ios::in); 

    if (new_file.is_open()){ // Making sure the file is opened correctly

        std::string line_string;            // String for reading from the file
        std::vector<int> results_vector;    // Contains the results of the tests
        std::vector<int> test_vector;       // Contains each test case
        int test_case;                      // Individual test case
        int maximum = 0;                    // Maximum of test cases, for setting up vector for tested paths

        getline(new_file, line_string);                 // Getting the first line, which is how many test cases there are
        int test_no = std::stoi (line_string, nullptr); // Converting the string to an int for the loop

        for(int i = 0; i < test_no; i++){ // For each test case

            getline(new_file, line_string);                 // Get the next line
            test_case = std::stoi (line_string, nullptr);   // Converting the string to an int for the test
            test_vector.push_back(test_case);                // Adding the number to the test cases

            if(test_case > maximum){ // Setting the maximum if needed
                maximum = test_case;
            }
        }

        std::vector<int> tested_paths(maximum+1);   // Vector for all tested paths
        tested_paths.assign(maximum+1, -1);         // Setting the default value for each value to -1

        // For each test case, store the result in the vector
        for(int i = 0; i < test_no; i++){
            results_vector.push_back(deleting_divisors_test(test_vector[i], tested_paths));
        }

        new_file.close(); // Closing file after use

        std::ofstream out_file("dd_output.txt"); // Opening the file to write to
        
        if(out_file.is_open()){ // Checking that the file opened correctly

            std::string b = "Bob";
            std::string a = "Alice";

            for(int i = 0; i < test_no; i++){ // For each test case, add the winner to the file

                // Alice start first, so if the test is 0 Bob wins, otherwise Alice wins
                if(results_vector[i]  == 0){ 
                    out_file << "" << b << "\n";
                }
                else{
                    out_file << "" << a << "\n";
                }
            }
            
            out_file.close(); // Closing the file after use
        }
    }
}



/**
 * Recursive function that checks whether the number can win or not
 * If the number is prime, it is an instant failure state
 * If a number that can be given to an opponent is a failure state, it is a winning state
 * If the numbers that can be given to an opponent are all winning states, it is a failure state
 * @param test_number The number currently being tested
 * @param tested_paths A vector representing which paths have been previously checked
 * @return Returns a 0 if the path leads to a failure state, or a 1 if the path leads to a winning state
 */
int deleting_divisors_test(int test_number, std::vector<int> &tested_paths){
    
    // Checking if the number is below 4, the first composite number
    if(test_number < 4){
        return 0;
    }

    // Checking if the path has already been checked
    if(tested_paths[test_number] != -1){
        return tested_paths[test_number];
    }

    // Otherwise we need to manually check the path
    for(int i = 2; i < sqrt(test_number)+1; i++){

        // Checking that the current number is composite
        if(test_number % i == 0){

            // Checking if the factors of the current number result in fail states
            if(deleting_divisors_test(test_number-i, tested_paths) == 0){

                // If one of the factors leads to a fail state, we win
                return tested_paths[test_number] = 1;
            }
        }
    }

    // This number is a fail state, so set the path to 0
    return tested_paths[test_number] = 0;
}