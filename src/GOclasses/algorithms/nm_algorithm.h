/*****************************************************************************
 *   Copyright (C) 2008, 2009 Advanced Concepts Team (European Space Agency) *
 *   act@esa.int                                                             *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

// 03/02/2009: Initial version by Francesco Biscani.

#ifndef PAGMO_NM_ALGORITHM_H
#define PAGMO_NM_ALGORITHM_H

#include <iostream>
#include <utility>
#include <vector>

#include "../../config.h"
#include "../basic/population.h"
#include "../problems/GOproblem.h"
#include "go_algorithm.h"

/// Nelder-Mead algorithm.
/**
 * See http://en.wikipedia.org/wiki/Nelder-Mead_method
 */
class __PAGMO_VISIBLE nm_algorithm: public go_algorithm {
		typedef std::vector<std::pair<std::vector<double>,double> > simplex;
	public:
		nm_algorithm(int, const double &, const double &, const double &, const double &);
		virtual Population evolve(const Population &) const;
		virtual nm_algorithm *clone() const {return new nm_algorithm(*this);}
	private:
		std::vector<double> center_mass(const simplex &) const;
		std::vector<double> sub_mult_add(const std::vector<double> &, const std::vector<double> &,
			const double &, const std::vector<double> &) const;
		void check_bounds(std::vector<double> &, const GOProblem &) const;
		double simplex_diameter(const simplex &) const;
		void shuffle_simplex(simplex &, const GOProblem &) const;
		virtual void log(std::ostream &) const;
		// Number of generations.
		const size_t	m_gen;
		// Reflection coefficient.
		const double	m_alpha;
		// Expansion coefficient.
		const double	m_gamma;
		// Contraction coefficient.
		const double	m_rho;
		// Shrink coefficient.
		const double	m_sigma;
};

#endif