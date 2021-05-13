#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define REP(i,n) for(int i=0; i<(n); i++)
#define REP2(i,x,n) for(int i=x; i<(n); i++)
#define ALL(n) begin(n),end(n)
const long long INF = numeric_limits<long long>::max();
//与えられた文字列を辞書ファイルから探して返す

// fileの文字列を1行ずつベクタに格納
vector<string> read_line(string filename) {
    vector<string> lines;
    ifstream ifs(filename);
    string str;
    while (getline(ifs, str)) {
        lines.push_back(str);
    }
    return lines;
}

// 辞書の各単語をソートした新しい辞書を作成
vector<pair<string, string>> make_sorted_words_vec(vector<string> words) {
    vector<pair<string, string>> sorted_words;
    for (string w : words) {
        string sorted_w = w;
        sort(sorted_w.begin(), sorted_w.end());
        sorted_words.push_back(make_pair(sorted_w, w));
    }
    sort(sorted_words.begin(), sorted_words.end());
    return sorted_words;
}

// ソートされた辞書sorted_dictから文字列inputのアナグラムとなっている全ての文字列を二分探索してベクタに格納して返す
vector<string> search_anagrams(string input, vector<pair<string, string>> sorted_dict) {
    vector<string> anagrams;
    string target = input;
    sort(target.begin(), target.end());
    int l=0, r=0;
    r = sorted_dict.size() -1;
    int pivot = 0;
    while(l < r) {
        int pivot = (l+r) /2;
        string word = sorted_dict.at(pivot).first;
        if (word == target) {
            anagrams.push_back(sorted_dict.at(pivot).second);
            sorted_dict.erase(sorted_dict.begin() + pivot);
            r = min(r, (int)sorted_dict.size());
        } else if(word < target) {
            l = pivot + 1;
        } else {
            r = pivot - 1;
        }
    }
    return anagrams;
}

int main()
{
    vector<string> words_vec = read_line("words.txt");
    vector<pair<string, string>> sorted_words = make_sorted_words_vec(words_vec);
    string in;
    cout << "input string: "<< endl;
    cin >> in;
    vector<string> anagrams = search_anagrams(in, sorted_words);
    for(string anagram : anagrams) {
        cout << anagram << endl;
    }
    return 0;
}