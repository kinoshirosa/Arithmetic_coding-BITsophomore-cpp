#include <iostream>
#include <fstream>
#include "charlist.h"

ListNode<Symbol> find_maxfreq(SymbolList&);
ListNode<Symbol> find_minfreq(SymbolList& symbol_list);
void print_symbol_list(SymbolList& sorted_symbol_list);
void get_sorted_symbol_list(std::ifstream& coding_file, SymbolList& target_symbol_list);