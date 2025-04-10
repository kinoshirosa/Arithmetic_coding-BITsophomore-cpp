#ifndef _CHARLIST_H_
#define _CHARLIST_H_
#include "cpplist.h"
#include "ablinklist.h"

class Symbol {
	// data is the alphabet, and we set up a nuw var to storage frequencies
private:
	char symbol;
	unsigned int num;
public:
	Symbol(char sym = '\0', unsigned int n = 1) {
		symbol = sym;
		num = n;
	}
	void set_sym(char sym) {
		symbol = sym;
	}
	char get_sym() {
		return symbol;
	}
	unsigned int get_num() {
		return num;
	}

	void operator++ (int) {
		num++;
	}

	void operator= (const Symbol& sym0) {
		symbol = sym0.symbol;
		num = sym0.num;
	}
	bool operator== (const Symbol& sym0) {
		return symbol == sym0.symbol;
	}
	bool operator!= (const Symbol& sym0) {
		return symbol != sym0.symbol;
	}
	bool operator> (const Symbol& sym0) {
		return num > sym0.num;
	}
	bool operator< (const Symbol& sym0) {
		return num < sym0.num;
	}
};

class SymbolList :
	public List<Symbol> {
};

#endif // !_CHARLIST_H_

