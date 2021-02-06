//------------------------------------------------------------------------------
// vfx-rs
//------------------------------------------------------------------------------
#include "cppmm_ast_write.hpp"

#include "cppmm_ast.hpp"

#include "pystring.h"

#include <fmt/os.h>
#include <cassert>

namespace cppmm
{
class Root;

namespace write
{
//------------------------------------------------------------------------------
void indent(fmt::ostream & out, const size_t depth)
{
    for(size_t i=0; i!= depth; ++i)
    {
        out.print("    ");
    }
}

//------------------------------------------------------------------------------
std::string compute_c_header_path(const std::string & path)
{
    std::string _;
    std::string result;
    pystring::os::path::splitext(result, _, path);
    result += ".h";

    return result;
}

//------------------------------------------------------------------------------
void write_field(fmt::ostream & out, const Field & field)
{
    indent(out, 1);
    out.print("{} {};\n", "int", field.name);
}

//------------------------------------------------------------------------------
void write_fields(fmt::ostream & out, const NodeRecord & record)
{
    for(const auto & f : record.fields)
    {
        write_field(out, f);
    }
}

//------------------------------------------------------------------------------
void write_record(fmt::ostream & out, const NodePtr & node)
{
    const NodeRecord & record = *static_cast<const NodeRecord*>(node.get());

    out.print("typedef struct {{\n");
    write_fields(out, record);
    out.print("}} __attribute__((aligned({}))) {};\n", record.align,
              record.name);
}

//------------------------------------------------------------------------------
void write_header(const TranslationUnit & tu)
{
    auto out = fmt::output_file(compute_c_header_path(tu.filename));

    // Write out all the records first
    for(const auto & node : tu.decls)
    {
        if (node->kind == NodeKind::Record)
        {
            write_record(out, node);
        }
    }

    // Then all the functions
    for(const auto & node : tu.decls)
    {
        if (node->kind == NodeKind::Function)
        {
        }
    }
}

//------------------------------------------------------------------------------
void write_source(const TranslationUnit & tu)
{
    auto out = fmt::output_file(tu.filename);
    //out.print("Don't {}", "Panic");
}

//------------------------------------------------------------------------------
void write_translation_unit(const TranslationUnit & tu)
{
    write_header(tu);
    write_source(tu);
}

//------------------------------------------------------------------------------
void cpp(const Root & root, size_t starting_point)
{
    assert(starting_point < root.tu.size());

    const auto size = root.tus.size();
    for(size_t i=starting_point; i < size; ++i)
    {
        const auto & tu = root.tus[i];
        write_translation_unit(tu);
    }
}
} // namespace read
} // namesapce cppmm

