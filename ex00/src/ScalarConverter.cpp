/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:21:45 by nuno              #+#    #+#             */
/*   Updated: 2026/04/07 22:47:02 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ScalarConverter.hpp"

static int handlePseudo(std::string s);
static int handleDouble(std::string s);
static int handleFloat(std::string s);
static int handleInt(std::string s);
static int handleChar(std::string s);

// ScalarConverter::ScalarConveter(){} // its not showing because its private? Answer: Yes, the default constructor is private, so it cannot be called from outside the class. This is a common technique to prevent instantiation of a class that is meant to be used only for its static members.	

ScalarConverter::~ScalarConverter()
{
	std::cout << "[ScalarConverter] -> Default Destructor called!" << std::endl;
}

static void convert(std::string string)
{
	if (handlePseudo(string) == 1)
		return ;
	else if (handleChar(string))
		return ;
	else if (handleFloat(string))
		return ;
	else if (handleDouble(string))
		return ;
	else if (handleInt(string))
		return ;
	else
		std::cout << "Invalid input\n";
}

static int handlePseudo(std::string s)
{
	std::string pseudo[] = {"-inf", "+inf", "nan", "-inff", "+inff", "nanf"};
	for (int i = 0; i < 6; i++)
	{
		if (s == pseudo[i])
		{
			std::cout << "char: impossible" << std::endl; 
			std::cout << "int: impossible" << std::endl;
			if (i < 3)
				std::cout << "float: " << pseudo[i] << "f\n";
			else
				std::cout << "float: " << pseudo[i] << std::endl;
			if (i < 3)
				std::cout << "double: " << pseudo[i] << "\n";
			else
				std::cout << "double: " << pseudo[i].substr(0, pseudo[i].length() - 1) << "\n";
			return (1);
		}
	}
	return (0);
}

static int handleChar(std::string s)
{
	if (s.length() == 1 && isdigit(s[0]) == 0)
	{
		if (static_cast<int>(s[0]) >= 32 && static_cast<int>(s[0]) <= 126)
		{
			std::cout << "char: '" << s[0] << "'\n";
			std::cout << "int: " << static_cast<int>(s[0]) << std::endl;
			std::cout << "float: " << static_cast<float>(s[0]) << ".0f\n";
			std::cout << "double: " << static_cast<double>(s[0]) << ".0\n";
			return (1);
		}
		else
			return (std::cout << "Invalid input\n", 1);
	}
	return (0);
}

static int handleFloat(std::string s)
{
	int		i = 0;
	bool	dot_flag = false;
	int		sign = 1;
	float	number = 0.0f;
	float	decimal_num = 1.0f;

	// maybe I will use stringstream to handle the conversion, is that allowed?
	//s.length() <= 2 because we need at least one digit, a dot, and an 'f' at the end. so the minimum length is 3 for a valid float like "0.f".
	if (s.length() <= 2 || (s[s.length() - 1] != 'f' && s[s.length() - 1] != 'F') || s.find('.') == std::string::npos)
		return 0;
	while(i < s.length() - 1)
	{
		// example- real number: 1234.45f.
		// first round - s[0] is '1', so number = 0 * 10 + (1 - '0') = 1, i = 1
		// second round - s[1] is '2', so number = 1 * 10 + (2 - '0') = 12, i = 2
		// third round - s[2] is '3', so number = 12 * 10 + (3 - '0') = 123, i = 3
		// fourth round - s[3] is '4', so number = 123 * 10 + (4 - '0') = 1234, i = 4
		// fifth round - s[4] is '.', so we set dot_flag to true, and we start processing the decimal part! decimal_num
		// sixth round - s[5] is '4', so decimal_num = 1 * 10 = 10, number = 1234 * 10 + (4 - '0') = 12344, i = 6
		// seventh round - s[6] is '5', so decimal_num = 10 * 10 = 100, number = 12344 * 10 + (5 - '0') = 123445, i = 7
		// eighth round - s[7] is 'f', so we exit the loop and we will divide number by decimal_num to get the final float value, which is 123445 / 100 = 1234.45f
		if (s[0] == '-' || s[0] == '+')
			sign = (s[0] == '-') ? -1 : 1, i++;
		else if (isdigit(s[i]))
			number = number * 10 + (s[i] - '0'), i++;
		else if (s[i] == '.' && dot_flag == false)
		{
			dot_flag = true;
			for (size_t j = i + 1; j < s.length() - 1; j++) // so here in the fifth round: j starts at 5, and it will check if s[5] is a digit, which is '4', so it will multiply decimal_num by 10, making it 10. then j will be 6, and it will check if s[6] is a digit, which is '5', so it will multiply decimal_num by 10 again, making it 100. then j will be 7, and it will check if s[7] is a digit, which is 'f', so it will return 0 because it's not a digit.
				if (isdigit(s[j]))
					decimal_num *= 10; // so decimal_num will be 100 after the loop.
				else
					return 0;
			i++;
		}
		else
			return 0;
	}
	if (number > std::numeric_limits<float>::max() || number < std::numeric_limits<float>::lowest())
		return (std::cerr << "Error: float overflow\n" << std::endl, 0);
	number *= sign;
	number /= decimal_num; // here we divide the number by the decimal_num to get the final float value. so in our example, number is 123445, and decimal_num is 100, so number / decimal_num is 1234.45f, which is the correct float representation of the input string "1234.45f".
	if (number > std::numeric_limits<float>::max() || number < std::numeric_limits<float>::lowest())
		return (std::cerr << "Error: float overflow\n" << std::endl, 0);

	if (number  < 32 || number > 126)
		std::cout << "char: Non displayable\n";
	else
		std::cout << "char: " << static_cast<char>(number) << std::endl;
	if (number > std::numeric_limits<int>::max() || number < std::numeric_limits<int>::min())
		std::cout << "int: impossible\n";
	else
		std::cout << "int: " << static_cast<int>(number) << std::endl;
	std::cout << "float: " << (number) << "f" << std::endl;
	std::cout << "double: " << (number) << std::endl;
	return 1;
}

static int handleDouble(std::string s)
{
	// maybe I will use stringstream here since I didn't use for Float
	// or I could just copy the code from handleFloat and just remove the 'f' at the end and change the type to double.
	std::stringstream ss(s);
	
}