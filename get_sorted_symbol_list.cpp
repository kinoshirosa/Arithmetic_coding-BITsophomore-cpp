#include "get_sorted_symbol_list.h"

void get_sorted_symbol_list(std::ifstream& coding_file, SymbolList& target_symbol_list) {
	SymbolList symbol_list;
	SymbolList sorted_symbol_list;
	ListNode<Symbol> new_symbol_node;
	ListNode<Symbol>* pnew_symbol_node;
	ListNode<Symbol>* pcurrent_symbol_node;
	ListNode<Symbol> max_symbol_node;
	char new_char;
	char current_char;
	Symbol new_symbol;
	unsigned int total_num = 0;

	if (!coding_file.is_open()) {
		std::cout << "file open failure!" << std::endl;
	}
	else {
		// struct the linklist of alphabet frequency
		while (!coding_file.eof()) {
			coding_file >> new_char;
			new_symbol.set_sym(new_char);
			total_num++;
			pcurrent_symbol_node = symbol_list.ablinklist<Symbol>::Find_value(new_symbol);
			if (pcurrent_symbol_node == nullptr) {
				symbol_list.Insert(new_symbol, symbol_list.GetLength());
				continue;
			}
			pcurrent_symbol_node->data++;
		}
		sorted_symbol_list.ablinklist<Symbol>::Find_index(0)->data.set_num(total_num);
	}

	// sort the frequency and form it into an array for easier read-only datastruct
	const int array_length = symbol_list.GetLength();
	while (symbol_list.GetLength() != 0) {
		max_symbol_node = find_minfreq(symbol_list);
		sorted_symbol_list.Insert(max_symbol_node.data);
		symbol_list.Remove_value(max_symbol_node.data);
	}

	target_symbol_list = sorted_symbol_list;
}

ListNode<Symbol> find_maxfreq(SymbolList& symbol_list) {
	ListNode<Symbol>* pcurrent_symbol_node = symbol_list.GetHead()->next;
	ListNode<Symbol> max_symbol_node = *pcurrent_symbol_node;
	while (pcurrent_symbol_node != nullptr) {
		if (max_symbol_node.data < pcurrent_symbol_node->data) {
			max_symbol_node = *pcurrent_symbol_node;
		}
		pcurrent_symbol_node = pcurrent_symbol_node->next;
	}
	return max_symbol_node;
}
ListNode<Symbol> find_minfreq(SymbolList& symbol_list) {
	ListNode<Symbol>* pcurrent_symbol_node = symbol_list.GetHead()->next;
	ListNode<Symbol> min_symbol_node = *pcurrent_symbol_node;
	while (pcurrent_symbol_node != nullptr) {
		if (min_symbol_node.data > pcurrent_symbol_node->data) {
			min_symbol_node = *pcurrent_symbol_node;
		}
		pcurrent_symbol_node = pcurrent_symbol_node->next;
	}
	return min_symbol_node;
}

void print_symbol_list(SymbolList& sorted_symbol_list) {
	ListNode<Symbol>* pcurrent_symbol_node = sorted_symbol_list.GetHead();
	while (pcurrent_symbol_node != nullptr) {
		std::cout << "symbol: " << pcurrent_symbol_node->data.get_sym()
			<< "\tfreq: " << pcurrent_symbol_node->data.get_num() << std::endl;
		pcurrent_symbol_node = pcurrent_symbol_node->next;
	}
}

double get_arith_code(std::ifstream& coding_file, SymbolList sorted_symbol_list) {
	double total_num = sorted_symbol_list.Find_index(0)->data.get_num();
	double upper_lim = 1;
	double lower_lim = 0;
	double upper_percent = 1;
	double lower_percent = 0;
	double ul_length = upper_lim - lower_lim;
	unsigned int accumulated_number = 0;
	SymbolList sorted_symbol_coord;
	ListNode<Symbol>* p = sorted_symbol_list.GetHead()->next;
	Symbol current_symbol;
	char new_char;

	while (p != nullptr) {
		current_symbol.set_num(accumulated_number);
		current_symbol.set_sym(p->get_data().get_sym());
		sorted_symbol_coord.Insert(current_symbol, sorted_symbol_coord.GetLength());
		accumulated_number += p->data.get_num();
		p = p->next;
		// we add the number to acc_num after the Insert
		// because the LinkList is just a foreward-only list
		// we can only get the numbers after the node, so we must get lower_percent from current node
		// then get upper_percent from next node
		// when is comes to the most frequent letter 'e' for example
		// the acc_num of 'e' is 0 but its own frequncy, bucause 0 is its lower_percent
	}
	if (!coding_file.is_open()) {
		std::cout << "file open failure!" << std::endl;
		return -1;
	}
	else {
		while (!coding_file.eof()) {
			coding_file >> new_char;		// read one char each time for coding
			current_symbol.set_sym(new_char);
			p = sorted_symbol_coord.Find_value(current_symbol);
			lower_percent = p->data.get_num() / total_num;
			if (p->next == nullptr) {
				upper_percent = 1;
			}
			else {
				upper_percent = p->next->data.get_num() / total_num;
			}
			upper_lim = lower_lim + ul_length * upper_percent;
			lower_lim = lower_lim + ul_length * lower_percent;
			ul_length = upper_lim - lower_lim;
		}
	}
	return (upper_lim + lower_lim) / 2;
}

