#Q1
def sorted_str(str):
    char_list = list(str)
    char_list.sort()
    sorted_str = "".join(char_list)
    return sorted_str

def sort_words(words):
    sorted_words = []
    for word in words:
        sorted_words.append((sorted_str(word), word))
    sorted_words.sort(key=lambda x: x[0])
    return sorted_words

def search_anagram(word, words_list):
    target = sorted_str(word)
    l = 0
    r = len(words_list)-1
    found_words = []
    while(l < r):
        pivot = (l+r)//2
        if words_list[pivot][0] == target:
            found = words_list.pop(pivot)
            found_words.append(found[1])
            r = min(r, len(words_list))
        elif words_list[pivot][0] < target:
            l = pivot + 1
        else:
            r = pivot - 1
    return found_words

def main():
    f = open("words.txt", "r")
    words = f.read().splitlines()
    f.close()
    sorted_words = sort_words(words)
    word = input("word: ")
    anagrams = search_anagram(word, sorted_words)
    for anagram in anagrams:
        print(anagram)
if __name__ == "__main__":
    main()