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

def print_anagram(word, words_list):
    target = sorted_str(word)
    l = 0
    r = len(words_list)-1
    while(l < r):
        pivot = (l+r)//2
        if words_list[pivot][0] == target:
            found = words_list.pop(pivot)
            print(found[1])
            r = min(r, len(words_list))
        elif words_list[pivot][0] < target:
            l = pivot + 1
        else:
            r = pivot - 1

def main():
    f = open("words.txt", "r")
    words = f.read().splitlines()
    f.close()
    sorted_words = sort_words(words)
    word = input("word: ")
    print_anagram(word, sorted_words)
if __name__ == "__main__":
    main()