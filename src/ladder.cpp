#include "ladder.h"
void error(string word1, string word2, string msg){
    std::cerr << word1 << ' ' << word2 << ' ' << msg << std::endl; 
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    std::size_t word1Size = str1.size();
    std::size_t word2Size = str2.size();
    int i = 0 , j = 0 , numEdits = 0; 
    while(i < word1Size && j < word2Size){
        if(numEdits > d)
            return false;

        if(str1[i] == str2[j]){
            ++i;
            ++j;
        } else {
            ++numEdits;
            if(word1Size > word2Size){
                ++i; 
            }
            if(word1Size < word2Size){
                ++j; 
            } 
        }
    }

    numEdits += (word1Size - i) + (word2Size - j); 
    return numEdits <= d; 
}

bool is_adjacent(const string& word1, const string& word2){
// 
    // covers cases other than inserting and deleting a letter 
    std::size_t word1Size = word1.size();
    std::size_t word2Size = word2.size();
    if(word1Size == word2Size){ // should this handle just the replacement case ot
        int differingLettersCount = 0; 
        for(int i = 0; i < word1Size; ++i){ 
            if(word1[i] != word2[i]){
                ++differingLettersCount;
            }
        }    

        if(differingLettersCount <= 1)
            return true; 

    } else {
        return edit_distance_within(word1 , word2 , 1);
    }
    return false; 
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if(word_list.find(end_word) == word_list.end()){
        // std::cout << "word was not found" << std::endl; 
        return {};
    }
    
    std::vector<std::string> startLadder; 
    startLadder.push_back(begin_word); //

    std::queue<std::vector<std::string>> ladderQ; 
    ladderQ.push(startLadder); // 

    std::set<std::string> visited;
    visited.insert(begin_word); // 
    while(!ladderQ.empty()){
        std::vector<std::string> ladder = ladderQ.front();
        ladderQ.pop();
        std::string last_word = ladder[ladder.size()-1] ;  
        for(auto word : word_list){
            if(is_adjacent(last_word , word)){
                if(visited.find(word) == visited.end() ){
                    visited.insert(word);
                    std::vector<std::string> new_ladderQ = ladder;
                    new_ladderQ.push_back(word);
                    if(word == end_word)
                        return new_ladderQ;
                    ladderQ.push(new_ladderQ); 
                }
            }
        }
    }
    return {}; 
}

void load_words(set<string> & word_list, const string& file_name){
    std::ifstream in(file_name);

    if(!in){
        std::cerr << "file did not open? " << std::endl; 
    }

    std::string word; 
    while(std::getline(in , word)){
        std::transform(word.begin() , word.end() , word.begin(), ::tolower); 
        word_list.insert(word);
    }
    
    in.close();
// 
    // for(auto w : word_list){
    //     std::cout << w << ' '; 
    // }
}

void print_word_ladder(const vector<string>& ladder){
    if(ladder.empty()){
        std::cout << "No word ladder found.\n"; 
    } else {
        std::cout << "Word ladder found: "; 
        for(auto word : ladder){
            std::cout << word << ' '; 
        }
        std::cout << std::endl;
    }
}

#define myAssert(e) {std::cout << #e << ((e) ? " passed" : " failed") << std::endl;}
void verify_word_ladder(){
    std::set<std::string> word_list;
    load_words(word_list , "./src/words.txt");

    myAssert(generate_word_ladder("cat" , "dog" , word_list).size() == 4);
    print_word_ladder(generate_word_ladder("cat" , "dog" , word_list)); 

    myAssert(generate_word_ladder("Marty" , "curls" , word_list).size() == 6);
    print_word_ladder(generate_word_ladder("Marty" , "curls" , word_list)); 

    myAssert(generate_word_ladder("code" , "data" , word_list).size() == 6);
    print_word_ladder(generate_word_ladder("code" , "data" , word_list)); 

    myAssert(generate_word_ladder("work" , "play" , word_list).size() == 6);
    print_word_ladder(generate_word_ladder("work" , "play" , word_list)); 

    myAssert(generate_word_ladder("sleep" , "awake" , word_list).size() == 8);
    print_word_ladder(generate_word_ladder("sleep" , "awake" , word_list)); 

    myAssert(generate_word_ladder("car" , "cheat" , word_list).size() == 4);
    print_word_ladder(generate_word_ladder("car" , "cheat" , word_list)); 

    myAssert(generate_word_ladder("car" , "smeegledanglesborgjargon" , word_list).size() == 0);
    print_word_ladder(generate_word_ladder("car" , "smeegledanglesborgjargon" , word_list)); 
}


/*

    // std::cout << "Starting edit_distance_within" << std::endl; 
    int str1Size=str1.size();
    int str2Size = str2.size();
    std::vector<int> prev(str2Size+1 , 0);
    std::vector<int> curr(str2Size+1 , 0); 
    for(int i = 0; i <=str2Size; i++){
        prev[i] = i; 
    }
    for(int i = 1; i <= str1Size; i++){
        curr[0] = i;
        for(int j = 1; j <= str2Size; j++){
            if(str1[i-1] == str2[j-1]){
                curr[j] = prev[j-1]; 
            } else {
                curr[j] = 1 + min({curr[j-1] , prev[j] , prev[j-1]});
            }
        }
        if(curr[str2Size] > d){
            return false; 
        }
        prev = curr; 
    }
    int x = prev[str2Size]; 
    return x <= d; 

*/