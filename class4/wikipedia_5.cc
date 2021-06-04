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
 @param[in] pages <id, ページ名>のマップ
 @return 始点ページのid
*/

int get_id_of_page(string start, map<int, string> pages) {
  for (const auto& page : pages) {
    if (page.second == start) {
      return page.first;
    }
  }
  cout << start << " is not included in this graph." << endl;
  exit(1);
}


/*! @brief 幅優先探索によって始点ノードから終点ノードまでの最短経路を探索する
 @param[in] start 始点ノードid
 @param[in] dist 終点ノードid
 @param[in] links <ノードid, 接続先ノードidの集合>のマップ
 @param[out] distances <ノードid,  始点ノードからの距離>のマップ
*/

void bfs_for_distance_6(int start, map<int, set<int>> links, vector<int> &distances) {
  queue<int> q;
  q.push(start);
  distances[start] = 0;
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    for (const auto& child : links[node]) {
      try {
        distances.at(child);
      }
      catch (out_of_range e) {// not visited
        int distance = distances[node] + 1;
        distances[child] = distance;
        if (distance < 5) q.push(child);
      }
    }
  }
  return;
}


int main() {
  map<int, string> pages;
  map<int, set<int>> links;

  read_pages("data/pages.txt", pages);
  read_links("data/links.txt", links);

  int n = pages.size();

  string start = "Google";
  int start_id = get_id_of_page(start, pages);

  cout << "loaded" << endl;
  vector<int> distances(n);
  bfs_for_distance_6(start_id, links, distances);

  int cnt_inaccessible = 0;
  for (const auto &p : pages) {
    try {
      distances.at(p.first);
    } catch (out_of_range e) {
      cout << p.second << endl;
      cnt_inaccessible++;
    }
  }
  cout << "There are " << cnt_inaccessible << " pages inaccessible from " << start << endl;
  return 0;
}