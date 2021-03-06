/*
 * Copyright (C) 2017-2018 Olzhas Rakhimov
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

#pragma once

#include <initializer_list>
#include <utility>

#include <QtTest>

namespace detail {

/// Initializes columns in the test data table.
///
/// @tparam Ts  void terminated type list.
template <typename T, typename... Ts>
void initializeColumns(const char *const *it)
{
    QTest::addColumn<T>(*it);

    if constexpr (sizeof...(Ts))
        initializeColumns<Ts...>(++it);
}

/// Initializes rows in the test data table.
///
/// @tparam N  The number of columns to initialize in the row.
template <int N, typename... Ts>
void initializeRows(QTestData &data, const std::tuple<const char *, Ts...> &row)
{
    static_assert(N >= 0);

    if constexpr (N != 0) {
        initializeRows<N - 1>(data, row);
        data << std::get<N>(row);
    }
}

} // namespace detail

/// Convenience function to populate QTest data table.
///
/// @tparam Ts  The column data types.
///
/// @param[in] columns  The column names.
/// @param[in] rows  The row name and data.
template <typename... Ts>
void populateData(const char *const (&columns)[sizeof...(Ts)],
                  std::initializer_list<std::tuple<const char *, Ts...>> rows)
{
    detail::initializeColumns<Ts...>(columns);

    for (const auto &row : rows)
        detail::initializeRows<sizeof...(Ts)>(QTest::newRow(std::get<0>(row)),
                                              row);
}
