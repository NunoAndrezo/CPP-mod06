/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:43:10 by nuno              #+#    #+#             */
/*   Updated: 2026/04/29 12:50:07 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::~Serializer()
{}

uintptr_t Serializer::serialize(Data *ptr)
{
	if (!ptr)
		std::cout << "Whiskas saquetas\n", exit(1);
	uintptr_t uintptr = reinterpret_cast<uintptr_t>(ptr);
	return (uintptr);
}

Data *Serializer::deserialize(uintptr_t raw)
{
	if (!raw)
		std::cout << "MotoRatos de marte\n", exit(1);
	Data *aleluia;
	aleluia = reinterpret_cast<Data *>(raw);
	return (aleluia);
}