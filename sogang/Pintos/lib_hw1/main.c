#include "bitmap.c"
#include "debug.h"
#include "hash.c"
#include "limits.h"
#include "round.h"
#include <stdio.h>
#include "list.c"
#include <string.h>
#include <stdlib.h>

struct list_item {
	struct list_elem elem;
	int data;
};

struct page {
	struct hash_elem hash_elem;
	int data;
};

void square(struct hash_elem* e, void* aux);
void triple(struct hash_elem* e, void* aux);
bool compare(const struct list_elem*, const struct list_elem*, void*);
unsigned forHashFunc(const struct hash_elem* e, void* aux);
bool forHashLess(const struct hash_elem* a, const struct hash_elem* b,
	void* aux);

int main(int argc, char *argv[]) {
	struct list listArr[10];
	struct hash hashArr[10];
	struct bitmap *bitArr[10];
	FILE* fp;
	
	while (1) {
		char instruction[20];
	scanf("%s", instruction);
	if (!strcmp(instruction, "create")) {
		char* creInst = (char*)malloc(sizeof(char) * 11);
		scanf("%s", creInst);
		if (!strcmp(creInst, "list")) {
			char* name = (char*)malloc(sizeof(char) * 11);
			scanf("%s", name);
			int index = name[4] - '0';
			list_init(&listArr[index]);
		}
		else if (!strcmp(creInst, "hashtable")) {
			char creInst[11]; scanf("%s", creInst);
			int index = creInst[4] - '0';
			void* aux;
			hash_hash_func* hash;
			hash_less_func* less;
			hash = forHashFunc;
			less = forHashLess;
			hash_init(&hashArr[index], hash, less, aux);
		}
		else if (!strcmp(creInst, "bitmap")) {
			char s[11]; scanf("%s", s);
			size_t bit_cnt; scanf("%zd", &bit_cnt);
			int index = s[2] - '0';
			bitArr[index] =  bitmap_create(bit_cnt);
		}
	}
	else if (!strcmp(instruction, "delete")) {
		char delInst[10]; scanf("%s", delInst);
		if (delInst[0] == 'l') {
			int index = delInst[4] - '0';
			struct list_elem* e, *j;
			for (e = list_begin(&listArr[index]); e != list_end(&listArr[index]);
				) {
				j = list_next(e);
				list_remove(e);
				e = j;
			}
		}
		else if (delInst[0] == 'h') {
			int index = delInst[4] - '0', i;
			hash_clear(&hashArr[index], NULL);
		}
		else if (delInst[0] == 'b') {
			int index = delInst[2] - '0';
			bitmap_destroy(bitArr[index]);
		}
	}
	else if (!strcmp(instruction, "dumpdata")) {
		char* dumpInst = (char*)malloc(sizeof(char) * 11);
		scanf("%s", dumpInst);

		if (dumpInst[0] == 'l') {
			struct list_elem* e;
			int index = dumpInst[4] - '0';
			for (e= list_begin(&listArr[index]); e!= list_end(&listArr[index]);
			e = list_next(e)) {
				struct list_item* f = list_entry(e, struct list_item, elem);
				printf("%d ", f->data);
			}
			if(!(e == list_begin(&listArr[index])))printf("\n");
		}
		else if (dumpInst[0] == 'h') {
			int index = dumpInst[4] - '0', i;
			struct hash_elem* e;
			struct hash_iterator* g = (struct hash_iterator *)malloc(sizeof(struct
				hash_iterator));
			hash_first(g, &hashArr[index]);
			size_t limit = hash_size(g->hash);
			for (i = 0; i < limit;  i++) {
				e = hash_next(g);
				struct page* f = hash_entry(e, struct page, hash_elem);
				printf("%d ", f->data);
			}
			if (!(i == 0))
				printf("\n");
		}
		else if (dumpInst[0] == 'b') {
			int index = dumpInst[2] - '0', i;
			size_t limit = bitArr[index]->bit_cnt;
			for (i = 0; i < limit; i++) {
				if (bitmap_test(bitArr[index], i))
					printf("1");
				else
					printf("0");
			}
			if (i) printf("\n");
		}
	}
	else if (!strcmp(instruction, "list_push_back")) {
		char s[11];
		int index;
		struct list_item* e = (struct list_item*)malloc(sizeof(struct list_item));
		scanf("%s", s); scanf("%d", &(e->data));
		index = s[4] - '0';
		list_push_back(&listArr[index], &(e->elem));
	}
	else if (!strcmp(instruction, "list_push_front")) {
		char s[11];
		int index;
		struct list_item* e = (struct list_item*)malloc(sizeof(struct list_item));
		scanf("%s", s); scanf("%d", &(e->data));
		index = s[4] - '0';
		list_push_front(&listArr[index], &(e->elem));
	}
	else if (!strcmp(instruction, "list_front")){
		char s[11]; scanf("%s", s);
		int index = s[4] - '0';
		struct list_elem* li;
		li = list_front(&listArr[index]);
		struct list_item* f = list_entry(li, struct list_item, elem);
		printf("%d\n", f->data);
	}
	else if (!strcmp(instruction, "list_back")) {
		char s[11]; scanf("%s", s);
		int index = s[4] - '0';
		struct list_elem* li;
		li = list_back(&listArr[index]);
		struct list_item* f = list_entry(li, struct list_item, elem);
		printf("%d\n", f->data);
	}
	else if (!strcmp(instruction, "list_pop_back")) {
		char s[11]; scanf("%s", s);
		int index = s[4] - '0';
		struct list_elem* li;
		li = list_pop_back(&listArr[index]);
	}
	else if (!strcmp(instruction, "list_pop_front")) {
		char s[11]; scanf("%s", s);
		int index = s[4] - '0';
		struct list_elem* li;
		li = list_pop_front(&listArr[index]);
	}
	else if (!strcmp(instruction, "list_insert")) {
		char s[11]; scanf("%s", s); // list name input
		int index = s[4] - '0', i;
		struct list_elem* li, * current;
		current = (struct list_elem*)malloc(sizeof(struct list_elem));
		int before, cur;
		scanf("%d", &before); scanf("%d", &cur);
		for (i = 0, li = list_begin(&listArr[index]); i < before; i++) li = list_next(li);
		struct list_item* f = list_entry(current, struct list_item, elem);
		f->data = cur;
		if (before == 0) list_push_front(&listArr[index], current);
		else list_insert(li, current);
	}
	else if (!strcmp(instruction, "list_insert_ordered")) {
		char s[11]; scanf("%s", s); // list 번호 받아들이는 곳임
		int index = s[4] - '0';

		int number; scanf("%d", &number); // list 이름 다음에 오는 number 받아들이는 공간
		list_less_func *func;
		void* aux;
		func = compare;
		struct list_item* it = (struct list_item*)malloc(sizeof(struct list_item));
		it->data = number;
		list_insert_ordered(&listArr[index], &(it->elem), func, aux);
	}
	else if (!strcmp(instruction, "list_empty")) {
		char s[10]; scanf("%s", s);
		int index = s[4] - '0';
		if (list_empty(&listArr[index]))
			printf("true\n");
		else
			printf("false\n");
	}
	else if (!strcmp(instruction, "list_size")) {
		char s[10]; scanf("%s", s);
		int index = s[4] - '0';
		printf("%zd\n", list_size(&listArr[index]));
	}
	else if (!strcmp(instruction, "list_max")) {
		char s[11]; scanf("%s", s); // list 번호 받아들이는 곳임
		int index = s[4] - '0';
		list_less_func* func;
		void* aux;
		func = compare;
		struct list_elem* max;
		max = list_max(&listArr[index], func, aux);
		struct list_item* g = list_entry(max, struct list_item, elem);
		printf("%d\n", g->data);
	}
	else if (!strcmp(instruction, "list_min")) {
		char s[11]; scanf("%s", s); // list 번호 받아들이는 곳임
		int index = s[4] - '0';
		list_less_func* func;
		void* aux;
		func = compare;
		struct list_elem* min;
		min = list_min(&listArr[index], func, aux);
		struct list_item* g = list_entry(min, struct list_item, elem);
		printf("%d\n", g->data);
	}
	else if (!strcmp(instruction, "list_remove")) {
		char s[11]; scanf("%s", s); // list 번호 받아들이는 곳임
		int index = s[4] - '0', i;
		int before; scanf("%d", &before);
		struct list_elem* li;
		for (i = 0, li = list_begin(&listArr[index]); i < before; i++) li = list_next(li);
		list_remove(li);
	}
	else if (!strcmp(instruction, "list_reverse")) {
		char s[11]; scanf("%s", s); // list 번호 받아들이는 곳임
		int index = s[4] - '0', i;
		list_reverse(&listArr[index]);
	}
	else if (!strcmp(instruction, "list_sort")) {
		char s[11]; scanf("%s", s); // list 번호 받아들이는 곳임
		int index = s[4] - '0';
		list_less_func* func;
		void* aux;
		func = &compare;
		list_sort(&listArr[index], func, NULL);
	}
	else if (!strcmp(instruction, "list_splice")) {
		char s[11]; scanf("%s", s); // list 번호 받아들이는 곳임
		int index = s[4] - '0', i, j;
		int inserting; scanf("%d", &inserting);
		char d[11]; scanf("%s", d);
		int dIndex = d[4] - '0';
		int bef, end; scanf("%d %d", &bef, &end);
		struct list_elem* before, * first, * last;
		for (i = 0, before = list_begin(&listArr[index]); i < inserting; i++)
			before = list_next(before);
		for (i = 0, first = list_begin(&listArr[dIndex]); i < bef; i++)
			first = list_next(first);
		for (i = 0, last = list_begin(&listArr[dIndex]); i < end; i++)
			last = list_next(last);
		list_splice(before, first, last);
	}
	else if (!strcmp(instruction, "list_swap")) {
		char s[11]; scanf("%s", s); // list 번호 받아들이는 곳임
		int index = s[4] - '0', i, j;
		int left, right; scanf("%d %d", &left, &right);
		struct list_elem* first, * last;
		for (i = 0, first = list_begin(&listArr[index]); i < left; i++)
			first = list_next(first);
		for (i = 0, last = list_begin(&listArr[index]); i < right; i++)
			last = list_next(last);

		list_swap(first, last);
	}
	else if (!strcmp(instruction, "list_unique")) {
		char origin[10], dup[10], c;
		struct list* noo = NULL;
		void* aux;
		scanf("%s", origin);
		list_less_func* func;
		func = compare;
		if ((c = getchar()) == '\n') {
			int oriIndex = origin[4] - '0';
			list_unique(&listArr[oriIndex], noo, func, aux);
		}
		else {
			scanf("%s", dup);
			int oriIndex = origin[4] - '0', dupIndex = dup[4] - '0';
			list_unique(&listArr[oriIndex], &listArr[dupIndex], func, aux);
		}
	}
	else if (!strcmp(instruction, "hash_insert")) {
		char s[11]; scanf("%s", s);
		int index = s[4] - '0';
		struct page* pages = (struct page*)malloc(sizeof(struct page));
		scanf("%d", &pages->data);
		hash_insert(&hashArr[index], &(pages->hash_elem));
	}
	else if (!strcmp(instruction, "hash_apply")){
		char s[11], func[10]; scanf("%s", s);
		int index = s[4] - '0';
		hash_action_func* act;
		scanf("%s", func);
		if (!strcmp(func, "square")) {
			act = square;
		}
		else if (!strcmp(func, "triple")) {
			act = triple;
		}
		hash_apply(&hashArr[index], act);
	}

	else if (!strcmp(instruction, "hash_delete")) {
		char s[10]; scanf("%s", s);
		int target; scanf("%d", &target);
		int index = s[4] - '0';
		struct hash_elem* e;
		struct hash_iterator* g = (struct hash_iterator *)malloc(sizeof(struct hash_iterator));
		hash_first(g, &hashArr[index]);
		size_t limit = hash_size(g->hash);
		for (int i = 0; i < limit; i++) {
			e = hash_next(g);
			struct page* f = hash_entry(e, struct page, hash_elem);
			if (f->data == target) {
				hash_delete(&hashArr[index], e);
			}
		}
	}
	else if (!strcmp(instruction, "hash_empty")) {
		char s[11]; scanf("%s", s);
		int index = s[4] - '0';
		if (hash_empty(&hashArr[index]))
			printf("true\n");
		else printf("false\n");
	}
	else if (!strcmp(instruction, "hash_size")) {
		char s[11]; scanf("%s", s);
		int index = s[4] - '0';
		printf("%zd\n", hash_size(&hashArr[index]));
	}
	else if (!strcmp(instruction, "hash_clear")) {
		char s[11]; scanf("%s", s);
		int index = s[4] - '0';
		hash_clear(&hashArr[index], NULL);
	}
	else if (!strcmp(instruction, "hash_find")) {
		char s[11]; scanf("%s", s);
		int index = s[4] - '0';
		int target; scanf("%d", &target);
		struct hash_elem* e;
		struct hash_iterator* g = (struct hash_iterator*)malloc(sizeof(struct hash_iterator));
		hash_first(g, &hashArr[index]);
		size_t limit = hash_size(g->hash);
		for (int i = 0; i < limit; i++) {
			e = hash_next(g);
			struct page* f = hash_entry(e, struct page, hash_elem);
			if (f->data == target) {
				e = hash_find(&hashArr[index], e);
				f = hash_entry(e, struct page, hash_elem);
				printf("%d\n", f->data);
			}
		}
	}
	else if (!strcmp(instruction, "hash_replace")) {
		char s[11]; scanf("%s", s);
		int index = s[4] - '0';
		int input; scanf("%d", &input);
		struct hash_elem* e = (struct hash_elem*)malloc(sizeof(struct hash_elem));
		struct page* f = hash_entry(e, struct page, hash_elem);
		f->data = input;
		hash_replace(&hashArr[index], e);
	}
	else if (!strcmp(instruction, "bitmap_mark")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		size_t IDX; scanf("%zd", &IDX);
		bitmap_mark(bitArr[index], IDX);
	}
	else if (!strcmp(instruction, "bitmap_set_all")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		char boole[10]; scanf("%s", boole);
		if (!strcmp(boole, "false"))
			bitmap_set_all(bitArr[index], false);
		else
			bitmap_set_all(bitArr[index], true);
	}
	else if (!strcmp(instruction, "bitmap_all")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		size_t start, cnt; scanf("%zd", &start); scanf("%zd", &cnt);
		if (bitmap_all(bitArr[index], start, cnt)) printf("true\n");
		else printf("false\n");
	}
	else if (!strcmp(instruction, "bitmap_dump")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		bitmap_dump(bitArr[index]);
	}
	else if (!strcmp(instruction, "bitmap_any")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		size_t start, cnt; scanf("%zd %zd", &start, &cnt);
		if (bitmap_any(bitArr[index], start, cnt)) printf("true\n");
		else printf("false\n");
	}
	else if (!strcmp(instruction, "bitmap_contains")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		size_t start, cnt; scanf("%zd %zd", &start, &cnt);
		char d[11]; scanf("%s", d);
		bool sim;
	
		if (d[0] == 't') sim = bitmap_contains(bitArr[index], start, cnt, true);
		else sim = bitmap_contains(bitArr[index], start, cnt, false);
		if (sim) printf("true\n");
		else printf("false\n");
	}
	else if (!strcmp(instruction, "bitmap_count")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		size_t start, cnt; scanf("%zd %zd", &start, &cnt);
		char d[10]; scanf("%s", d);
		size_t sim;

		if (d[0] == 't') sim = bitmap_count(bitArr[index], start, cnt, true);
		else sim = bitmap_count(bitArr[index], start, cnt, false);
		printf("%zd\n", sim);
	}
	else if (!strcmp(instruction, "bitmap_expand")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		int exp; scanf("%d", &exp);
		size_t start = bitmap_size(bitArr[index]);
		bitArr[index]->bit_cnt += exp;
		bitmap_set_multiple(bitArr[index], start, (size_t)exp, false);
	}
	else if (!strcmp(instruction, "bitmap_flip")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		size_t idx; scanf("%zd", &idx);
		bitmap_flip(bitArr[index], idx);
	}
	else if (!strcmp(instruction, "bitmap_none")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		size_t start, cnt; scanf("%zd %zd", &start, &cnt);
		if (bitmap_none(bitArr[index], start, cnt)) printf("true\n");
		else printf("false\n");
	}
	else if (!strcmp(instruction, "bitmap_reset")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		size_t idx; scanf("%zd", &idx);
		bitmap_reset(bitArr[index], idx);
	}
	else if (!strcmp(instruction, "bitmap_scan_and_flip")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		size_t start, cnt; scanf("%zd %zd", &start, &cnt);
		char d[10]; scanf("%s", d);
		uint32_t result;
		if (d[0] == 't') result = (uint32_t)bitmap_scan_and_flip(bitArr[index], start, cnt, true);
		else result = (uint32_t)bitmap_scan_and_flip(bitArr[index], start, cnt, false);
		printf("%u\n", result);
	}
	else if (!strcmp(instruction, "bitmap_scan")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		size_t start, idx; scanf("%zd %zd", &start, &idx);
		char d[10]; scanf("%s", d);
		uint32_t size; 
		if (d[0] == 't') size = (uint32_t)bitmap_scan(bitArr[index], start, idx, true);
		else  size = (uint32_t)bitmap_scan(bitArr[index], start, idx, false);
		printf("%u\n", size);
	}
	else if (!strcmp(instruction, "bitmap_set")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		size_t idx; scanf("%zd", &idx);
		char d[10]; scanf("%s", d);
		if (d[0] == 't')	bitmap_set(bitArr[index], idx, true);
		else bitmap_set(bitArr[index], idx, false);
	}
	else if (!strcmp(instruction, "bitmap_set_multiple")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		size_t start, ind; scanf("%zd %zd", &start, &ind);
		char d[10]; scanf("%s", d);
		if (d[0] == 't') bitmap_set_multiple(bitArr[index], start, ind, true);
		else bitmap_set_multiple(bitArr[index], start, ind, false);
	}
	else if (!strcmp(instruction, "bitmap_size")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		printf("%zd\n", bitmap_size(bitArr[index]));
	}
	else if (!strcmp(instruction, "bitmap_test")) {
		char s[11]; scanf("%s", s);
		int index = s[2] - '0';
		size_t idx; scanf("%zd", &idx);
		if (bitmap_test(bitArr[index], idx)) printf("true\n");
		else printf("false\n");
	}
	else if (!strcmp(instruction, "list_shuffle")) {
	char s[11]; scanf("%s", s);
	int index = s[4] - '0';
	list_shuffle(&listArr[index]);

}
	else if (!strcmp(instruction, "quit"))
	return 0;

	}
	return 0;
}

bool compare(const struct list_elem* a, const struct list_elem* b, void* aux) {
	const struct list_item* f = list_entry(a, struct list_item, elem);
	const struct list_item* g = list_entry(b, struct list_item, elem);
	return f->data < g->data;
}

unsigned forHashFunc(const struct hash_elem* e, void* aux) {
	const struct page* p = hash_entry(e, struct page, hash_elem);
	return hash_int(p->data);
}

bool forHashLess(const struct hash_elem* a, const struct hash_elem* b,
	void* aux) {
	const struct page* p = hash_entry(a, struct page, hash_elem);
	const struct page* q = hash_entry(b, struct page, hash_elem);
	
	return p->data < q->data;
}
void square(struct hash_elem* e, void* aux) {
	struct page* p = hash_entry(e, struct page, hash_elem);
	int tr = p->data;
	tr = tr * tr;
	p->data = tr;
}
void triple(struct hash_elem* e, void* aux) {
	struct page* p = hash_entry(e, struct page, hash_elem);
	int tri = p->data;
	p->data = tri * tri * tri;
}