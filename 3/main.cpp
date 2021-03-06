#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
long long fibonacci(int number) {
	using namespace std;
	long long first{ 0 }, second{ 1 };
	for (int i{ 2 }; i <= number; ++i) {
		(i % 2 == 0) ? first += second : second += first;
	}
	return (second > first) ? second: first;
}

long long fibonacciRec(int number) {
	if (number < 2) {
		return 1;
	}
	long long result{ 0 };
	result = fibonacciRec(number - 1) + fibonacciRec(number - 2);
	return  result;
}

//Перевод в другую систему счисления
std::string translate(std::string num, int b, int c) { //b - нач   c - кон
	using namespace std;
	bool noError{ true }; //Корректность введенного числа
	for (int i{ 0 }; i < num.size(); ++i) {
		if (num[i] - '0' >= b || //Цифра должна быть меньше основания
				(num[i] < 46 || num[i] == 47 || (num[i] > 57 && num[i] < 65) || num[i] > 90)) {
			if (num[i] > 96 && num[i] < 123) { 
				num[i] -= 32; //uppercase
					continue;
			}
			noError = false;
			break;
		}
	}
	if (c > 1 && b > 1 && noError) {
		string inputIntegerPart{ "" }; //Целая часть
		string inputRealPartString{"0."}; //Дробная часть
		int counter{ 0 };

		while (counter < num.size() && num[counter] != '.') { //Получение целой части
			inputIntegerPart += num[counter];
			++counter;
		}
		++counter;
		while (counter < num.size()) { //Получение дробной части
			inputRealPartString += num[counter];
			++counter;
		}

		long long decIntegerPart{ 0 }; //Число в десятичной форме
		double decRealPart{ 0 }; //Дробная часть
		//В 10-чную---------------------
		if (b != 10) {
			//Целая часть
			if (inputIntegerPart.size() > 0) {
				for (int i{ 0 }; i < inputIntegerPart.size(); ++i) {
					decIntegerPart *= b;
					(inputIntegerPart[i] <= '9') ?
						decIntegerPart += (inputIntegerPart[i] - '0') :
						decIntegerPart += (inputIntegerPart[i] - 55);
					//55 - разница между кодом буквы и её значением
				}
			}
			//Дробная часть
			for (int i{ (int)inputRealPartString.size() - 1 }; i > 1; --i) {
				decRealPart = (inputRealPartString[i] <= '9') ?
					double(decRealPart + inputRealPartString[i] - '0') / b:
					decRealPart = double(decRealPart + inputRealPartString[i] - 55) / b;
			}
		}
		else {
			decIntegerPart = stoll(inputIntegerPart); //Число в десятичной форме
			decRealPart = stod(inputRealPartString); //Дробная часть
		}

		//Из 10-чной---------------------
		//Целая часть
		string integerPart{ "" };
		vector<char> finNum; //Финальное число как массив символов
		integerPart = to_string(decIntegerPart);
		int numeral{ 0 }; //цифра итогового цисла
		for (int i{ 0 }; stoll(integerPart) > 0; ++i) {
			numeral = stoll(integerPart) % c;
			(numeral < 10) ? finNum.push_back((numeral) + '0') :
				finNum.push_back((numeral) + 55); //Буквы
			integerPart = to_string(stoll(integerPart) / c);
		}
		(decIntegerPart == 0) ? finNum.push_back('0') :
				reverse(finNum.begin(), finNum.end()); //Переворачиваем массив
		string str(finNum.begin(), finNum.end()); //Vector to String
		string strReal{ "" };
		//Дробная часть

		//Округлили
		bool isRounded{ false };
		if (decRealPart > 0) {
			isRounded = true;
			for (int i{ 0 }; i < 15; ++i) { //Если делится бесконечно - округлять до 15 знаков
				decRealPart *= c;
				numeral = (int)trunc(decRealPart);
				(numeral < 10) ?
					strReal += to_string(numeral) :
					strReal += (char)numeral + 55; //Буквы
				decRealPart = (decRealPart - trunc(decRealPart)); //Отделение дробной части от числа
				if (decRealPart == 0.0) {
					isRounded = false;
					break;
				}
			}
		}
		for (int i{ (int)strReal.size() - 1 }; i >= 0; --i) { //Удаление лишних нулей
			if (strReal[i] == '0') {
				strReal.erase(i, '0');
			}
			else { break; }
		}
		if (strReal != "") { //Если есть дробная часть, отделяем точкой
			str += '.';
		}
		//Если округлили, то стави знак тильды
		isRounded ? str = '~' + str + strReal : str += strReal;
		return str;
	}
	return "Error";
}
void main1() {
	std::cout << "Enter Number: ";
	int number{ 0 };
	std::cin >> number;
	std::cin.get();
	std::cout << fibonacci(number);
}

void main2() {
	std::cout << "Enter Number: ";
	int number{ 0 };
	std::cin >> number;
	std::cin.get();
	std::cout << fibonacciRec(number);
}

void main3() {
	std::cout << "Enter Number: ";
	std::string number{ "" };
	std::getline(std::cin, number);
	std::cout << "Enter intial Numeral System ( 1 < n < 37 ): ";
	int initial{ 0 };
	std::cin >> initial;
	std::cin.get();
	std::cout << "Enter final Numeral System ( 1 < n < 37 ): ";
	int final{ 0 };
	std::cin >> final;
	std::cin.get();
	std::cout << translate(number, initial, final);
}

//https://numsys.ru/
int main() {
	using namespace std;
	cout << "Enter Task:\n" <<
		"1) Fibbonacci (circle)\n" <<
		"2) Fibbonacci (recursion)\n" <<
		"3) Numeral System Converter (error after 15 decimal places)\n";
	int taskNum{ 0 };
	cin >> taskNum;
	cin.get();
	switch (taskNum) {
	case 1: {main1(); break; }
	case 2: {main2(); break; }
	case 3: {main3(); break; }
	case 0: { //Быстрый тест конвертера
		int number = 11;
		//cout << fibonacci(number) << endl;
		//cout << fibonacciRec(number - 1);
		cout << "0.0000000000000001\t8 -> 2\t= " << translate("0.0000000000000001", 8, 2) << endl;
		cout << "0\t8 -> 10\t\t= " << translate("0", 8, 10) << endl; 
		cout << "88888888.8888\t36 -> 2\t= " << translate("88888888.8888", 36, 2) << endl;
		cout << "35.817\t9 -> 10\t\t= " << translate("35.817", 9, 10) << endl;
		cout << "68.5z\t36 -> 6\t\t= " << translate("68.5z", 36, 6) << endl;
		cout << "350.ff\t16 -> 32\t= " << translate("350.ff", 16, 32) << endl;
		cout << "80\t10 -> 8\t\t= " << translate("80", 10, 8) << endl;
		cout << "-80\t10 -> 2\t\t= " << translate("-80", 10, 2) << endl;
		cout << "80\t10 -> 2\t\t= " << translate("80", 10, 2) << endl;
		cout << "80\t10 -> 1\t\t= " << translate("80", 10, 1) << endl;
		cout << "80\t10 -> 10\t= " << translate("80", 10, 10) << endl;
		cout << "85\t6 -> 8\t\t= " << translate("85", 6, 8) << endl;
		cout << "35\t6 -> 8\t\t= " << translate("35", 6, 8) << endl;
		cout << "32.259\t10 -> 8\t\t= " << translate("35.259", 10, 8) << endl;
		cout << "35.200000087\t10 -> 8\t= " << translate("35.200000087", 10, 8) << endl;
		cout << "35.29\t10 -> 5\t\t= " << translate("35.29", 10, 5) << endl;
		cout << "35.29\t6 -> 10\t\t= " << translate("35.29", 6, 10) << endl;
		cout << "35D\t16 -> 10\t= " << translate("35D", 16, 10) << endl;
		cout << "35D.F\t16 -> 8\t\t= " << translate("35D.F", 16, 8) << endl;
		cout << "350\t8 -> 16\t\t= " << translate("350", 8, 16) << endl;
		cout << "350FF\t16 -> 32\t= " << translate("350FF", 16, 32) << endl;
		cout << "35.246\t7 -> 10\t\t= " << translate("35.246", 7, 10) << endl;
		cout << "45.5\t6 -> 4\t\t= " << translate("45.5", 6, 4) << endl;
		break;
	}
	default: {break; }
	}
	return 0;
}
