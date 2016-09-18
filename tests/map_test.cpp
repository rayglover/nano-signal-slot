#include "../nano_signal_slot.hpp"

#include <functional>
#include <iostream>
#include <vector>
#include <cassert>
#include <tuple>

//------------------------------------------------------------------------------

// To utilize automatic disconnect you must inherit from Nano::Observer
struct Foo : public Nano::Observer
{
    bool handler_a(const char* sl, int x) const
    {
        std::cout << "[" << sl << "] " << x << std::endl;
        return true;
    }
};

auto add_one (const char* sl) { return std::make_tuple("add one", std::stoi(sl) + 1); }
auto add_two (const char* sl) { return std::make_tuple("add two", std::stoi(sl) + 2); }

//------------------------------------------------------------------------------

int main()
{
    // Declare Nano::Signals using function signature syntax
    Nano::Signal<bool(const char*)> signal_one;

    // Create a new scope to test automatic disconnect
    {
        Foo foo;

        // Connect member functions to mapped Nano::Signals
        signal_one.map<const char*, int>()
            .connect<Foo, &Foo::handler_a, add_one>(&foo);

        signal_one.map<const char*, int>()
            .connect<Foo, &Foo::handler_a, add_two>(&foo);

        // Emit Signals
        signal_one.emit("3");
        signal_one.emit("4");

        // Remove all connections
        signal_one.removeAll();
    }

    // Pause the screen
    std::cin.get();
}
