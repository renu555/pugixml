// This file includes all tests for deprecated functionality; this is going away in the next release!

#ifdef _MSC_VER
#	pragma warning(disable: 4996)
#endif

#ifdef __GNUC__
#	if __GNUC__ >= 4 && __GNUC_MINOR__ >= 2
#		pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#	else
#		define PUGIXML_DEPRECATED
#	endif
#endif

#ifdef __INTEL_COMPILER
#	pragma warning(disable: 1478)
#endif

#include <string.h>

#include "common.hpp"

#include "writer_string.hpp"

#include <vector>
#include <iterator>

// parse - it's now load_buffer_inplace
TEST(document_parse)
{
	char text[] = "<node/>";

	pugi::xml_document doc;

	CHECK(doc.parse(text));
	CHECK_NODE(doc, STR("<node />"));
}

// parse with transfer_ownership_tag attribute - it's now load_buffer_inplace_own
TEST(document_parse_transfer_ownership)
{
	allocation_function alloc = get_memory_allocation_function();

	char* text = static_cast<char*>(alloc(strlen("<node/>") + 1));
	CHECK(text);

	memcpy(text, "<node/>", strlen("<node/>") + 1);

	pugi::xml_document doc;

	CHECK(doc.parse(transfer_ownership_tag(), text));
	CHECK_NODE(doc, STR("<node />"));
}

#ifndef PUGIXML_NO_STL
// as_utf16 - it's now as_wide
TEST(as_utf16)
{
	CHECK(as_utf16("") == L"");

	// valid 1-byte, 2-byte and 3-byte inputs
#ifdef U_LITERALS
	CHECK(as_utf16("?\xd0\x80\xe2\x80\xbd") == L"?\u0400\u203D");
#else
	CHECK(as_utf16("?\xd0\x80\xe2\x80\xbd") == L"?\x0400\x203D");
#endif
}
#endif
