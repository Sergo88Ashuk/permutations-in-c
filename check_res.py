# python 3.9.2

def create_perms_list(w2sw):
	w2sw = dict(sorted(w2sw.items(), key=lambda item: item[1]))
	w2sw_list = list(w2sw.items())
	perms = { w2sw_list[0][1] : [w2sw_list[0][0]] }
	for i in range(1, len(w2sw_list)):
		perm = w2sw_list[i][1]
		if perm in perms:
			perms[perm].append(w2sw_list[i][0])
		else:
			perms[perm] = [ w2sw_list[i][0] ] 
	result = []
	for k, v in perms.items():
		result.append(v)
	return result

def create_list_of_sorted_words(words):
	w2sw = {}
	for w in words:
		wrd = w.lower()
		w2sw[w] = ''.join(sorted(wrd))
	return w2sw

def parse_test_input(f):
	perms_list = []
	with open(f, "r") as file:
		input_str = file.read()
		words = input_str.split()
		word_to_sorted_word = create_list_of_sorted_words(words)
		perms = create_perms_list(word_to_sorted_word)
		return perms

def get_perms_list_from_app(f):
	with open(f, "r") as file:
		input_str = file.read().splitlines()
		result = []
		for s in input_str:
			l = s.split()
			result.append(l)
		return result
	
def compare_perms_lists(c_pl, py_pl):
	c_pl_sets = []
	py_pl_sets = []
	# set each list in c_pl
	for elem in c_pl:
		c_pl_sets.append(set(elem))
	for elem in py_pl:
		py_pl_sets.append(set(elem))
	# set each list in py_pl
	for s in c_pl_sets:
		if s in py_pl_sets:
			py_pl_sets.remove(s)
	if len(py_pl_sets) == 0:
		print("TEST: OK")
	else:
		print("TEST: ERROR")
	
def check_test(test_name):
	print(f'{test_name} status: ')
	py_pl = parse_test_input(test_name)
	c_pl = get_perms_list_from_app(test_name+'_res')
	compare_perms_lists(c_pl, py_pl)

check_test('test0')
check_test('big_n_input')
