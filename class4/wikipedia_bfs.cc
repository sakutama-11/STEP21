#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

void read_pages(string filename, map<string, string> &pages){
  ifstream file(filename);
  string data;
  while (getline(file, data)) {
    auto index = data.find('\t');
    auto id = data.substr(0, index);
    auto title = data.substr(index + 1, data.size() - id.size() - 1);
    pages[id] = title;
  }
}

void read_links(string filename, map<string, set<string>> &links){
  ifstream file(filename);
  string data;
  while (getline(file, data)) {
    auto index = data.find('\t');
    auto from = data.substr(0, index);
    auto to = data.substr(index + 1, data.size() - from.size() - 1);
    links[from].insert(to);
  }
}


/*! @brief 始点と終点のページ名から該当するページのidを返す
 @param[in] start 始点ページ名
 @param[in] dist 終点ページ名
 @param[in] pages <id, ページ名>のマップ
 @param[out] start_id 始点ノードid
 @param[out] dist_id 終点ノードid
*/

void get_id_of_page(string start, string dist, map<string, string> pages, string &start_id, string &dist_id) {
  bool s_found = false, d_found = false;
  for (const auto& page : pages) {
    if (page.second == start) {
      start_id = page.first;

    } 
    else if (page.second == dist) {
      dist_id = page.first;
    }
    if (s_found && d_found) return;
  }
}


/*! @brief 幅優先探索によって始点ノードから終点ノードまでの最短経路を探索する
 @param[in] start 始点ノードid
 @param[in] dist 終点ノードid
 @param[in] links <ノードid, 接続先ノードidの集合>のマップ
 @param[out] distances <ノードid, <始点からの距離, 一つ前のノードid>>のマップ
 @return startからdistまでの最短距離
*/

int path_search_by_bfs(string start, string dist, map<string, set<string>> links, map<string, pair<int, string>> &distances) {
  // map<page_id, <distance, prev_node>>
  queue<string> q;
  q.push(start);
  distances[start] = make_pair(0, "-1");
  if (start == dist) return 0;
  while (!q.empty()) {
    string node = q.front();
    q.pop();
    int d = distances[node].first;
    for (const auto& child : links[node]) {
      if (distances.find(child) == end(distances)) { // not visited
        distances[child] = make_pair(d + 1, node);
        q.push(child);
        if (child == dist) return distances[child].first;
      }
    }
  }
  return -1;
}


/*! @brief startからendまでの最短経路を標準出力する再帰関数
 @param[in] distances <ノードid, <始点からの距離, 一つ前のノードid>>のマップ
 @param[in] pages <ノードid, <始点からの距離, 一つ前のノードid>>のマップ
 @param[in] node printするノードid
*/

void print_path(map<string, pair<int, string>> distances, map<string, string> pages, string node) {
  string prev = distances[node].second;
  if (prev == "-1") {
    cout << pages[node];
    return;
  }
  print_path(distances, pages, prev);
  cout << " -> " << pages[node];
}

int main() {
  map<string, string> pages;
  map<string, set<string>> links;

  read_pages("data/pages.txt", pages);
  cout << "pages readed" << endl;
  read_links("data/links.txt", links);
  cout << "links readed" << endl;
  string start = "Google";
  string dist = "渋谷";
  string start_id, dist_id;
  get_id_of_page(start, dist, pages, start_id, dist_id);
  cout << "got page_id" << endl;

  map<string, pair<int, string>> distances;
  int distance = path_search_by_bfs(start_id, dist_id, links, distances);

  if (distance >= 0) {
    cout << "The distance from " << start << " to " << dist << " is " << distance << "." << endl;
  }
  else {
    cout << start << " to " << dist << " is not connected." << endl;
  }

  print_path(distances, pages, dist_id);
  cout << endl;
  return 0;
}