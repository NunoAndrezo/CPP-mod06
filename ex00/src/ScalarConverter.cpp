/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:21:45 by nuno              #+#    #+#             */
/*   Updated: 2026/04/07 14:38:54 by nuno             ###   ########.fr       */
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

	// maybe I will use stringstream to handle the conversion, is that allowed?
	if (s.length() <= 2 || (s[s.length() - 1] != 'f' && s[s.length() - 1] != 'F') || s.find('.') == std::string::npos)
		return 0;
	while(i < s.length() - 1)
	{
		if (s[0] == '-' || s[0] == '+')
			sign = (s[0] == '-') ? -1 : 1, i++;
		else if (isdigit(s[i]))
			number = number * 10 + (s[i] - '0'), i++;
		else if (s[i] == '.' && dot_flag == false)
		{
			dot_flag = true; // example- real number: 120.45f. number is at 120, dot_flag is true, and i is at 120.45f[3] which is the dot. so we need to move the number to 0.12045 by dividing it by 10 for each digit after the dot.
			size_t j = i + 1;
			while (j < s.length() - 1 && isdigit(s[j]))
			{
				number = number * 10 + (s[j] - '0'); //shouldnt I divide here? 
				j++;
			}
			i++;
		}
		else
			return 0;
	}
	if (number > std::numeric_limits<float>::max() || number < std::numeric_limits<float>::lowest())
		return 0;
	
	std::cout << "char: " << static_cast<char>(number * sign) << std::endl;
	std::cout << "int: " << static_cast<int>(number * sign) << std::endl;
	std::cout << "float: " << (number * sign) << "f" << std::endl;
	std::cout << "double: " << (number * sign) << std::endl;
	return 1;

}