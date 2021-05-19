#Q1
def sorted_str(str):
    char_list = list(str)
    char_list.sort()
    sorted_str = "".join(char_list)
    return sorted_str

def make_sorted_words_list(words):
    sorted_words = []
    for word in words:
        sorted_words.append((sorted_str(word), word))
    sorted_words.sort(key=lambda x: x[0])
    return sorted_words

def nearby_linear_search(i, words_list, found_words):
    # find words same as index of i in words_list by linear search
    target = words_list[i][0]
    j = 1
    while words_list[i+j][0] == target:
        found_words.append(words_list[i+j][1])
        j += 1
    j = -1
    while words_list[i+j][0] == target:
        found_words.append(words_list[i+j][1])
        j -= 1

def search_anagram(word, words_list):
    """Search word by binary search.
    Args:
        word: [string] the target of search
        words_list: [list] [(sorted word [str], word[str]), (), (), ...] sorted by first str of tuple
    
    Returns:
        found_words: [list] [str, str, ...] found anagram words

    """
    target = sorted_str(word)
    l = 0
    r = len(words_list) - 1
    found_words = []
    while l < r:
        pivot = (l + r) // 2
        if words_list[pivot][0] == target:
            found_words.append(words_list[pivot][1])
            nearby_linear_search(pivot, words_list, found_words)
            return found_words
        elif words_list[pivot][0] < target:
            l = pivot + 1
        else:
            r = pivot - 1
    return found_words

def make_words_dict(words):
    """make dict for search anagrams.
    Args:
        words: [list] [str, str, str, ...] the words list
    
    Returns:
        words_dict: [dict] {sorted_str: [str, str, str...], sorted_str:[], ...}

    """
    words_dict = {}
    for word in words:
        sorted_word = sorted_str(word)
        if sorted_word in words_dict:
            words_dict[sorted_word].append(word)
        else:
            words_dict[sorted_word] = [word]
    return words_dict

def search_by_dict(word, words_dict):
    target = sorted_str(word)
    return words_dict[target]

def main():
    f = open("words.txt", "r")
    words = f.read().splitlines()
    f.close()
    word = input("word: ")
    """
    # use binary search
    sorted_words = make_sorted_words_list(words)
    anagrams = search_anagram(word, sorted_words)
    """
    # use dict for search
    words_dict = make_words_dict(words)
    anagrams = search_by_dict(word, words_dict)
    for anagram in anagrams:
        print(anagram)

if __name__ == "__main__":
    main()