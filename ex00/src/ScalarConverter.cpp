/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:21:45 by nuno              #+#    #+#             */
/*   Updated: 2026/04/21 13:40:56 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ScalarConverter.hpp"

#include <cerrno>
#include <cstdlib>
#include <iomanip>

static int handlePseudo(std::string s);
static int handleDouble(std::string s);
static int handleFloat(std::string s);
static int handleInt(std::string s);
static int handleChar(std::string s);
static void printAll(double valueForCharInt, double valueForDouble, bool floatPossible, float valueForFloat);

//ScalarConverter::ScalarConveter() {} // the default constructor is private, so it cannot be called from outside the class. This is a common technique to prevent instantiation of a class that is meant to be used only for its static members.	

ScalarConverter::~ScalarConverter()
{
	std::cout << "[ScalarConverter] -> Default Destructor called!" << std::endl;
}

void ScalarConverter::convert(std::string string)
{
	if (handlePseudo(string)) // nan, inf, -inf, +inf and their float variants.
		return;
	if (string.length() == 1 && std::isdigit(static_cast<unsigned char>(string[0])) == 0) // we double check this inside handleChar, but we can save some time by checking it here first.
	{
		handleChar(string); // if it's a single non-digit character, we can directly handle it as a char without trying to parse it as a number. This is an optimization that allows us to skip unnecessary parsing steps for this specific case.
		return;
	}
	if (string.length() >= 2)
	{
		const char last = string[string.length() - 1];
		if (last == 'f' || last == 'F')
		{
			if (handleFloat(string))
				return;
			std::cerr << "Invalid input\n";
			return;
		}
	}
	if (string.find('.') != std::string::npos)
	{
		if (handleDouble(string))
			return;
		std::cerr << "Invalid input\n";
		return;
	}
	if (handleInt(string))
		return;
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
		const int code = static_cast<unsigned char>(s[0]);
		if (code < 32 || code > 126)
			std::cout << "char: Non displayable" << std::endl;
		else
			std::cout << "char: '" << s[0] << "'" << std::endl;
		std::cout << "int: " << code << std::endl;
		std::cout << std::fixed << std::setprecision(1); // Set fixed-point notation and precision to 1 for float and double output
		std::cout << "float: " << static_cast<float>(code) << "f" << std::endl;
		std::cout << "double: " << static_cast<double>(code) << std::endl;
		std::cout.unsetf(std::ios::fixed); // Unset fixed-point notation for any future output. No need to reset precision as it will be set explicitly in other handlers.
		return (1);
	}
	return (0);
}

static int handleInt(std::string s)
{
	std::stringstream ss(s);
	int number;
	ss >> number;
	if (ss.fail() || !ss.eof())
		return 0;
	// char
	if (number < 0 || number > 127)
		std::cout << "char: impossible" << std::endl;
	else if (number < 32 || number > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(number) << "'" << std::endl;
	// int
	std::cout << "int: " << number << std::endl;
	// float and double
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "float: " << static_cast<float>(number) << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(number) << std::endl;
	std::cout.unsetf(std::ios::fixed); // unsetf: unsets the specified formatting flags for the output stream. In this case, it unsets the fixed-point notation flag that was set earlier with std::fixed. This means that any subsequent floating-point output will not be forced to use fixed-point notation, and will instead use the default formatting based on the value being printed and the current precision settings. By calling unsetf after printing the float and double values, we ensure that any future floating-point output is not affected by the fixed-point formatting that we applied specifically for this output.
	return (1);
}

static int handleFloat(std::string s)
{
	if (s.length() < 2)
		return (0);
	const char last = s[s.length() - 1]; // grab the last character.
	if (last != 'f' && last != 'F')
		return (0);

	const std::string core = s.substr(0, s.length() - 1); // core is the part of the string without the trailing 'f' or 'F'.
	errno = 0; // reset errno by setting it to 0 before calling strtod to ensure that we can accurately detect if an overflow or underflow occurred during the conversion. If strtod encounters a value that is too large or too small to be represented as a double, it will set errno to ERANGE. By resetting errno to 0 beforehand, we can check its value after the call to strtod to determine if an error occurred.
	char *end = 0; // check explanation bellow
	const double parsed = std::strtod(core.c_str(), &end); // parsed will be the double value. The end pointer is used to determine if the entire string was successfully parsed as a valid floating-point number. After calling strtod, end will point to the first character in the string that was not part of the valid number. If end points to the beginning of the string (core.c_str()), it means that no valid number was found. If end points to a character that is not the null terminator ('\0'), it means that there are extra characters after the valid number, which also indicates an invalid input. Therefore, we check if end is equal to core.c_str() or if *end is not '\0' to determine if the parsing was successful and if the input is valid.
	if (end == core.c_str() || end == 0 || *end != '\0') // now we need end to point to the null terminator.
		return (0);
	if (errno == ERANGE)
		return (0);
	if (std::fabs(parsed) > static_cast<double>(std::numeric_limits<float>::max())) // if the absololute value of the parsed double is greater than the maximum representable float, then it's impossible to convert it to a float without overflow.
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return (1);
	}
	else if (parsed != 0.0 && std::fabs(parsed) < static_cast<double>(std::numeric_limits<float>::min()))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return (1);
	}

	const float number = static_cast<float>(parsed);
	const double d = static_cast<double>(number);
	printAll(d, static_cast<double>(number), true, number);
	return (1);
}

static int handleDouble(std::string s)
{
	if (s.find('.') == std::string::npos)
		return (0);
	if (s.length() > 1)
	{
		const char last = s[s.length() - 1];
		if (last == 'f' || last == 'F')
			return (0);
	}

	errno = 0;
	char *end = 0;
	const double number = std::strtod(s.c_str(), &end);
	if (end == s.c_str() || end == 0 || *end != '\0')
		return (0);
	if (errno == ERANGE)
		return (0);

	const bool floatPossible = (std::fabs(number) <= static_cast<double>(std::numeric_limits<float>::max()));
	printAll(number, number, floatPossible, static_cast<float>(number));
	return (1);
}

static void printAll(double valueForCharInt, double valueForDouble, bool floatPossible, float valueForFloat)
{
	const bool isInt = (valueForCharInt == std::floor(valueForCharInt));

	// char
	if (!isInt || valueForCharInt < 0.0 || valueForCharInt > 127.0)
		std::cout << "char: impossible" << std::endl;
	else if (static_cast<int>(valueForCharInt) < 32 || static_cast<int>(valueForCharInt) > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(static_cast<int>(valueForCharInt)) << "'" << std::endl;

	// int
	if (!isInt || valueForCharInt > static_cast<double>(std::numeric_limits<int>::max())
		|| valueForCharInt < static_cast<double>(std::numeric_limits<int>::min()))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(valueForCharInt) << std::endl;

	// float
	if (!floatPossible)
		std::cout << "float: impossible" << std::endl;
	else
	{
		std::ios::fmtflags oldFlags = std::cout.flags();
		std::streamsize oldPrec = std::cout.precision();
		if (isInt)
			std::cout << std::fixed << std::setprecision(1);
		else
		{
			const double absValue = std::fabs(valueForCharInt);
			if (absValue != 0.0 && (absValue >= 1e6 || absValue < 1e-4))
				std::cout << std::scientific << std::setprecision(5);
			else
				std::cout << std::setprecision(9);
		}
		std::cout << "float: " << valueForFloat << "f" << std::endl;
		std::cout.flags(oldFlags);
		std::cout.precision(oldPrec);
	}

	// double
	{
		std::ios::fmtflags oldFlags = std::cout.flags();
		std::streamsize oldPrec = std::cout.precision();
		if (isInt)
			std::cout << std::fixed << std::setprecision(1);
		else
			std::cout << std::setprecision(15);
		std::cout << "double: " << valueForDouble << std::endl;
		std::cout.flags(oldFlags);
		std::cout.precision(oldPrec);
	}
}
