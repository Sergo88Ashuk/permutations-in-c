struct sym_cnt; // table with count of each symbol in word; permutation means sym_cnt[word0] == sym_cnt[word1]
struct words_list; // linked list or permutation words
struct perms_list; // linked list of words_list

extern struct sym_cnt* create_sym_cnt_array(int words_cnt, char* words[]);
extern void sort_sym_cnt_array(struct sym_cnt* sym_cnt_arr, int arr_len);
extern struct perms_list* create_perms_list(struct sym_cnt* sym_cnt_arr, int input_len);
extern void print_perms(struct perms_list* plist, char* words[]);
extern void destroy_perms_list(struct perms_list* head);
extern void destroy_sym_cnt_array(struct sym_cnt* sym_cnt_arr);

int main(int argc, char* argv[])
{
	// parse input
	int input_len = argc - 1;
	char** input = argv + 1;

	// build sym_cnt array: O(n * k), n = input len, k = max input word len (maybe it is a constant actully?)
	struct sym_cnt* sym_cnt_arr = create_sym_cnt_array(input_len, input);

	// sort sym_cnt array: O(nlogn)
	sort_sym_cnt_array(sym_cnt_arr, input_len);

	// create output (list of ptrs to list of word idxs): O(n)
	struct perms_list* result_list =  create_perms_list(sym_cnt_arr, input_len);

	// output permutations
	print_perms(result_list, input);

	destroy_sym_cnt_array(sym_cnt_arr);
	destroy_perms_list(result_list);

	return 0;
}
