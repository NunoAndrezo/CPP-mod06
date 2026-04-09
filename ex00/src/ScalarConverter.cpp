/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:21:45 by nuno              #+#    #+#             */
/*   Updated: 2026/04/09 21:26:11 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ScalarConverter.hpp"

static int handlePseudo(std::string s);
static int handleDouble(std::string s);
static int handleFloat(std::string s);
static int handleInt(std::string s);
static int handleChar(std::string s);

//ScalarConverter::ScalarConveter() {} // the default constructor is private, so it cannot be called from outside the class. This is a common technique to prevent instantiation of a class that is meant to be used only for its static members.	

ScalarConverter::~ScalarConverter()
{
	std::cout << "[ScalarConverter] -> Default Destructor called!" << std::endl;
}

void ScalarConverter::convert(std::string string)
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
	std::cerr << "Invalid input\n";
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
			return (0);
	}
	return (0);
}

static int handleFloat(std::string s)
{
	size_t	i = 0;
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
	std::cout << "number: " << number << std::endl; // this is just for debugging, I will remove it later.
	std::cout << "decimal_num: " << decimal_num << std::endl; // this is just for debugging, I will remove it later.
	number /= decimal_num; // here we divide the number by the decimal_num to get the final float value. so in our example, number is 123445, and decimal_num is 100, so number / decimal_num is 1234.45f, which is the correct float representation of the input string "1234.45f".
	number *= sign;
	if (number > 340282346638528859811704183484516925440.0000000000000000  || number < -340282346638528859811704183484516925440.0000000000000000)
		return (std::cerr << "Error: float overflow\n" << std::endl, 0);
	// char
	if ((number  < 32 || number > 126) || number != static_cast<int>(number)) // how to make sure 45.9 doesn't pass the char case? Answer: You can check if the number is an integer and if it falls within the range of displayable ASCII characters. For example, you can add a condition to check if the number is a whole number (i.e., has no decimal part) and if it is between 32 and 126 inclusive. Here's how you can modify the condition:
		std::cout << "char: Non displayable\n";
	else
		std::cout << "char: " << static_cast<char>(number) << std::endl;
	// int
	if (static_cast<long>(number) > 2147483647 || static_cast<long>(number) < -2147483648 || number != static_cast<int>(number))
		std::cout << "int: impossible\n";
	else
		std::cout << "int: " << static_cast<int>(number) << std::endl;
	// float and double
	std::cout << "float: " << (number) << "f" << std::endl;
	std::cout << "double: " << (number) << std::endl;
	return 1;
}

static int handleDouble(std::string s)
{
	// maybe I will use stringstream here since I didn't use for Float
	// or I could just copy the code from handleFloat and just remove the 'f' at the end and change the type to double.
	std::stringstream ss(s);
	double number;
	ss >> number; // what this does is: it tries to extract a double value from the stringstream ss and store it in the variable number. if the extraction is successful, it will return true, and if it fails (for example, if the string does not contain a valid double), it will return false. so if ss.fail() is true, it means that the extraction failed, and we should return 0 to indicate that this function cannot handle the input string as a double. also, we check if ss.eof() is true to ensure that we have reached the end of the string after extracting the double value. if there are extra characters after the number, it would also be considered an invalid input for a double.
	// how does >> operator work with stringstream? Answer: The >> operator is overloaded for stringstream to extract formatted data from the stream. When you use ss >> number, it tries to read characters from the stringstream ss and convert them into a double value, which is then stored in the variable number. The operator will skip any leading whitespace characters and then read characters until it encounters a character that cannot be part of a valid double (such as a letter or a symbol). If the extraction is successful, it will set the failbit to false, and if it fails, it will set the failbit to true. Additionally, if there are extra characters after the number that are not part of a valid double, it will not consume those characters, and ss.eof() will return false, indicating that we have not reached the end of the string.
	if (ss.fail() || !ss.eof())
		return 0;
	// example: number is 43.89
	// round 1: char: 43.89 is not a displayable character, so it will print "char: Non displayable"
	// round 2: int: 43.89 is not an integer, so it will print "int: impossible"
	// round 3: float: 43.89f
	// round 4: double: 43.89
	
	if (number > 1.7e+308 || number < -1.7)
		return (std::cerr << "Error: double overflow\n" << std::endl, 0);
	return 0;
	// char
	if (number < 32 || number > 126)
		std::cout << "char: Non displayable\n";
	else
		std::cout << "char: " << static_cast<char>(number) << std::endl;
	// int
	if (number > std::numeric_limits<int>::max() || number < std::numeric_limits<int>::min())
		std::cout << "int: impossible\n";
	else
		std::cout << "int: " << static_cast<int>(number) << std::endl;
	// float and double
	std::cout << "float: " << static_cast<float>(number) << "f" << std::endl;
	std::cout << "double: " << (number) << std::endl;
	return 1;
}

static int handleInt(std::string s)
{
	std::stringstream ss(s);
	int number;
	ss >> number;
	if (ss.fail() || !ss.eof())
		return 0;
	// char
	if (number < 32 || number > 126)
		std::cout << "char: Non displayable\n";
	else
		std::cout << "char: " << static_cast<char>(number) << std::endl;
	// int
	std::cout << "int: " << number << std::endl;
	// float and double
	std::cout << "float: " << static_cast<float>(number) << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(number) << std::endl; // do I need to add the .00 here? Answer: No, I don't need to add .00 here because when I cast an int to a double, it will automatically be represented as a floating-point number. For example, if number is 42, then static_cast<double>(number) will yield 42.0, which is the correct double representation of the integer 42. The output will show "double: 42" but it is understood that it is a double value. If you want to explicitly show the decimal part, you could use std::fixed and std::setprecision manipulators from the <iomanip> header to format the output, like this: std::cout << std::fixed << std::setprecision(2) << static_cast<double>(number) << std::endl; This would display the double value with two decimal places, showing "double: 42.00". However, for this project, it's not necessary to format the output in that way.
	return 1;
}
