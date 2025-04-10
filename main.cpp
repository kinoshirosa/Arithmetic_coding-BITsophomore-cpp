#include <iostream>
#include <fstream>
#include "charList.h"
#include "get_sorted_symbol_list.h"

int main() {
	std::ifstream coding_file, decoding_file;
	std::ofstream coded_file, decoded_file;
	SymbolList sorted_symbol_list;
	ListNode<Symbol>* pcurrent_symbol_node;

	coding_file.open("short_testbench_ver1.txt", std::ios::in);
	get_sorted_symbol_list(coding_file, sorted_symbol_list);
	pcurrent_symbol_node = sorted_symbol_list.GetHead()->next;
	while (pcurrent_symbol_node != nullptr) {
		std::cout << "symbol: " << pcurrent_symbol_node->data.get_sym()
			<< "\tfreq: " << pcurrent_symbol_node->data.get_num() << std::endl;
		pcurrent_symbol_node = pcurrent_symbol_node->next;
	}

	return 0;
}
