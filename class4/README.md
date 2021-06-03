## ディレクトリ構成

この class4 ディレクトリ配下に配布された data ディレクトリを展開してください。

```
class4
├── data
│   ├── graph_small.png
│   ├── links_small.txt
│   ├── links.txt
│   ├── pages_small.txt
│   └── pages.txt
├── README.md
└── wikipedia_bfs.cc
```
c++実行環境が整っている方は
```class4/ にて実行
g++ wikipedia_bfs.cc -o wikipedia_bfs.out
./wikipedia_bfs.out
```

c++実行環境は
- Win<br>
  https://qiita.com/whim0321/items/ed76b490daaec152dc69<br>
  https://qiita.com/nsd24/items/805d0b53c67a1043e819

- Mac<br>
  ターミナルで行けるらしい？
  
## 方針
  1. キューを使った幅優先探索で、探索されたノードと探索経路の一つ前の対応を保存するmap、prev_nodesを作成(始点の一つ前は-1にしておく)
  2. 目的のノードを発見したら終了
  3. 終点ノードからprev_nodesを再帰的に検索してさかのぼり、始点ノードにたどり着いたら0を返し、再帰関数の返り値に1を足していくことによって距離を算出する。

## 時間計算量
read_pages...O(V)
read_links...O(E)
get_id_of_page...O(V)
path_search_by_bfs...O(V+E)
print_path(再帰)...O(V)
最も時間がかかったのはpath_search_by_bfsだったので全体の計算量のオーダーはO(V+E)
## 空間計算量
最初に書いた時は、6.4GBでメモリが足りずbad_allocationになってしまった。以下の点を修正した。
https://github.com/sakutama-11/STEP21/commit/19484241359eb39ed9cc0cde60ae041eb147ec9e#diff-4e11399e67efb66d84224176d5a82cb81bad44bc46cf19e82e61a8d7a3a4a8f0
1. 幅優先探索において、探索された点の<始点からの距離><一つ前のノード>を共に保存していたので、一つ前のノードのみを保存するようにした。
2. ノードのidをstring型で保存していたサンプルコードをそのまま使っていたためint型に直した
