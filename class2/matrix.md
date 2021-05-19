# 宿題1：行列積を求めるプログラムの実行時間を調べる
## 方針
### Python
https://github.com/sakutama-11/STEP21/tree/master/class2/matrix_py
1. N×Nの行列を用意する。
2. 行列積を計算(calc_matrix_production())。実行時間を計測する。
3. 0からnまで繰り返し、各大きさの行列の行列積の計算時間をリストtime_listに格納。
4. matplotlibでグラフ化する。計算量がO(N)となることを予想し、得られた実行時間とNの関係を3次近似したグラフを赤で比較のため表示。

### C言語
https://github.com/sakutama-11/STEP21/tree/master/class2/matrix_c
matrix.cで行列積を計算し、0からNまでの大きさの行列積の計算時間をtime.txtに出力。テキストファイルから配列を読み込み、time_graph.pyでグラフ化した。
1. N×Nの行列を用意する。
2. 行列積を計算(calc_prod())。実行時間を計測する。
3. 各Nで3回計測し、最大値を除く2回の平均を取ることでノイズを減らす。
4. テキストファイルに出力する。
5. 出力したテキストデータをtime_graph.pyで読み込み、matplotlibでグラフ化する。計算量がO(N)となることを予想し、得られた実行時間とNの関係を3次近似したグラフを赤で比較のため表示。

## 結果
### pyの結果
https://github.com/sakutama-11/STEP21/blob/master/class2/matrix_py/time_py_200.png 
![image](https://user-images.githubusercontent.com/58587065/118750374-40688c80-b89a-11eb-992d-9b6a7c13ba3e.png)
<br>
### cの結果
https://github.com/sakutama-11/STEP21/blob/master/class2/matrix_c/time_c_200.png
![image](https://user-images.githubusercontent.com/58587065/118750321-2333be00-b89a-11eb-8ccd-fdb1ff083b17.png)

### O(N^3)の確認
行列積の計算部分のコードは、3重ループとなっているので、O(N^3)であると考えられる。

グラフを見て確認すると、np.polyfit(x, y, 3)を用いて3次方程式の近似式のうち3次の項の係数をaとし、モデル式をy=ax^3として赤で表示した。他の項の係数の影響か上手くフィットしなかったが、定数倍して調整してやるとぴったりと一致したので計算量がN^3の定数倍になっていることは確認できた。

### ノイズについて
pythonとC言語で、どちらも実行時間はきれいにN^3の定数倍とはならず、高周波のノイズが見られた。これはPCの実行時のCPU使用状況等マシンの状態によるものではないかと思った。

### 言語による比較
CはPythonより常に100倍ほど早いことが確認された。
