#include <stdio.h>
#include <stdlib.h>

struct stack {
	int array[100];
	int top;
};

int is_emputy(struct stack s) {
	if (s.top == 0)
		return 1;
	else
		return 0;
}

int push(struct stack s, int data) {
	if (!s.top)
		s.top = 0;
	s.top += 1;
	s.array[s.top] = data;
	return 1;
}

int pop(struct stack s) {
	if (is_emputy(s)) {
		return 0;
	} else {
		int data = s.array[s.top];
		s.top -= 1;
		return data;
	}
}
