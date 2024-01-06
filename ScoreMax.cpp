#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::vector<int> string_to_digits(std::string s){
 
    std::vector<int> out; 
 
    for(int i = 0; i < s.size(); i++){
 
       std::string digit_string;
       digit_string.push_back(s[i]);
 
       int digit_int = std::stoi(digit_string);
 
       out.push_back(digit_int);
 
    }
 
    return out;
 
}

bool possible_sequence(std::string digits, std::string sequence){
    
    int sequence_number = 0;
    int digits_number = 0;


    std::vector <int> dig = string_to_digits(digits);
    std::vector <int> seq = string_to_digits(sequence);


    for (int i = 0; i < 10; i++) {
        
        for (int j = 0; j < seq.size(); j++){
            
            if (seq[j] == i){
                
                sequence_number = sequence_number + 1;

            }
        
        }

        for (int k = 0; k< dig.size(); k++) {

            if (dig[k] == i){

                digits_number = digits_number + 1;

            }

       }

       if(sequence_number > digits_number){

            return false;

        }
        sequence_number = 0;
        digits_number = 0;

    }

    return true;

}


int score(std::string s, const std::vector<int>& values){

    int length = 1;
    int start = 0;
    int result = 0;

    std::vector<int> vector_digit;
    vector_digit = string_to_digits(s);
    std::vector<int> multiplier(vector_digit.size(),1);

    for(int i = 0; i < vector_digit.size(); i++){

        if (vector_digit[i] == vector_digit[i+1] - 1){

            length = length + 1;

        }

        else{

            for(int j = start; j < length + start; j++){

                multiplier[j] = multiplier[j] * length;

            }

            start = i + 1;
            length = 1;

        }

    }

    for(int i = 0; i < vector_digit.size(); i++){

        result = result + (values[vector_digit[i]] * multiplier[i]);

    }
 
    return result;

}

int get_best_sequence(std::string digits, const std::vector<std::string>& allowed, const std::vector<int>& values, std::string& best_sequence){

   int best_score = 0;
   int sequence_score = 0;
   int answer = 0;
   
   std::vector<int> cur_score;
   std::vector<std::string> cur_sequence;

    for(int i = 0; i < allowed.size(); i++){

       if (possible_sequence(digits, allowed[i])) {

           sequence_score = score(allowed[i], values);
           cur_score.push_back(sequence_score);
           cur_sequence.push_back(allowed[i]);

        }
  
    }

    if (cur_score.size() == 0){

        return 0;

    }

    best_score = cur_score[0];

    for(int j = 0; j < cur_score.size(); j++){

        if (cur_score[j] >= best_score){

           best_score = cur_score[j];
           answer = j;

        }  

    }

    best_sequence = cur_sequence[answer];
    return best_score;
  
}



int main(){

    std::ifstream allowedfile; 
    std::string allowedfilename;
    std::cin >> allowedfilename;

    allowedfile.open(allowedfilename);
    std::vector<std::string> allowed_vector;
    std::string temp1;
    while(allowedfile >> temp1){

        allowed_vector.push_back(temp1); 

    }
    allowedfile.close();  

    std::ifstream valuefile;
    std::string valuefilename;
    std::cin >> valuefilename;

    valuefile.open(valuefilename);
    std::vector<int> value_vector;
    int temp2;
    while(valuefile >> temp2){

        value_vector.push_back(temp2); 

    }
    valuefile.close();  
  
    std::ifstream digitfile; 
    std::string digitfilename;
    std::cin >> digitfilename;

    digitfile.open(digitfilename);
    std::vector<std::string> digit_vector;
    std::string temp3;
    while(digitfile >> temp3){

        digit_vector.push_back(temp3); 

    }
    digitfile.close();  
  
    std::ofstream outfile; 
    std::string outputfilename;
    std::cin >> outputfilename;

    outfile.open(outputfilename);

    std::string best_sequence;

    for(int i = 0; i < digit_vector.size(); i++){

        int score = get_best_sequence(digit_vector[i],allowed_vector,value_vector, best_sequence);
        outfile << digit_vector[i] << " " << best_sequence << " " << score << std::endl;

    }
    outfile.close();

}