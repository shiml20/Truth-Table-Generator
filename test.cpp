#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<map>
using namespace std;

int n=0,flag=0;
map<string, int> save;//各个子表达式的真值
string input;  //存储中缀表达式
string output; //存储后缀表达式
string letters;//存储单个字母
stack<char> oper1;//存储操作数
vector<int> binum;//二进制数字向量
stack<string> fruit;//存储各个子命题事件
vector<int> result;//存储各命题事件结果值
stack<string> temp;//临时存储命题事件
string temp2; //存储计算的命题事件
string temp3; //临时存储temp2
stack<int> result2;
bool isletter(char c) {
	return (int(c) >= 65 && int(c) <= 90) || (int(c) >= 97 && int(c) <= 122);
}
void createnum(vector<int>& binum, int n) {
	for (int i = 0;i < n;i++) {
		binum.push_back(0);
	}
}
//创建二进制数并初始化为0，使用向量的好处是可以直接取出每一位
void changenum(vector<int>& binum, int n) {
	for (int i = 0;i < n;i++) {
		if (binum[i] == 2 && binum[i+1] != 2) {
			binum[i + 1]++;
			//cout << i + 1 << " is " << binum[i + 1] << " ";调试使用
			binum[i] = 0;
		}
	}
}
//二进制数的进位
void resetmap( string input, map<string, int>& save) {
	int flag = 0;
	int count = 0;
	for (int i = 0;i < n;i++) {
		for (int k = 0;k < i;k++) {
			if (input[k] == input[i]) {
				flag++;
			}
		}
		if (flag == 0) {
			save[letters.substr(i, 1)] = 0;
			count++;
		}
	}
}
void createmap(vector<int> binum, string input,map<string,int> &save) {
	int flag = 0;
	int count = 0;
	for (int i = 0;i < n;i++) {
		for (int k = 0;k < i;k++) {
			if (input[k] == input[i]) {
				flag++;
			}
		}
		if (flag == 0) {
			save[letters.substr(i,1)] = binum[count];
			count++;
		}
	}
}
//创建一个映射，使得各个命题事件映射到一个值
bool isoperator(string a) {
	if (a == "!" || a == "(" || a == ")" || a == "-" || a == "=" || a == "&" || a == "|") {
		return true;
	}
	else return false;
	}
//判断是否为操作数，这里判断以字符串的格式判断操作符
void intro() {
	cout << "Welcome to Truth table generator made by Serrylei" << endl;
	cout << "   " << "Input" << "   " << "Operator" << endl;
	cout << "   " << "  &  " << "   " << "     AND" << endl;
	cout << "   " << "  |  " << "   " << "      OR" << endl;
	cout << "   " << "  !  " << "   " << "     NOR" << endl;
	cout << "   " << "  -  " << "   " << "      ->" << endl;
	cout << "   " << "  =  " << "   " << "     <->" << endl;
	cout << "You can use '()' to change the priority!" << endl;
	cout << "Priority sequence：() > ! > & > | > - > =" << endl;
	cout << "Associative way : Left-associative." << endl;
	cout << "Please input the proper expression,use one letter to refer to an event：" << endl;
}
bool proper(string strori) {
	string str;
	stack<char> bracket;
	for (int i = 0;i < size(strori);i++) {
		if (strori[i] == '(') {
			bracket.push('(');
		}
		if (strori[i] == ')') {
			if (bracket.empty()) {
				return 0;
			}
			else if (bracket.top() == '(') {
				bracket.pop();
			}
		}
		if ((strori[i] != '(') && (strori[i] != ')')) {
			str.push_back(strori[i]);
		}
	}
	if (!bracket.empty()) {
		return 0;
	}
	int flag=0;
	if (size(str) == 1) {
		if (isletter(str[0])) {
			return 1;
		}
		else return 0;
	}
	if (size(str) == 2) {
		if (str[0] == '!' && isletter(str[1]) ){
			return 1;
		}
		else if (isletter(str[0]) && isletter(str[1])) {
			return 0;
		}
		else return 0;
	}
	if (size(str) > 2) {
		for (int i = 0;i < size(str)-2;i++) {
			if (!isoperator(str.substr(i, 1)) && !isletter(str[i])) {
				flag++;
			}
			else if (isletter(str[i])) {
				if (str[i + 2] == '!') {
					flag = 0;
				}
				else if (isletter(str[i + 2])) {
					flag = 0;
				}
				else if (str[i + 2] == '(') {
					flag = 0;
				}
				else flag++;
			}
		}
		if (isoperator(str.substr((size(str) - 3),1))) {
			if (isoperator(str.substr(size(str) - 2,1))&& str.substr(size(str) - 2, 1) != "!") {
				flag++;
			}
			else if (isletter(str[size(str) - 2])) {
				flag++;
			}
		}
		else if (isletter(str[size(str) - 3])) {//倒数第三个字符是字母
			if (!isoperator(str.substr((size(str) - 2),1))) {
				flag++;
			}
			else if (isoperator(str.substr((size(str) - 2), 1))) {
				if (str.substr(size(str) - 2,1) == "!") {
					flag++;
				}
			}
		}
	}
	if (flag == 0) {
		return 1;
	}
	else return 0;
}
//判断输入表达式的合法性
int prior(char a) {

	if (a == '(') {
		return 5;
	}
	else if (a == '!') {
		return 4;
	}
	if (a == '&') {
		return 3;
	}
	else if (a == '|') {
		return 2;
	}
	else if (a == '-') {
		return 1;
	}
	else if (a == '=') {
		return 0;
	}
	else return -1;
}
//确定操作数优先级，这里以字符的格式判断操作符
string changes(string &str,stack<char> &oper1,string &output, string &letters) {
	for (int i = 0;i < size(str);i++) {//将操作数按照逆波兰式规则放入操作数栈中
		//cout <<"here is "<< judge_prior(str[i]) << endl;
		//if(!oper1.empty())cout << "there is " << oper1.top()<<endl;
		if (!isoperator(str.substr(i,1)) && (int(str[i]) >= 65 && int(str[i]) <= 90) || (int(str[i]) >= 97 && int(str[i]) <= 122)) {
			output.push_back(str[i]);
			int flag = 0;
			for (int k = 0;k < i;k++) {
				if (str[k] == str[i]) {
					flag++;
				}
			}
			if (flag == 0) {
				letters.push_back(str[i]);
				n++;
			}
		}//将字母放入output队列中
		else if (isoperator(str.substr(i, 1))) {
			if (oper1.empty()) {
				oper1.push(str[i]);
				//	cout << oper1.top()<<endl;
				//	cout << flag<<endl;
				//	flag++;
			}
			else if (str[i] == ')') {
				while (!oper1.empty()) {
					if (oper1.top() != '(') {
						//cout << oper1.top()<<endl;
						output.push_back(oper1.top());
						oper1.pop();
						//	cout << "here" << endl;
					}
					else if (oper1.top() == '(') { oper1.pop(); }
				}
			}
			else if (prior(oper1.top()) == 4 && prior(str[i]) == 4) {
				oper1.pop();
			}
			else if (prior(oper1.top()) < prior(str[i])) {//高优先级直接加入
				oper1.push(str[i]);
				//cout << oper1.top()<<endl;
				//cout << count << endl;
				//count++;
			}
			else if (oper1.top() == '(') {
				oper1.push(str[i]);
			}
			else if ((oper1.top() != '(') && (prior(oper1.top()) >= prior(str[i])) && !(prior(oper1.top()) == 4 && prior(str[i]) == 4)) {
				while ((!oper1.empty() && prior(oper1.top()) >= prior(str[i]))) {
					//cout << oper1.top()<<endl;
					if (oper1.top() != '(') {
						output.push_back(oper1.top());
						oper1.pop();
					}
					else {
						oper1.pop();//括号不输出，直接弹出
					}
				}//低优先级遇到高优先级，应该先输出并弹出高优先级，且遇到左括号情形除外。
				oper1.push(str[i]);//最后将当前操作符比较的数直接加入栈中。
			}
		}
		else {
			cout << "WRONG EXPRESSION!";
			break;
		}
	}
	while (!oper1.empty()) {
		output.push_back(oper1.top());
		oper1.pop();
	}//操作数非空时，将最后的操作数放入output字符串中
	return output;
}
//形成后缀表达式的函数
int logic2(string output, map<string, int>& save) {
	int count = -1;
	string output2 = output;
	while (!fruit.empty()) {
		fruit.pop();
	}
	while (size(output) > 0) {
		if (size(output) == 1) {
			fruit.push(output);
		}
		if (!isoperator(output.substr(0, 1))) {
			temp.push(output.substr(0, 1));
			output.erase(0, 1);
		}
		else if (isoperator(output.substr(0, 1)) && output.substr(0, 1) != "!") {
			result.clear();
			result.push_back(save[temp.top()]);
			temp2.append(output.substr(0, 1) + temp.top());
			temp.pop();
			temp2.insert(0, temp.top());
			result.push_back(save[temp.top()]);
			temp.pop();
			temp.push(temp2);
			fruit.push(temp2);
			if (output.substr(0, 1) == "&") {
				save[fruit.top()] = result[0] && result[1];
				//cout<<" here:" <<fruit.top()<<" is " << save[fruit.top()]<<" ";
			}
			else if (output.substr(0, 1) == "|") {
				save[fruit.top()] = result[0] || result[1];
			}
			else if (output.substr(0, 1) == "-") {
				save[fruit.top()] = result[0] || (!result[1]);
			}
			else if (output.substr(0, 1) == "=") {
				save[fruit.top()] = result[0] == result[1];
			}
			temp2 = "";
			output.erase(0, 1);
		}
		else if (isoperator(output.substr(0, 1)) && output.substr(0, 1) == "!") {
			temp2.append(output.substr(0, 1) + temp.top());
			save[temp2] = !save[temp.top()];
			temp.pop();
			temp.push(temp2);
			fruit.push(temp2);
			temp2 = "";
			output.erase(0, 1);
		}
	}
	output = output2;//因为要循环，所以每次判断后都要初始化
	return save[fruit.top()];
}
int logic(string output, map<string, int> &save) {
	int count = -1;
	string output2=output;
	while (!fruit.empty()) {
		fruit.pop();
	}
	while (size(output) > 0) {
		if (size(output) == 1) {
			fruit.push(output);
		}
		if (!isoperator(output.substr(0, 1))) {
			temp.push(output.substr(0, 1));
			output.erase(0, 1);
		}
		else if (isoperator(output.substr(0, 1))&&output.substr(0,1)!="!") {
			result.clear();
			result.push_back(save[temp.top()]);
			temp2.append(output.substr(0,1)+temp.top());
			temp.pop();
			temp2.insert(0, temp.top());
			result.push_back(save[temp.top()]);
			temp.pop();
			temp.push(temp2);
			fruit.push(temp2);
			if (output.substr(0, 1) == "&") {
				save[fruit.top()] = result[0] && result[1];
				//cout<<" here:" <<fruit.top()<<" is " << save[fruit.top()]<<" ";
			}
			else if (output.substr(0, 1) == "|") {
				save[fruit.top()] = result[0] || result[1];
			}
			else if (output.substr(0, 1) == "-") {
				save[fruit.top()] = result[0] ||(!result[1]);
			}
			else if (output.substr(0, 1) == "=") {
				save[fruit.top()] = result[0] == result[1];
			}
			temp2 = "";
			output.erase(0, 1);
		}
		else if (isoperator(output.substr(0, 1)) && output.substr(0, 1) == "!") {
			temp2.append(output.substr(0, 1) + temp.top());
			save[temp2] = !save[temp.top()];
			temp.pop();
			temp.push(temp2);
			fruit.push(temp2);
			temp2 = "";
			output.erase(0, 1);
		}
	}
	output = output2;//因为要循环，所以每次判断后都要初始化
	//以下为绘图使用
	stack<string> fruittemp = fruit;
	fruittemp = fruit;
	int n = size(fruit);//不能使用可变化的量作为循环判断值。
	for (int l = 0;l < n;l++) {
		if(!isoperator(fruit.top())){ cout << " * "; }
		if (!fruit.empty()&&!isoperator(fruit.top())) {
			for (int k = 0;k < size(fruit.top())-1;k++) {
				cout<<" ";
			}
		cout << save[fruit.top()];//输出每个子命题的逻辑判断值并对齐
		//cout << " here: "<<fruit.top()<<" is " << save[fruit.top()];//输出每个子命题的逻辑判断值
		}
		fruit.pop();//弹出fruit中最顶层的操作符（源于最后一次压栈）
	}
	fruit = fruittemp;//遍历完fruit后恢复
	//以上为绘图使用
	return save[fruit.top()];
}

void maketable(map<string,int>& save) {
	cout << endl;
	for (int i = 0;i < n;i++) {
		cout << " * " << letters.substr(i,1);
	}
	stack<string> fruittemp = fruit;
	while (!fruit.empty()) {
		if (!isoperator(fruit.top())) {
			cout << " * " << fruit.top();
		}
		fruit.pop();
	}
	fruit = fruittemp;;//遍历完fruit后恢复
	for (int j = 0;j < pow(2, n);j++) {
		cout << endl;
		changenum(binum, n);//二进制数移位
		for (int k = n - 1, i = 0;k > -1;k--, i++) {
			save[letters.substr(k, 1)] = binum[i];//将哈希表的元素变成二进制数
		//	cout<<" "<< letters.substr(k, 1)<<"=" << binum[i]<<" "; 输出每一步的赋值情况
		}
		for (int i = 0;i < n;i++) {
			cout << " * " << save[letters.substr(i, 1)];//绘制每一层的子命题事件值
		}
		binum[0]++;//二进制数加一
		logic(output, save);//判断加绘图
	}
	cout << endl << endl;
}
int main() {
	intro();
	while (1) {
		cin >> input;
		if (proper(input)) {
			createmap(binum, input, save);//先创建映射
			changes(input, oper1, output, letters);
			createnum(binum, n);
			cout << endl;
			cout <<"All events: "<< letters << endl;
			cout<<"Nifix Expression: "<< input << endl;
			cout <<"Postfix Expressiion: "<< output << endl;
			logic2(output, save);//首次逻辑判断使得绘表时第一行可以出现子命题事件
			cout << " ";
			maketable(save);
			//resetmap(letters, save);
			//letters="";//清空letters
			//n = 0;//还原所有的值，每次循环都要换原值
			//output = "";
				//int n = 0, flag = 0;
				//map<string, int> save;//各个子表达式的真值
				//string input;  //存储中缀表达式
				//string output; //存储后缀表达式
				//string letters;//存储单个字母
				//stack<char> oper1;//存储操作数
				//vector<int> binum;//二进制数字向量
				//stack<string> fruit;//存储各个子命题事件
				//vector<int> result;//存储各命题事件结果值
				//stack<string> temp;//临时存储命题事件
				//string temp2; //存储计算的命题事件
				//string temp3; //临时存储temp2
				//stack<int> result2;
			n = 0, flag = 0;
			output="";
			letters="";
			save.clear();
			binum.clear();
			stack<string>().swap(fruit);
			stack<string>().swap(temp);

		}
		else {
			cout << "WRONG EXPRESSION!" << endl;
			cout << "Please reinput your expression:" << endl;
		}
		
	}
	return 0;
}