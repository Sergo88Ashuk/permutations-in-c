#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RUSSIAN 33 // TODO: implement it
#define ENGLISH 26
#define ALPHABET_LEN ENGLISH


struct sym_cnt {
	int word_number;
	int cnt[ALPHABET_LEN];
};

struct words_list {
	int word_number;
	struct words_list* next;
};

struct perms_list {
	struct words_list* wl_head;
	struct perms_list* next;
};

static int sym_to_int(char sym)
{
	char wc =  sym;
	if (wc >= 'A' && wc <= 'Z') return wc - 'A';
	if (wc >= 'a' && wc <= 'z') return wc - 'a';
	return -1;
}

int cmp_sym_cnt(const void* rhs, const void* lhs)
{
	struct sym_cnt* r_sc = (struct sym_cnt*) rhs;
	struct sym_cnt* l_sc = (struct sym_cnt*) lhs;
	int res = 0;
	for(int i = 0; i < ALPHABET_LEN; ++i) {
		if (r_sc->cnt[i] > l_sc->cnt[i]) { 
			return -1;
		}
		if (r_sc->cnt[i] < l_sc->cnt[i]) {
			return 1;
		}
	}
	return 0;
}

void print_sym_cnt(struct sym_cnt* sc)
{
	printf("word[%d]: ", sc->word_number);
	for (int i = 0; i < ALPHABET_LEN; ++i) {
		printf("[%c]:%d; ", i + 'a', sc->cnt[i]);
	}
	printf("\n");
}

void print_sym_cnt_array(struct sym_cnt* sym_cnt_arr, int input_len)
{
	for (int i = 0; i < input_len; ++i) {
		print_sym_cnt(&sym_cnt_arr[i]);
	}
	printf("\n");
}

// TODO: check for return errs
// TODO: multithread it
struct sym_cnt* create_sym_cnt_array(int words_cnt, char* words[])
{
	struct sym_cnt* sc = NULL;
	sc = malloc(words_cnt * sizeof(struct sym_cnt));

	if (!sc) return sc;

	for(int wrd_idx = 0; wrd_idx < words_cnt; ++wrd_idx) {
		int wrd_len = strlen(words[wrd_idx]);
		sc[wrd_idx].word_number = wrd_idx;
		for(int sym_idx = 0; sym_idx < wrd_len; ++sym_idx) {
			int sym_val = sym_to_int(words[wrd_idx][sym_idx]);
			sc[wrd_idx].cnt[sym_val]++;
		}
	}

	return sc;
}

void destroy_sym_cnt_array(struct sym_cnt* sym_cnt_arr)
{
	free(sym_cnt_arr);
}

// TODO: sort without struct copying
void sort_sym_cnt_array(struct sym_cnt* sym_cnt_arr, int arr_len)
{
	qsort(sym_cnt_arr, arr_len, sizeof(struct sym_cnt), cmp_sym_cnt);
}

void print_perms(struct perms_list* plist, char* words[])
{
	while(plist) {
		struct words_list* wl = plist->wl_head;
		while (wl) {
			printf("%s ", words[wl->word_number]);
			wl = wl->next;
		}
		plist = plist->next;
		printf("\n");
	}
}

struct perms_list* create_perms_list(struct sym_cnt* sym_cnt_arr, int input_len)
{
	struct perms_list* pl_head = malloc(sizeof(struct perms_list));

	pl_head->next = NULL;
	pl_head->wl_head = malloc(sizeof(struct words_list));

	pl_head->wl_head->word_number = sym_cnt_arr[0].word_number;
	pl_head->wl_head->next = NULL;

	for (int i = 1; i < input_len; ++i) {
		if (cmp_sym_cnt(&sym_cnt_arr[i-1], &sym_cnt_arr[i]) != 0) {
			// new pl_head
			struct perms_list* new_pl_head = malloc(sizeof(struct perms_list));
			new_pl_head->wl_head = malloc(sizeof(struct words_list));
			new_pl_head->wl_head->word_number = sym_cnt_arr[i].word_number;
			new_pl_head->wl_head->next = NULL;
			new_pl_head->next = pl_head;
			pl_head = new_pl_head;
		} else {
			// append to list pl_head->wl_head
			struct words_list* new_wl_head = malloc(sizeof(struct words_list));
			new_wl_head->word_number = sym_cnt_arr[i].word_number;
			new_wl_head->next = pl_head->wl_head;
			pl_head->wl_head = new_wl_head;
		}
	}
	return pl_head;
}

void destroy_perms_list(struct perms_list* head)
{
	while(head) {
		struct words_list* wl_head = head->wl_head;
		while (wl_head) {
			struct words_list* tmp_wl_head = wl_head;
			wl_head = wl_head->next;
			free(tmp_wl_head);
		}
		struct perms_list* tmp_head = head;
		head = head->next;
		free(tmp_head);
	}
}
