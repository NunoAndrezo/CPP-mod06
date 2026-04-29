/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:22:08 by nuno              #+#    #+#             */
/*   Updated: 2026/04/29 12:48:41 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main(int ac, char **av)
{
	if (ac != 1)
		std::cout << "How to use: ./serializer" << std::endl, exit(1);
	(void)av;
	Data *student = new Data;
	student->name = "Martim Manha";
	student->grade = 19.7;
	std::cout << "Here is the original struct:" <<
				"\n\taddress: " << student <<
				"\n\tname: " << student->name <<
				"\n\tgrade: " << student->grade << std::endl << std::endl;
// ---------------------- Serialization ----------------------
	uintptr_t ptr = Serializer::serialize(student);

	std::cout << "Here is the uintptr_t:" <<
				"\n\tptr value in decimal: " << ptr <<
				"\n\tptr value in hexadecimal: " << std::hex << ptr << std::dec <<std::endl << std::endl;

// ---------------------- Deserialization ----------------------
	Data *stu_ptr = Serializer::deserialize(ptr);

	std::cout << "Here is the copied struct:" <<
				"\n\taddress: " << stu_ptr <<
				"\n\tname: " << stu_ptr->name <<
				"\n\tgrade: " << stu_ptr->grade << std::endl;
	delete student;
	return (0);
}