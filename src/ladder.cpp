
void error(string word1, string word2, string msg){
    std::cerr << word1 << ' ' << word2 << ' ' << msg << std::endl; 
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){

}

bool is_adjacent(const string& word1, const string& word2){

}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    std::queue<std::vector<std::string>> ladderQ; 
    ladderQ.push(begin_word);
    std::set<std::string> visited;
    visited.insert(begin_word);
    while(!ladderQ.empty()){
        std::string ladder = ladderQ.top();
        ladderQ.pop();
        std::string last_word = ladder[ladder.size()] ; 
        for(auto word : word_list){
            if(is_adjacent(last_word , word)){
                if(visited.find(word) == visited.end() ){
                    visited.insert(word);
                    std::vector<std::string> new_ladderQ = ladderQ;
                    new_ladderQ.push_back(word);
                    if(word == end_word)
                        return new_ladderQ;
                    ladderQ.push(new_ladderQ); 
                }
            }
        }
    }
}

void load_words(set<string> & word_list, const string& file_name){

}

void print_word_ladder(const vector<string>& ladder){
    for(auto word : ladder){
        std::cout << word << ' '; 
    }
    std::cout << std::endl;     

}

#define myAssert(e) {std::cout << #e << ((e) ? "passed" : " failed") << std::endl;}
void verify_word_ladder(){
    std::set<std::string> word_list;
    load_words(word_list , "words.txt");
    myAssert(generate_word_ladder("cat" , "dog" , word_list).size() == 4);
    myAssert(generate_word_ladder("marty" , "curls" , word_list).size() == 6);
    myAssert(generate_word_ladder("code" , "data" , word_list).size() == 6);
    myAssert(generate_word_ladder("work" , "play" , word_list).size() == 6);
    myAssert(generate_word_ladder("sleep" , "awake" , word_list).size() == 8);
    myAssert(generate_word_ladder("car" , "cheat" , word_list).size() == 4);

}
