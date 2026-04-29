/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 11:42:29 by nuno              #+#    #+#             */
/*   Updated: 2026/04/29 12:33:43 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdint.h>
#include <cstdlib>

struct Data
{
	std::string	name;
	double		grade;
};

class Serializer
{
	private:
		Serializer(void);
		Serializer(const Serializer &other);
		Serializer &operator=(const Serializer &other);
	public:
		~Serializer();
		static uintptr_t serialize(Data *ptr);
		static Data *deserialize(uintptr_t raw);
};