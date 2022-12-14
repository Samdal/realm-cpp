#include <cpprealm/internal/bridge/uuid.hpp>
#include <realm/uuid.hpp>
#include <cpprealm/internal/bridge/utils.hpp>
#include <cpprealm/persisted_uuid.hpp>

namespace realm::internal::bridge {
    static_assert(SizeCheck<16, sizeof(::realm::UUID)>{});
    uuid::uuid() {
        new (&m_uuid) UUID();
    }
    uuid::uuid(const std::string &v) {
        new (&m_uuid) UUID(v);
    }
    uuid::uuid(const ::realm::uuid &v)
    {
        new (&m_uuid) UUID(v.to_string());
    }
    uuid::uuid(const UUID &v) {
        new (&m_uuid) UUID(v);
    }

    std::string uuid::to_string() const {
        return reinterpret_cast<const UUID*>(m_uuid)->to_string();
    }

    uuid::operator ::realm::uuid() const {
        return ::realm::uuid(*this);
    }

    uuid::operator UUID() const {
        return *reinterpret_cast<const UUID*>(m_uuid);
    }

    std::string uuid::to_base64() const {
        return reinterpret_cast<const UUID*>(m_uuid)->to_base64();
    }

    std::array<uint8_t, 16> uuid::to_bytes() const {
        return reinterpret_cast<const UUID*>(m_uuid)->to_bytes();
    }

#define __cpp_realm_gen_uuid_op(op) \
    bool operator op(const uuid& a, const uuid& b) { \
        return *reinterpret_cast<const UUID*>(a.m_uuid) op *reinterpret_cast<const UUID*>(b.m_uuid);                                        \
    }

    __cpp_realm_gen_uuid_op(==)
    __cpp_realm_gen_uuid_op(!=)
    __cpp_realm_gen_uuid_op(>)
    __cpp_realm_gen_uuid_op(<)
    __cpp_realm_gen_uuid_op(>=)
    __cpp_realm_gen_uuid_op(<=)
}