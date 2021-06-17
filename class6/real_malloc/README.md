# Real malloc challenge!

## Instruction

Your task is implement a better malloc logic in [malloc.c](malloc.c) to improve the speed and memory usage.

## How to build & run a benchmark

```
# build
make
# run a benchmark
make run
```

If the commands above don't work, you can build and run the challenge directly by running:

```
gcc -Wall -O3 -lm -o malloc_challenge.bin main.c malloc.c simple_malloc.c
./malloc_challenge.bin
```

## Acknowledgement

This work is based on [xharaken's malloc_challenge.c](https://github.com/xharaken/step2/blob/master/malloc_challenge.c). Thank you haraken-san!

# My Work

## 方針

- 最初に発見した十分なメモリ領域を使用する first-fit になっているのを、best-fit にして効率化する。
- 線形リストを最初から最後まで探索し、十分なメモリ領域のうち最小の領域を採用する。

## 結果

[malloc.c](https://github.com/sakutama-11/STEP21/blob/master/class6/real_malloc/malloc.c)<br>
![image](https://user-images.githubusercontent.com/58587065/122464084-5f6d5200-cff1-11eb-952b-83fee1fccf33.png)

challenge1 や challenge2 では、そもそも malloc/free の回数が少ないため utilization はほとんど変わらなかった。<br>
実行時間は、線形リストを最初から最後まで探索するため first-fit より長い時間がかかった。<br>

(worst-fit の場合 ↓)<br>
![image](https://user-images.githubusercontent.com/58587065/122464160-7dd34d80-cff1-11eb-870c-8cef9af34833.png)

worst-fit にすると、空き領域がコマ切れになり空き領域のリストのノード数が大きくなるので、探索時間が長くなる。

## やろうとして出来なかったアイディア

### best-fit を高速化する

空き領域の線形リストを、領域の大きい(または小さい)箇所から順にソートしておき、十分な空き領域と不十分な空き領域の境界部分の空き領域を採用することで、first-fit と同じ時間で探索できるのではないかと考えた。<br>
その代わり、挿入時に挿入箇所を探索する必要がある分遅くなる。<br>
[malloc_sort.c](https://github.com/sakutama-11/STEP21/blob/master/class6/real_malloc/malloc_sort.c) 　に実装をしたが、insert 時の順番の制御が上手くいかず、思うように並ばなかった。
![image](https://user-images.githubusercontent.com/58587065/122464934-5fba1d00-cff2-11eb-9ccd-3bf981171df6.png)

### index を作る

線形リストのほかに、0-4000 の 200 刻みなどと決めて、ソートした空き領域の線形リストのうち、0、200、400…に最も近い metadata を配列に格納しておくことで、リストの途中から探索できるようにして探索時の探索時間を高速化する。

### 隣り合っているノードの結合

空き領域を探索する際に、\*metadata が一つ前の metadata のポインタからサイズを足した場所であった場合、二つの領域は隣り合っているとわかる。これを結合することによって、より効率的にメモリを使うことができる。
