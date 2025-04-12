#include <iostream>
#include <fstream>
#include "charList.h"
#include "get_sorted_symbol_list.h"
#include "ablinklist.h"

double get_arith_code(std::ifstream& coding_file, SymbolList sorted_symbol_list);

int main() {
	std::ifstream coding_file, decoding_file;
	std::ofstream coded_file, decoded_file;
	SymbolList sorted_symbol_list;
	ListNode<Symbol>* pcurrent_symbol_node;
	double arith_code;

	coding_file.open("short_testbench_ver1.txt", std::ios::in);
	get_sorted_symbol_list(coding_file, sorted_symbol_list);
	// print_symbol_list(sorted_symbol_list);
	coding_file.clear();
	coding_file.seekg(std::ios::beg);
	arith_code = get_arith_code(coding_file, sorted_symbol_list);
	std::cout << "arithmetic code: " << arith_code << std::endl;

	return 0;
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
	print_symbol_list(sorted_symbol_coord);
	return (upper_lim + lower_lim) / 2;
}

