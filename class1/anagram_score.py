# Q2
from score_checker import calculate_score
def make_alp_list(str):
    # make list that the number of times each alphabet is used in str.
    alp_list = [0] * 26
    for c in str:
        ascii = ord(c) - ord("a")
        alp_list[ascii] += 1
    return alp_list

def make_alp_dict(words):
    # Returns: alp_dict [list] [([a=0, b=2, ...], word), ([], str), ([], str), ...]
    alp_dict = []
    for word in words:
        alp_dict.append((make_alp_list(word), word))
    return alp_dict

def search_anagram(word, alp_dict):
    target = make_alp_list(word)
    for alp_word in alp_dict:
        enough_chars = True
        alp_list = alp_word[0]
        word = alp_word[1]
        for c in word:
            ascii = ord(c) - ord("a")
            if target[ascii] < alp_list[ascii]:
                enough_chars = False
                break
        if enough_chars == True:
            return word
    return ""

def main():
    f = open("words.txt", "r")
    dictionary = f.read().splitlines()
    f.close()
    sorted_dictionary = sorted(dictionary, key=calculate_score, reverse=True)
    alp_dictionary = make_alp_dict(sorted_dictionary)
    for file in ["small", "medium","large"]:
        i = open(file + ".txt", "r")
        inputs = i.read().splitlines()
        i.close()
        o = open(file + "_answer.txt", "w")
        for input in inputs:
            anagram = search_anagram(input, alp_dictionary)
            print(anagram, file=o)

if __name__ == "__main__":
    main()