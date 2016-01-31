#ifndef NANO_EXTRAS_HPP
#define NANO_EXTRAS_HPP

#include "nano_signal_slot.hpp"

namespace Nano {

template<typename T>
struct VisitorBase
{
    virtual void visit(Signal<T>& s) = 0;
};

template <typename T, T>
struct Callback
    : public VisitorBase<T>
{
};

template <typename T, typename RT, typename ...Args, RT (T::* mf)(Args...)>
struct Callback<RT (T::*)(Args...), mf>
    : public VisitorBase<RT(Args...)>
{
    T* m_ptr;

    Callback(T* ptr)
        : m_ptr { ptr } {
    }

    virtual void visit(Signal<RT(Args...)>& s) override {
        s.template connect<T, mf>(m_ptr);
    }
};

} // namespace Nano ------------------------------------------------------------

#endif
