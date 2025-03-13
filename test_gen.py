# python 3.9.2
from random import choices, randrange
import string
from itertools import permutations, islice
import sys

words_number_per_word_len = int(sys.argv[1]) # 10000 perf run; 1000 verif run

test_input = []

for l in range(3, 13): # 3, ... , 12 lengths of words
	for i in range(words_number_per_word_len):
		random_string = ''.join(choices(string.ascii_letters, k=l))
		perm_num = randrange(1, 3)
		perm_list = list(islice(permutations(random_string), perm_num))
		for s in perm_list:
			test_input.append(''.join(s))

print(f"test file n: {len(test_input)}")
# write test_input to the file
with open("big_n_input", "w") as f:
	f.write(' '.join(test_input))



