/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 23:03:28 by nuno              #+#    #+#             */
/*   Updated: 2026/04/29 23:58:56 by nuno             ###   ########.fr       */
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
	if (dynamic_cast<A *>(p))
		std::cout << "It's A :)" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "It's B :)" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "It's C :)" << std::endl;
}

void identify(Base &p)
{
	
}
