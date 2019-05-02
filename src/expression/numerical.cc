/*
 * Copyright (C) 2014-2018 Olzhas Rakhimov
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/// @file
/// Implementation of various numerical expressions.

#include "numerical.h"

#include "src/error.h"

namespace scram::mef {


Mean::Mean(std::vector<Expression*> args) : ExpressionFormula(std::move(args)) {
  if (Expression::args().size() < 2)
    SCRAM_THROW(ValidityError("Expression requires 2 or more arguments."));
}

}  // namespace scram::mef
