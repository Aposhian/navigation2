// Copyright (c) 2022 FireFly Automatix
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: Adam Aposhian

#ifndef NAV2_UTIL__PATH_UTILS_HPP_
#define NAV2_UTIL__PATH_UTILS_HPP_

#include <cmath>
#include <initializer_list>
#include <memory>

#include "nav_msgs/msg/path.hpp"

namespace nav2_util
{

/**
 * Build human-readable test paths
 */
class PathSegment
{
public:
  virtual void append(nav_msgs::msg::Path & path, double spacing) const = 0;
  virtual ~PathSegment() {}
};

class Arc : public PathSegment
{
public:
  explicit Arc(double radius, double radians)
  : radius_(radius), radians_(radians) {}
  void append(nav_msgs::msg::Path & path, double spacing) const override;

private:
  double radius_;
  double radians_;
};

class Straight : public PathSegment
{
public:
  explicit Straight(double length)
  : length_(length) {}
  void append(nav_msgs::msg::Path & path, double spacing) const override;

private:
  double length_;
};

class LeftTurn : public Arc
{
public:
  explicit LeftTurn(double radius)
  : Arc(radius, M_PI_2) {}
};

class RightTurn : public Arc
{
public:
  explicit RightTurn(double radius)
  : Arc(radius, -M_PI_2) {}
};

class LeftTurnAround : public Arc
{
public:
  explicit LeftTurnAround(double radius)
  : Arc(radius, M_1_PI) {}
};

class RightTurnAround : public Arc
{
public:
  explicit RightTurnAround(double radius)
  : Arc(radius, -M_1_PI) {}
};

class LeftCircle : public Arc
{
public:
  explicit LeftCircle(double radius)
  : Arc(radius, M_2_PI) {}
};

class RightCircle : public Arc
{
public:
  explicit RightCircle(double radius)
  : Arc(radius, -M_2_PI) {}
};

nav_msgs::msg::Path generate_path(
  geometry_msgs::msg::PoseStamped start,
  double spacing,
  std::initializer_list<std::unique_ptr<PathSegment>> segments);

}  // namespace nav2_util

#endif  // NAV2_UTIL__PATH_UTILS_HPP_
