#include <iostream>
#include <string>
using namespace std;

class Stack {
private:
	char* stack;
	int capacity;
	int top;
	void Double() {
		capacity *= 2;
		char* newstack = new char[capacity];
		for (int i = 0; i < capacity / 2; i++) {
			newstack[i] = stack[i];
		}
		delete[]stack;
		stack = newstack;
	}
public:
	Stack() {
		stack = new char[capacity];
		capacity = 1;
		top = -1;
	}
	bool Empty() {
		return top == -1;
	}
	int Top() {
		if (!Empty()) return stack[top];
	}
	void Push(char push) {
		if (top == capacity - 1) Double();
		stack[++top] = push;
	}
	void Pop() {
		if (!Empty()) top--;
	}
};

bool Operator(char i) {
	if (i == '+' || i == '-' || i == '*' || i == '/') return true;
	else return false;
}

bool Operand(char i) {
	if (!Operator(i) && i != '(' && i != ')') return true;
	else return false;
}

int Priority(char i) {
	if (i == '*' || i == '/') return 1;
	else if (i == '+' || i == '-') return -1;
	else return 0;
}

string Infix2Posfix(string in) {
	string out;
	Stack opt;
	opt.Push('N');
	int l = in.length();
	for (int i = 0; i < l; i++) {
		if (Operand(in[i])) out += in[i]; 
		else if (in[i] == '(') opt.Push(in[i]);
		else if (in[i] == ')') {					//pop remaining operator before (
			while (opt.Top() != 'N' && opt.Top() != '(') {
				out += opt.Top();
				opt.Pop();
			}
			opt.Pop();
		}
		else if (Operator(in[i])) {
			while (opt.Top() != 'N' && opt.Top() != '(' && Priority(opt.Top()) >= Priority(in[i])) {
				out += opt.Top();
				opt.Pop();
			}
			opt.Push(in[i]);
		}
	}
	//pop out all remaining 
	while (opt.Top() != 'N') {
		out += opt.Top();
		opt.Pop();
	}
	return out;
}


int main() {
	string in = "((A/B-C)+(D*E))-(A*C)";
	cout<<Infix2Posfix(in)<<endl;


	system("pause");
	return 0;
}