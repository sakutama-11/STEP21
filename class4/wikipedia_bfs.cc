#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

void read_pages(string filename, map<int, string> &pages){
  ifstream file(filename);
  string data;
  while (getline(file, data)) {
    auto index = data.find('\t');
    auto id = data.substr(0, index);
    int i = stoi(id);
    auto title = data.substr(index + 1, data.size() - id.size() - 1);
    pages[i] = title;
  }
}

void read_links(string filename, map<int, set<int>> &links){
  ifstream file(filename);
  string data;
  while (getline(file, data)) {
    auto index = data.find('\t');
    auto from = data.substr(0, index);
    int f = stoi(from);
    auto to = data.substr(index + 1, data.size() - from.size() - 1);
    int t = stoi(to);
    links[f].insert(t);
  }
}


/*! @brief 始点と終点のページ名から該当するページのidを返す
 @param[in] start 始点ページ名
 @param[in] dist 終点ページ名
 @param[in] pages <id, ページ名>のマップ
 @param[out] start_id 始点ノードid
 @param[out] dist_id 終点ノードid
*/

void get_id_of_page(string start, string dist, map<int, string> pages, int &start_id, int &dist_id) {
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
 @param[out] prev_nodes <ノードid,  一つ前のノードid>のマップ
 @return distにたどり着けばtrue, たどり着かなければfalse
*/

bool path_search_by_bfs(int start, int dist, map<int, set<int>> links, map<int, int> &prev_nodes) {
  queue<int> q;
  q.push(start);
  prev_nodes[start] = -1;
  if (start == dist) return 0;
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    for (const auto& child : links[node]) {
      if (prev_nodes.find(child) == end(prev_nodes)) { // not visited
        prev_nodes[child] = node;
        q.push(child);
        if (child == dist) return true;
      }
    }
  }
  return false;
}


/*! @brief startからnodeまでの最短経路を標準出力する再帰関数
 @param[in] prev_nodes <ノードid, 一つ前のノードid>のマップ
 @param[in] pages <ノードid, <始点からの距離, 一つ前のノードid>>のマップ
 @param[in] node printする終点ノードid
 @return startからnodeまでの距離
*/

int print_path(map<int, int> prev_nodes, map<int, string> pages, int node) {
  int prev = prev_nodes[node];
  if (prev == -1) {
    cout << pages[node];
    return 0;
  }
  int d = print_path(prev_nodes, pages, prev);
  cout << " -> " << pages[node];
  return ++d;
}

int main() {
  map<int, string> pages;
  map<int, set<int>> links;

  read_pages("data/pages.txt", pages);
  read_links("data/links.txt", links);

  string start = "Google";
  string dist = "渋谷";
  int start_id, dist_id;
  get_id_of_page(start, dist, pages, start_id, dist_id);

  map<int, int> distances;
  bool found = path_search_by_bfs(start_id, dist_id, links, distances);

  if (found) {
    int distance = print_path(distances, pages, dist_id);
    cout << endl;
    cout << "The distance from " << start << " to " << dist << " is " << distance << "." << endl;
  }
  else {
    cout << start << " to " << dist << " is not connected." << endl;
  }
  return 0;
}