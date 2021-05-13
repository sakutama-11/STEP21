# Q2
from score_checker import calculate_score

def make_alp_list(str):
    alp_list = [0] * 26
    for c in str:
        ascii = ord(c) - ord("a")
        alp_list[ascii] += 1
    return alp_list

def make_alp_dict(words):
    alp_dict = []
    for word in words:
        alp_dict.append((make_alp_list(word), word))
    return alp_dict

def search_anagram(word, alp_dict):
    target = make_alp_list(word)
    anagram = ""
    max_score = 0
    for alp_word in alp_dict:
        flg = 0
        for c in alp_word[1]:
            ascii = ord(c) - ord("a")
            if target[ascii] < alp_word[0][ascii]:
                flg = 1
                break
        if flg == 0 and calculate_score(alp_word[1]) > max_score:
            max_score = calculate_score(alp_word[1])
            anagram = alp_word[1]
    return anagram

def main():
    f = open("words.txt", "r")
    dictionary = f.read().splitlines()
    f.close()
    alp_dictionary = make_alp_dict(dictionary)
    for file in ["small", "medium", "large"]:
        i = open(file + ".txt", "r")
        inputs = i.read().splitlines()
        i.close()
        o = open(file + "_answer.txt", "w")
        for input in inputs:
            anagram = search_anagram(input, alp_dictionary)
            print(anagram, file=o)
        

if __name__ == "__main__":
    main()