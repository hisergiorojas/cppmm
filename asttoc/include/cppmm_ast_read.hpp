//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#pragma once
#include <istream>
#include "cppmm_ast.hpp"

namespace cppmm
{
namespace read
{
Root json(std::istream & input);
} // namespace read
} // namesapce cppmm
