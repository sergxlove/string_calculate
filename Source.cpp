#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;
enum condition_attribute //��������� ��������
{
	atr_none,// ��� ���������
	atr_operator, //��������� ���������
	atr_value //��������� �����
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
bool check_correct(std::string& str)//�������� ����������� ��������� �����
{
	try
	{
		std::vector<int> symbol = { 32,40,41,42,43, 45,46, 47,48,49,50,51,52,53,54,55,56,57 };//���������� ��������
		int count = 0;// �������� �������
		for (size_t i = 0; i < str.size();)//�������� ������� �������� ������ �� ������������
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
bool check_scobs(std::string& str)//�������� �� ������������ ������
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
double math_operation(double value1, double value2, char opr)//���������� �������������� ��������
{
	try
	{
		if (opr == '+')//��������
		{
			return value1 + value2;
		}
		if (opr == '-')//���������
		{
			return value1 - value2;
		}
		if (opr == '*')//���������
		{
			return value1 * value2;
		}
		if (opr == '/')//�������
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
bool check_value(char symbol)//���������� �����
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
bool check_operator(char symbol)//����������� ���������
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
void get_attribute(const std::string& str, std::string& value_str, int& condition, size_t& pozition)//��������� ���������� ��������
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
		if (check_correct(expression))//�������� ����������� ��������� ��������
		{
			if (check_scobs(expression))//�������� ������������ ���������� ������
			{
				std::stack<double> arr_num;//���� ��� �����
				std::stack<char> arr_opr;//���� ��� ��������
				std::string value_str = "";//����������� ����� ���� ������
				std::string full_str = expression + ' ';//������ � �������������� ���������� + ������  � �����
				int condition = condition_attribute::atr_none;//��������� ��������
				size_t pozition = 0;//������� ��������� � ������
				double first_value = 0;//������ ����� ��� �������������� ��������
				double second_value = 0;//������ ����� ��� �������������� ��������
				char var_operator = ' ';//��������
				int streak_operator = 0;//���������� ������ ������ ����������
				bool negative_value = false;//����� �������������� �����
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
				while (true)//����������� ���� ���������� �������������� ��������
				{
					if (pozition >= full_str.size())//�������� �� ��������� ������ � ��������������� ����������
					{
						break;//��������� �����
					}
					value_str = "";//���������� ������� ��������
					condition = condition_attribute::atr_none;//���������� ������� ��������
					get_attribute(full_str, value_str, condition, pozition);//���������� ���������� ��������
					if (condition == condition_attribute::atr_operator)//���������� ��� �������� ���������
					{
						if (arr_opr.empty())//��� ������ ����� ��������
						{
							if (arr_num.empty()&&value_str[0] == '-')//��� ������ ����� � �������
							{
								negative_value = true;//��������� ������ �������������� �����
							}
							else
							{
								arr_opr.push(value_str[0]);//���������� ������� ��������� � ���� � �����������
								streak_operator++;//���������� ���������� ������ ������ ����������
							}
						}
						else // ��� ������� ��������� � ����� � ����������
						{
							if (get_priority(value_str[0]) == 3)// ���� �������� = "("
							{
								arr_opr.push(value_str[0]);//���������� �������� "(" � ����
							}
							else if (get_priority(value_str[0]) == 4)// ���� �������� = ")" 
							{
								while (true)//����������� ����, �� ������� �������� "("
								{
									if (get_priority(arr_opr.top()) == 3)//��� ������� �������� "("
									{
										arr_opr.pop();//�������� �������� "("
										break;//����� �� �����
									}
									second_value = arr_num.top();//���������� �������� ����� ����� 
									arr_num.pop();//�������� �������� ����� �����
									first_value = arr_num.top();//���������� �������� ����� �����
									arr_num.pop();//�������� �������� ����� �����
									var_operator = arr_opr.top();//���������� ������� �������� �����
									arr_opr.pop();//�������� ������� �������� �����
									arr_num.push(math_operation(first_value, second_value, var_operator));//���������� � ���� � ������� ���������� �������������� ��������
									if (get_priority(arr_opr.top()) == 3)//��� ������� �������� "("
									{
										arr_opr.pop();//�������� �������� "("
										break;//����� �� �����
									}
								}
							}
							else if (get_priority(value_str[0]) == get_priority(arr_opr.top()))//��� ������� �������� � ������������ �����������
							{
								if (arr_num.size() > 1 && arr_opr.size() > 0)//��� ����������� �������� ����������� �������������� ��������
								{
									second_value = arr_num.top();//���������� �������� ����� �����
									arr_num.pop();//�������� �������� ����� �����
									first_value = arr_num.top();//���������� �������� ����� �����
									arr_num.pop();//�������� �������� ����� �����
									var_operator = arr_opr.top();//���������� ������� �������� �����
									arr_opr.pop();//�������� ������� �������� �����
									arr_num.push(math_operation(first_value, second_value, var_operator));//���������� � ���� � ������� ���������� �������������� ��������
								}
								arr_opr.push(value_str[0]);//���������� ��������� � ���� � �����������
								streak_operator++;//���������� ���������� ������ ������ ����������
							}
							else if (get_priority(value_str[0]) == 2 && get_priority(arr_opr.top()) == 1)//��� ����� ������� ���������� ������� �������� ��� �������� � �����
							{
								arr_opr.push(value_str[0]);//���������� �������� � ����
								streak_operator++;//���������� ���������� ������ ������ ��������
							}
							else if (get_priority(value_str[0]) == 1 && get_priority(arr_opr.top()) == 2)//��� ����� ������ ���������� ������� �������� ��� �������� � �����
							{
								if (arr_num.size() > 1)//��� ����������� �������� �������������� ��������
								{
									replay:
									second_value = arr_num.top();//���������� �������� ����� �����
									arr_num.pop();//�������� �������� ����� �����
									first_value = arr_num.top();//���������� �������� ����� �����
									arr_num.pop();//�������� �������� ����� �����
									var_operator = arr_opr.top();//���������� ������� �������� �����
									arr_opr.pop();//�������� ������� �������� �����
									arr_num.push(math_operation(first_value, second_value, var_operator));//���������� � ���� ���������� �������������� ��������
								}
								if (arr_opr.size() != 0)
								{
									if (get_priority(value_str[0]) == get_priority(arr_opr.top()))
									{
										goto replay;
									}
									else
									{
										arr_opr.push(value_str[0]);//���������� ��������� � ���� � �����������
										streak_operator++;//���������� ���������� ������ ������ ����������
									}
								}
								else
								{
									arr_opr.push(value_str[0]);//���������� �������� � ����
									streak_operator++;//���������� ���������� ������ ������ ��������
								}
							}
							else if (get_priority(arr_opr.top()) == 3 && (get_priority(value_str[0]) == 1 || get_priority(value_str[0]) == 2))// ���� ���������� �������� ����� ������� "("
							{
								arr_opr.push(value_str[0]);//���������� �������� � ����
								streak_operator++;//���������� ���������� ������ ������ ����������
							}
							if (streak_operator > 1)//��� ���� ������ ������ ����������
							{
								negative_value = true;//��������� ������ �������������� ����� 
								streak_operator = 0;//��������� �������� ������ ������ ����������
								arr_opr.pop();//�������� ������� ��������� �����
								continue;//������� �����
							}
						}
					}
					else if (condition == condition_attribute::atr_value)//���������� ��� �������� �����
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
						if (negative_value)//������� ����� �������������� �����
						{
							arr_num.push(std::stod(value_str) * (-1.0));//���������� �������������� ����� � ����
							pozition--;//���������� �������
							streak_operator = 0;//��������� ���������� ������ ������ ��������
							negative_value = false;//���������� ������ �������������� �����
						}
						else//�������� ����� �������������� �����
						{
							arr_num.push(std::stod(value_str));//���������� �������� ����� � ����
							pozition--;//���������� �������
							streak_operator = 0;//��������� ���������� ������ ������ ��������
						}
					}
				}
				while (!arr_opr.empty())//���� ����������� ����� � ����������
				{
					second_value = arr_num.top();//���������� �������� ����� �����
					arr_num.pop();//�������� �������� ����� �����
					first_value = arr_num.top();//���������� �������� ����� �����
					arr_num.pop();//�������� �������� ����� �����
					var_operator = arr_opr.top();//���������� �������� ��������� �����
					arr_opr.pop();//���������� �������� ����� �����
					arr_num.push(math_operation(first_value, second_value, var_operator));//���������� � ���� ���������� �������������� ��������
				}
				return arr_num.top();//������� �������� �������� ����� (����������)
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