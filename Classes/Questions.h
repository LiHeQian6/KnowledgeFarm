#ifndef __QUESTIONS_H__
#define __QUESTIONS_H__


class Questions {
	int num1;
	std::string signal1;
	int num2;
	std::string signal2;
	int num3;
	int result;
public:
	Questions(int num1, std::string signal1, int num2, std::string signal2, int num3, int result) :num1(0), signal1(""), num2(0), signal2(""), num3(0), result(0) {
		this->num1 = num1;
		this->num2 = num2;
		this->num3 = num3;
		this->signal1 = signal1;
		this->signal2 = signal2;
		this->result = result;
	};
	std::string getQuestions();
	int getAnswers();
};

#endif 