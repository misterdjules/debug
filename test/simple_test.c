#include <debug.h>

TEST(SimpleTests, OutputIsLogged)
{
	debug_context_t* debug_context = debug_create_context("foo");
	debug(debug_context, "Foo\n");
}