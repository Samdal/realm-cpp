#include <cpprealm/internal/bridge/lnklst.hpp>
#include <cpprealm/internal/bridge/obj.hpp>
#include <cpprealm/internal/bridge/obj_key.hpp>
#include <cpprealm/internal/bridge/utils.hpp>

#include <realm/list.hpp>

namespace realm::internal::bridge {
#ifdef __i386__
    static_assert(SizeCheck<104, sizeof(LnkLst)>{});
    static_assert(SizeCheck<4, alignof(LnkLst)>{});
#elif __x86_64__
    static_assert(SizeCheck<160, sizeof(LnkLst)>{});
    static_assert(SizeCheck<8, alignof(LnkLst)>{});
#elif __arm__
    static_assert(SizeCheck<128, sizeof(LnkLst)>{});
    static_assert(SizeCheck<8, alignof(LnkLst)>{});
#elif __aarch64__
    static_assert(SizeCheck<160, sizeof(LnkLst)>{});
    static_assert(SizeCheck<8, alignof(LnkLst)>{});
#elif _WIN32
    static_assert(SizeCheck<8, alignof(LnkLst)>{});
    #if _DEBUG
    static_assert(SizeCheck<168, sizeof(LnkLst)>{});
    #else
    static_assert(SizeCheck<160, sizeof(LnkLst)>{});
    #endif
#endif
    
    lnklst::lnklst() {
        new (&m_lnk_lst) LnkLst();
    }
    
    lnklst::lnklst(const lnklst& other) {
        new (&m_lnk_lst) LnkLst(*reinterpret_cast<const LnkLst*>(&other.m_lnk_lst));
    }

    lnklst& lnklst::operator=(const lnklst& other) {
        if (this != &other) {
            *reinterpret_cast<LnkLst*>(&m_lnk_lst) = *reinterpret_cast<const LnkLst*>(&other.m_lnk_lst);
        }
        return *this;
    }

    lnklst::lnklst(lnklst&& other) {
        new (&m_lnk_lst) LnkLst(std::move(*reinterpret_cast<LnkLst*>(&other.m_lnk_lst)));
    }

    lnklst& lnklst::operator=(lnklst&& other) {
        if (this != &other) {
            *reinterpret_cast<LnkLst*>(&m_lnk_lst) = std::move(*reinterpret_cast<LnkLst*>(&other.m_lnk_lst));
        }
        return *this;
    }

    lnklst::~lnklst() {
        reinterpret_cast<LnkLst*>(&m_lnk_lst)->~LnkLst();
    }

    lnklst::lnklst(const LnkLst &v) {
        new (&m_lnk_lst) LnkLst(v);
    }

    obj lnklst::create_and_insert_linked_object(size_t idx) {
        return reinterpret_cast<LnkLst*>(&m_lnk_lst)->create_and_insert_linked_object(idx);
    }

    void lnklst::add(const obj_key &v) {
        return reinterpret_cast<LnkLst*>(&m_lnk_lst)->add(v);
    }

    lnklst::operator LnkLst() const {
        return *reinterpret_cast<const LnkLst*>(&m_lnk_lst);
    }
}