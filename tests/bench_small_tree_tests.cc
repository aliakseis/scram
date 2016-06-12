/*
 * Copyright (C) 2014-2016 Olzhas Rakhimov
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

#include <gtest/gtest.h>

#include "risk_analysis_tests.h"

namespace scram {
namespace core {
namespace test {

// Benchmark Tests for Small Tree fault tree from XFTA.
// This benchmark is for uncertainty analysis.
TEST_P(RiskAnalysisTest, SmallTree) {
  std::string tree_input = "./share/scram/input/SmallTree/SmallTree.xml";
  settings.uncertainty_analysis(true);
  settings.num_trials(10000);
  ASSERT_NO_THROW(ProcessInputFile(tree_input));
  ASSERT_NO_THROW(ran->Analyze());
  std::set<std::set<std::string>> mcs = {{"e1", "e2"}, {"e3", "e4"}};
  EXPECT_EQ(2, products().size());
  EXPECT_EQ(mcs, products());
  EXPECT_NEAR(0.02569, mean(), 1e-3);
  EXPECT_NEAR(0.018065, sigma(), 2e-3);
}

}  // namespace test
}  // namespace core
}  // namespace scram