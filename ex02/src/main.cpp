/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 23:03:28 by nuno              #+#    #+#             */
/*   Updated: 2026/05/01 13:17:55 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Base.hpp"
#include "../inc/A.hpp"
#include "../inc/B.hpp"
#include "../inc/C.hpp"

#include <cstdlib>
#include <cstdio>
#include <iostream>

Base *generate(void);
void identify(Base *p);
void identify(Base &p); // cannot use a pointer inside this function!!!!!!

int	main(int ac, char **av)
{
	if (ac != 1)
	{
		std::cerr << "Try the following: " << av[0] << std::endl;
		return (1);
	}
	Base *bricky_bobby;

	srand(time(NULL));
	bricky_bobby = generate();
	if (!bricky_bobby)
	{
		std::cerr << "Bricky Bobby no more!" << std::endl;
		return 1;
	}
	identify(bricky_bobby);
	identify(*bricky_bobby);
	delete bricky_bobby;
	return (0);
}

Base *generate(void)
{
	int random;

	random = rand() % 3;
	if (random == 0)
		return (new A);
	else if (random == 1)
		return new B;
	else if (random == 2)
		return new C;
	else
	{
		std::cerr << "Blyat Rand()" << std::endl;
		return NULL;
	}
}

void identify(Base *p)
{
	std::cout << "Idenfify by pointer: " << std::endl;
	if (dynamic_cast<A *>(p))
		std::cout << "It's A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "It's B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "It's C" << std::endl;
}

void identify(Base &p)
{
	std::cout << "Idenfify by reference: " << std::endl;
	try
	{
		A &a = dynamic_cast<A&>(p); // dynamic_cast already throws: std::bad_cast, if failed
		(void)a;
		std::cout << "Still A :)" << std::endl;
	}
	catch (std::exception &e) {}
	try
	{
		B &b = dynamic_cast<B&>(p);
		(void)b;
		std::cout << "Still B :)" << std::endl;
	}
	catch (std::exception &e) {}
	try
	{
		C &c = dynamic_cast<C&>(p);
		(void)c;
		std::cout << "Still C :)" << std::endl;
	}
	catch (std::exception &e) {}
}
