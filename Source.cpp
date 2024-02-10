#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;
enum condition_attribute //состояние атрибута
{
	atr_none,// без состояния
	atr_operator, //состояние оператора
	atr_value //состояние числа
};
std::string update_str(std::string str)
{
	try
	{
		std::string result;
		result = str + ' ';
		if (str[0] == '-')
		{
			result = '0' + str + ' ';
		}
		return result;
	}
	catch (...)
	{
		return "error";
	}
}
bool check_correct(std::string& str)//проверка коректности введенных чисел
{
	try
	{
		std::vector<int> symbol = { 32,40,41,42,43, 45,46, 47,48,49,50,51,52,53,54,55,56,57 };//допустимые значения
		int count = 0;// итератор вектора
		for (size_t i = 0; i < str.size();)//проверка каждого элемента строки на корректность
		{
			if ((int)str[i] == symbol[count])
			{
				++i;
				count = 0;
			}
			else
			{
				++count;
			}
			if (count == symbol.size())
			{
				return false;
			}
		}
		return true;
	}
	catch (...)
	{
		return 0;
	}
}
bool check_scobs(std::string& str)//проверка на корректность скобок
{
	try
	{
		int count_left = 0;
		int count_right = 0;
		for (size_t i = 0;i < str.size();i++)
		{
			if ((int)str[i] == 40)
			{
				++count_left;
			}
			if ((int)str[i] == 41)
			{
				++count_right;
			}
		}
		if (count_left == count_right)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (...)
	{
		return 0;
	}
}
double math_operation(double value1, double value2, char opr)//выполнение математической операции
{
	try
	{
		if (opr == '+')//сложение
		{
			return value1 + value2;
		}
		if (opr == '-')//вычитание
		{
			return value1 - value2;
		}
		if (opr == '*')//умножение
		{
			return value1 * value2;
		}
		if (opr == '/')//деление
		{
			return value1 / value2;
		}
		return 0.0;
	}
	catch (...)
	{
		return 0;
	}
}
bool check_value(char symbol)//пределение числа
{
	try
	{
		if ((int)symbol >= 48 && (int)symbol <= 57 || (int)symbol == 46)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (...)
	{
		return 0;
	}
}
bool check_operator(char symbol)//определение оператора
{
	try
	{
		std::vector<int> arr_symbol = { 40, 41, 42, 43, 45, 47 };
		for (size_t i = 0;i < arr_symbol.size();i++)
		{
			if (arr_symbol[i] == (int)symbol)
			{
				return true;
			}
		}
		return false;
	}
	catch (...)
	{
		return 0;
	}
}
void get_attribute(const std::string& str, std::string& value_str, int& condition, size_t& pozition)//получение следующего атрибута
{
	try
	{
		std::string value_s = "";
		value_str = "";
		bool write_value = false;
		bool exit = false;
		for (;pozition < str.size();++pozition)
		{
			if (exit)
			{
				break;
			}
			if (write_value == false)
			{
				if (check_operator(str[pozition]))
				{
					value_s = str[pozition];
					value_str = value_s;
					condition = condition_attribute::atr_operator;
					exit = true;
					continue;
				}
			}
			if (check_value(str[pozition]))
			{
				value_s += str[pozition];
				write_value = true;
			}
			else
			{
				write_value = false;
			}
			if (!write_value && !value_s.empty())
			{
				value_str = value_s;
				condition = condition_attribute::atr_value;
				exit = true;
				continue;
			}
		}
	}
	catch (...)
	{
		return;
	}
}
int get_priority(char opr)
{
	// +, - : 1
	// *, / : 2
	// ( : 3
	// ) : 4
	if ((int)opr == 43 || (int)opr == 45)
	{
		return 1;
	}
	if ((int)opr == 42 || (int)opr == 47)
	{
		return 2;
	}
	if ((int)opr == 40)
	{
		return 3;
	}
	if ((int)opr == 41)
	{
		return 4;
	}
	return 0;
}
int get_quantity_value(const std::string& str)
{
	try
	{
		std::string value_s = "";
		bool write_value = false;
		int result = 0;
		for (size_t i = 0;i < str.size();i++)
		{
			if (write_value == false)
			{
				if (check_operator(str[i]))
				{
					continue;
				}
			}
			if (check_value(str[i]))
			{
				value_s += str[i];
				write_value = true;
			}
			else
			{
				write_value = false;
			}
			if (!write_value && !value_s.empty())
			{
				value_s = "";
				result++;
				continue;
			}
		}
		return result;
	}
	catch (...)
	{
		return 0;
	}
}
int get_quantity_operator(const std::string& str)
{
	try
	{
		int result = 0;
		for (size_t i = 0;i < str.size();i++)
		{
			if (str[i] == '-')
			{
				++result;
			}
		}
		return result;
	}
	catch (...)
	{
		return 0;
	}
}
double calc(std::string expression)
{
	try
	{
		if (check_correct(expression))//проверка коректности введенных символов
		{
			if (check_scobs(expression))//проверка корректности введеннных скобок
			{
				std::stack<double> arr_num;//стек для чисел
				std::stack<char> arr_opr;//стек для операций
				std::string value_str = "";//считываемое число типа стринг
				std::string full_str = expression + ' ';//строка с математическим выражением + пробел  в конце
				int condition = condition_attribute::atr_none;//состояние атрибута
				size_t pozition = 0;//позиция итератора в строке
				double first_value = 0;//первое число для математической операции
				double second_value = 0;//второе число для математической операции
				char var_operator = ' ';//опреация
				int streak_operator = 0;//количество подряд идущих опреаторов
				bool negative_value = false;//режим отрицательного числа
				bool unic_value = false;
				bool unic_negative_value = false;
				if (get_quantity_value(full_str) == 1)
				{
					if (get_quantity_operator(full_str) > 0)
					{
						if (get_quantity_operator(full_str) % 2 == 0)
						{
							unic_value = true;
						}
						else
						{
							unic_value = true;
							unic_negative_value = true;
						}
					}
				}
				while (true)//бесконечный цикл выполнения математических операций
				{
					if (pozition >= full_str.size())//проверка на окончание строки с математичекским выражением
					{
						break;//остановка цикла
					}
					value_str = "";//присвоение пустого значения
					condition = condition_attribute::atr_none;//присвоение пустого атрибута
					get_attribute(full_str, value_str, condition, pozition);//считывание следующего атрибута
					if (condition == condition_attribute::atr_operator)//выполнение при атрибуте оператора
					{
						if (arr_opr.empty())//при пустом стеке опреаций
						{
							if (arr_num.empty()&&value_str[0] == '-')//при пустом стеке с числами
							{
								negative_value = true;//активация режима отрицательного числа
							}
							else
							{
								arr_opr.push(value_str[0]);//добавление первого оператора с стек с операторами
								streak_operator++;//увеличение количества подряд идущих операторов
							}
						}
						else // при наличии элементов с стеке с операциями
						{
							if (get_priority(value_str[0]) == 3)// если опреация = "("
							{
								arr_opr.push(value_str[0]);//добавление опреации "(" в стек
							}
							else if (get_priority(value_str[0]) == 4)// если операция = ")" 
							{
								while (true)//бесконечный цикл, до встречи операции "("
								{
									if (get_priority(arr_opr.top()) == 3)//при встрече операции "("
									{
										arr_opr.pop();//удаление операции "("
										break;//выход из цикла
									}
									second_value = arr_num.top();//считывание верхнего числа стека 
									arr_num.pop();//удаление верхнего числа стека
									first_value = arr_num.top();//считывание верхнего числа стека
									arr_num.pop();//удаление верхнего числа стека
									var_operator = arr_opr.top();//считывание верхней операции стека
									arr_opr.pop();//удаление верхней операции стека
									arr_num.push(math_operation(first_value, second_value, var_operator));//добавление в стек с числами результата математической опреации
									if (get_priority(arr_opr.top()) == 3)//при встрече операции "("
									{
										arr_opr.pop();//удаление опреации "("
										break;//выход из цикла
									}
								}
							}
							else if (get_priority(value_str[0]) == get_priority(arr_opr.top()))//при встрече операции с равнозначным приоритетом
							{
								if (arr_num.size() > 1 && arr_opr.size() > 0)//при возможности провести полноценную математическую операцию
								{
									second_value = arr_num.top();//считывание верхнего числа стека
									arr_num.pop();//удаление верхнего числа стека
									first_value = arr_num.top();//считывание верхнего числа стека
									arr_num.pop();//удаление верхнего числа стека
									var_operator = arr_opr.top();//считывание верхней операции стека
									arr_opr.pop();//удаление верхней операции стека
									arr_num.push(math_operation(first_value, second_value, var_operator));//добавление в стек с числами результата математической операции
								}
								arr_opr.push(value_str[0]);//добавление опреатора в стек с опреаторами
								streak_operator++;//увеличение количества подряд идущих опреаторов
							}
							else if (get_priority(value_str[0]) == 2 && get_priority(arr_opr.top()) == 1)//при более высоком приоритете текущей операции чем операции в стеке
							{
								arr_opr.push(value_str[0]);//добавление операции в стек
								streak_operator++;//увеличение количество подряд идущих операций
							}
							else if (get_priority(value_str[0]) == 1 && get_priority(arr_opr.top()) == 2)//при более низком приоритете текучей опреации чем операции в стеке
							{
								if (arr_num.size() > 1)//при возможности провести математическую операцию
								{
									replay:
									second_value = arr_num.top();//считывание верхнего числа стека
									arr_num.pop();//удаление верхнего числа стека
									first_value = arr_num.top();//считывание верхнего числа стека
									arr_num.pop();//удаление верхнего числа стека
									var_operator = arr_opr.top();//считывание верхней опреации стека
									arr_opr.pop();//удаление верхней операции стека
									arr_num.push(math_operation(first_value, second_value, var_operator));//добавление в стек результата математической операции
								}
								if (arr_opr.size() != 0)
								{
									if (get_priority(value_str[0]) == get_priority(arr_opr.top()))
									{
										goto replay;
									}
									else
									{
										arr_opr.push(value_str[0]);//добавление опреатора в стек с опреаторами
										streak_operator++;//увеличение количества подряд идущих опреаторов
									}
								}
								else
								{
									arr_opr.push(value_str[0]);//добавление операции в стек
									streak_operator++;//увеличение количества подряд идущих символов
								}
							}
							else if (get_priority(arr_opr.top()) == 3 && (get_priority(value_str[0]) == 1 || get_priority(value_str[0]) == 2))// прри добавлении операции после символа "("
							{
								arr_opr.push(value_str[0]);//добавление операции в стек
								streak_operator++;//увеличение количества подряд идущих операторов
							}
							if (streak_operator > 1)//при двух подряд идущих операторах
							{
								negative_value = true;//включение режима отрицательного числа 
								streak_operator = 0;//обнуление счетчика подряд идущих операторов
								arr_opr.pop();//удаление вехнего оператора стека
								continue;//пропуск цикла
							}
						}
					}
					else if (condition == condition_attribute::atr_value)//выполнение при атрибуте числа
					{
						if (unic_value)
						{
							if (unic_negative_value)
							{
								return std::stod(value_str) * (-1.0);
							}
							else
							{
								return std::stod(value_str);
							}
						}
						if (negative_value)//включен режим отрицательного числа
						{
							arr_num.push(std::stod(value_str) * (-1.0));//добавление отрицательного числа в стек
							pozition--;//уменьшение позиции
							streak_operator = 0;//обнуление количества подряд идущих символов
							negative_value = false;//выключение режима отрицательного числа
						}
						else//выключен режим отрицательного числа
						{
							arr_num.push(std::stod(value_str));//добавление обычного числа в стек
							pozition--;//уменьшение позиции
							streak_operator = 0;//обнуление количества подряд идущих символов
						}
					}
				}
				while (!arr_opr.empty())//цикл опустошения стека с операциями
				{
					second_value = arr_num.top();//считывание верхнего числа стека
					arr_num.pop();//удаление верхнего числа стека
					first_value = arr_num.top();//считывание верхнего числа стека
					arr_num.pop();//удаление верхнего числа стека
					var_operator = arr_opr.top();//считывание верхнего оператора стека
					arr_opr.pop();//считывание верхнего числа стека
					arr_num.push(math_operation(first_value, second_value, var_operator));//добавление в стек результата математической операции
				}
				return arr_num.top();//возврат верхнего элемента стека (результата)
			}
			else
			{
				return 0.0;
			}
		}
		else
		{
			return 0.0;
		}
		return 0;
	}
	catch (...)
	{
		return 0;
	}
}
int main()
{
	cout << calc("1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1") << endl;
	return 0;
}