# class3

## 宿題 1 　掛け算、割り算に対応する

### 方針

evaluate 関数のなかで、掛け算割り算を評価する部分と足し算引き算を評価する部分に分ける。
evaluate_mult_div()関数内では、tokens を前から線形探索し、新しい new_tokens というリストに再格納していく。掛け算記号か割り算記号があればその前後の数字を演算し、new_tokens リストの末尾の数字を計算結果に書き換える。
そのあと、evaluate_plus_minus が実行され、new_tokens を前から線形探索し、加算減算を順番にしていき答えを出す。

### 計算量

tokens 配列の長さを n とすると、evaluate_mult_div()でリストを先頭から末尾まで線形探索するので evaluate_mult_div()の計算量は O(n)。evaluate_plus_minus()も同様に O(n)なのでコード全体の計算量は O(n)である。

### 他の方法

evaluate_mult_div()の探索では、掛け算や割り算の演算子がなくても線形探索をしてリストをコピーしなおす部分が無駄である。式全体のうちどこにかける記号と割る記号があるか分かればその必要はないので、かける記号と割る記号があるかを配列に保存しておき、順々に演算を処理していけば無駄が省ける。

木構造を用いて計算式を表現することもできる。
![image](https://user-images.githubusercontent.com/58587065/119826318-da7fa300-bf32-11eb-9714-6bbdf8f9a449.png)
これを用いれば木構造を構築し、深さの深い方から計算してノードを置き換えていけば計算をすることができる。

## 宿題 2：テストケース

```
 "1+2"
 "2-1"
 "1.0+2.1-3"
 "1+2*3"
 "1.0*3*0.2"
 "1.0*3*0.2+1"
 "1.0*3*0.2+2*3.5/5"
 "3/1.0"
 "(3+4*(2-1))/5"
 "3*(1+2)*4+2*6/3"
 "(3*4/2+5)-((14-3)/3-2)"
 "(3*4/2+5)-((14-3)/3-2)+1.5"
```

宿題 3 の部分も含めて、このようなテストケースを考えた。<br>

- '+', '-', '\*', '/'が混合した計算式になること<br>
  → 優先順位が正確に計算されているか？
- '\*', '/'の演算が'+', '-'を挟んで離れた場所に現れていること<br>
  → 複数回の掛け算と割り算の演算があっても正確に動作するか？
- A\*B\*C などの 3 つの数字の連続した掛け算・割り算があること
  →A×B、A÷B という形以外でも正常に動作するか
- ()があること<br>
  → 宿題 3 の()への対応が上手くいっているか
- ()が離れた場所にあること<br>
  → 複数回の()の演算が上手くいっているか
- ()が入れ子になっていること<br>
  → 逐次的でない構造の式に対応できているか

などを意識して洗い出した。実際、テストケースを追加した際にバグを発見することが 3 回ほどあった。少ないテストケースで動くと安心しないことが大切。

また、モジュール化されていると、小数に対するテストケースを掛け算割り算のテストケースであまり考慮しなくてよかったり、掛け算割り算の入ったテストケースでエラーが出たときに足し算割り算や文字列の読み取りに誤りがある可能性を考えなくてよいのでテストを踏まえて考えやすかった。

## 宿題 3：()への対応

### 方針

開き括弧'('があったトークンのインデックスを記録しておき、tokens の先頭から順に線形探索を行う。閉じ括弧')'があったら、一番最後に追加された開き括弧の一から閉じ括弧の位置までを evaluate する。開き括弧があった位置に括弧内の計算結果を代入することを繰り返し、最後には一つの数字になる。この時、式全体を括弧でくくるようにしておくことで一番外側の計算を行う。

### 計算量

tokens 配列を先頭から線形探索しながら掛ける割るの計算と足し引きの計算をしながら進んでいくので、計算量は掛ける割るの計算に加えてさらに n 回増える。
オーダーとしては O(n)のままだが実行時間は 1.5 倍になってしまう。

### 他の方法

宿題 1 で書いた木構造を用いれば、同じように優先度を考えた木の構築が出来れば計算量は掛け算割り算のみの時と変わらず計算できる。
