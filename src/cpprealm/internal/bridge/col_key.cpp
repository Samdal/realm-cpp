#include <cpprealm/internal/bridge/col_key.hpp>
#include <cpprealm/internal/bridge/utils.hpp>
#include <realm/keys.hpp>

namespace realm::internal::bridge {
#ifdef __i386__
    static_assert(SizeCheck<8, sizeof(ColKey)>{});
    static_assert(SizeCheck<4, alignof(ColKey)>{});
#elif __x86_64__
    static_assert(SizeCheck<8, sizeof(ColKey)>{});
    static_assert(SizeCheck<8, alignof(ColKey)>{});
#elif __arm__
    static_assert(SizeCheck<8, sizeof(ColKey)>{});
    static_assert(SizeCheck<8, alignof(ColKey)>{});
#elif __aarch64__
    static_assert(SizeCheck<8, sizeof(ColKey)>{});
    static_assert(SizeCheck<8, alignof(ColKey)>{});
#elif _WIN32
    static_assert(SizeCheck<8, sizeof(ColKey)>{});
    static_assert(SizeCheck<8, alignof(ColKey)>{});
#endif

    col_key::col_key() noexcept {
        new (&m_col_key) ColKey();
    }
    col_key::col_key(const col_key& other) {
        new (&m_col_key) ColKey(*reinterpret_cast<const ColKey *>(&other.m_col_key));
    }
    col_key& col_key::operator=(const col_key& other) {
        if (this != &other) {
            *reinterpret_cast<ColKey *>(&m_col_key) = *reinterpret_cast<const ColKey *>(&other.m_col_key);
        }
        return *this;
    }
    col_key::col_key(col_key&& other) {
        new (&m_col_key) ColKey(std::move(*reinterpret_cast<ColKey *>(&other.m_col_key)));
    }
    col_key& col_key::operator=(col_key&& other) {
        if (this != &other) {
            *reinterpret_cast<ColKey *>(&m_col_key) = std::move(*reinterpret_cast<ColKey *>(&other.m_col_key));
        }
        return *this;
    }
    col_key::~col_key() {
        reinterpret_cast<ColKey *>(&m_col_key)->~ColKey();
    }
    col_key::col_key(int64_t v) {
        new (&m_col_key) ColKey(v);
    }
    col_key::col_key(const ::realm::ColKey &v) {
        new (&m_col_key) ColKey(v);
    }

    int64_t col_key::value() const {
        return reinterpret_cast<const ColKey *>(&m_col_key)->value;
    }
    col_key::operator bool() const {
        return reinterpret_cast<const ColKey *>(&m_col_key);
    }
    col_key::operator ColKey() const {
        return *reinterpret_cast<const ColKey *>(&m_col_key);
    }
}
