#include <cpprealm/internal/bridge/obj.hpp>

#include <realm/dictionary.hpp>
#include <realm/list.hpp>
#include <realm/table_view.hpp>

#include <realm/object-store/object_store.hpp>
#include <realm/object-store/shared_realm.hpp>

#include <cpprealm/object.hpp>
#include <cpprealm/internal/type_info.hpp>

#include <cpprealm/internal/bridge/dictionary.hpp>
#include <cpprealm/internal/bridge/lnklst.hpp>
#include <cpprealm/internal/bridge/obj_key.hpp>
#include <cpprealm/internal/bridge/timestamp.hpp>
#include <cpprealm/internal/bridge/uuid.hpp>

#include <cpprealm/internal/bridge/utils.hpp>
#include <cpprealm/internal/bridge/realm.hpp>

namespace realm::internal::bridge {
#ifdef __i386__
    static_assert(SizeCheck<44, sizeof(Obj)>{});
    static_assert(SizeCheck<4, alignof(Obj)>{});
#elif __x86_64__
    static_assert(SizeCheck<64, sizeof(Obj)>{});
    static_assert(SizeCheck<8, alignof(Obj)>{});
#elif __arm__
    static_assert(SizeCheck<56, sizeof(Obj)>{});
    static_assert(SizeCheck<8, alignof(Obj)>{});
#elif __aarch64__
    static_assert(SizeCheck<64, sizeof(Obj)>{});
    static_assert(SizeCheck<8, alignof(Obj)>{});
#elif _WIN32
    static_assert(SizeCheck<64, sizeof(Obj)>{});
    static_assert(SizeCheck<8, alignof(Obj)>{});
#endif
    
    obj::obj() {
        new (&m_obj) Obj();
    }
    
    obj::obj(const obj& other) {
        new (&m_obj) Obj(*reinterpret_cast<const Obj*>(&other.m_obj));
    }

    obj& obj::operator=(const obj& other) {
        if (this != &other) {
            *reinterpret_cast<Obj*>(&m_obj) = *reinterpret_cast<const Obj*>(&other.m_obj);
        }
        return *this;
    }

    obj::obj(obj&& other) {
        new (&m_obj) Obj(std::move(*reinterpret_cast<Obj*>(&other.m_obj)));
    }

    obj& obj::operator=(obj&& other) {
        if (this != &other) {
            *reinterpret_cast<Obj*>(&m_obj) = std::move(*reinterpret_cast<Obj*>(&other.m_obj));
        }
        return *this;
    }

    obj::~obj() {
        reinterpret_cast<Obj*>(&m_obj)->~Obj();
    }
    
    group::group(realm& val)
    : m_realm(val)
    {
    }

    group realm::read_group() {
        return *this;
    }

    obj::obj(const Obj& v) {
        new (&m_obj) Obj(v);
    }

    obj::operator Obj() const {
        return *reinterpret_cast<const Obj*>(&m_obj);
    }
    
    obj_key obj::get_key() const {
        return reinterpret_cast<const Obj*>(&m_obj)->get_key();
    }
    obj_link obj::get_link() const {
        return reinterpret_cast<const Obj*>(&m_obj)->get_link();
    }
    table obj::get_table() const noexcept {
        return reinterpret_cast<const Obj*>(&m_obj)->get_table();
    }
    table obj::get_target_table(col_key key) const noexcept {
        return reinterpret_cast<const Obj*>(&m_obj)->get_target_table(key);
    }
    
    obj obj::get_linked_object(const col_key &col_key) {
        return reinterpret_cast<Obj*>(&m_obj)->get_linked_object(col_key);
    }
    bool obj::is_null(const col_key &col_key) const {
        return reinterpret_cast<const Obj*>(&m_obj)->is_null(col_key);
    }
    bool obj::is_valid() const {
        return reinterpret_cast<const Obj*>(&m_obj)->is_valid();
    }
    template <>
    std::string get(const obj& o, const col_key& col_key) {
        return reinterpret_cast<const Obj*>(&o.m_obj)->get<StringData>(col_key);
    }
    template <>
    int64_t get(const obj& o, const col_key& col_key) {
        return reinterpret_cast<const Obj*>(&o.m_obj)->get<Int>(col_key);
    }
    template <>
    double get(const obj& o, const col_key& col_key) {
        return reinterpret_cast<const Obj*>(&o.m_obj)->get<Double>(col_key);
    }
    template <>
    bool get(const obj& o, const col_key& col_key) {
        return reinterpret_cast<const Obj*>(&o.m_obj)->get<bool>(col_key);
    }
    template <>
    binary get(const obj& o, const col_key& col_key) {
        return reinterpret_cast<const Obj*>(&o.m_obj)->get<BinaryData>(col_key);
    }
    template <>
    uuid get(const obj& o, const col_key& col_key) {
        return reinterpret_cast<const Obj*>(&o.m_obj)->get<UUID>(col_key);
    }
    template <>
    object_id get(const obj& o, const col_key& col_key) {
        return reinterpret_cast<const Obj*>(&o.m_obj)->get<ObjectId>(col_key);
    }
    template <>
    decimal128 get(const obj& o, const col_key& col_key) {
        return reinterpret_cast<const Obj*>(&o.m_obj)->get<Decimal128>(col_key);
    }
    template <>
    mixed get(const obj& o, const col_key& col_key) {
        return reinterpret_cast<const Obj*>(&o.m_obj)->get_any(col_key);
    }
    template <>
    timestamp get(const obj& o, const col_key& col_key) {
        return reinterpret_cast<const Obj*>(&o.m_obj)->get<Timestamp>(col_key);
    }
    template <>
    core_dictionary get(const obj& o, const col_key& col_key) {
        return reinterpret_cast<const Obj*>(o.m_obj)->get_dictionary(col_key);
    }

    void obj::set(const col_key &col_key, const std::string &value) {
        reinterpret_cast<Obj*>(&m_obj)->set<StringData>(col_key, value);
    }
    void obj::set(const col_key &col_key, const binary &value) {
        reinterpret_cast<Obj*>(&m_obj)->set<BinaryData>(col_key, value);
    }
    void obj::set(const col_key &col_key, const int64_t &value) {
        reinterpret_cast<Obj*>(&m_obj)->set<Int>(col_key, value);
    }
    void obj::set(const col_key &col_key, const bool &value) {
        reinterpret_cast<Obj*>(&m_obj)->set<Bool>(col_key, value);
    }
    void obj::set(const col_key &col_key, const double &value) {
        reinterpret_cast<Obj*>(&m_obj)->set<Double>(col_key, value);
    }
    void obj::set(const col_key &col_key, const internal::bridge::uuid &value) {
        reinterpret_cast<Obj*>(&m_obj)->set<UUID>(col_key, value);
    }
    void obj::set(const col_key &col_key, const internal::bridge::object_id &value) {
        reinterpret_cast<Obj*>(&m_obj)->set<ObjectId>(col_key, value);
    }
    void obj::set(const col_key &col_key, const internal::bridge::decimal128 &value) {
        reinterpret_cast<Obj*>(&m_obj)->set<Decimal128>(col_key, value);
    }
    void obj::set(const col_key &col_key, const obj_key &value) {
        reinterpret_cast<Obj*>(&m_obj)->set<ObjKey>(col_key, value);
    }
    void obj::set(const col_key &col_key, const mixed &value) {
      if (value.is_null()) {
           reinterpret_cast<Obj*>(&m_obj)->set(col_key, Mixed());
       } else if (value.type() == data_type::Link) {
           reinterpret_cast<Obj *>(&m_obj)->set(col_key,
                                               Mixed(ObjLink(reinterpret_cast<Obj *>(&m_obj)->get_table()->get_key(),
                                                              value.operator bridge::obj_key())));
        } else {
            reinterpret_cast<Obj*>(&m_obj)->set(col_key, value.operator ::realm::Mixed());
        }
    }
    void obj::set(const col_key &col_key, const timestamp &value) {
        reinterpret_cast<Obj*>(&m_obj)->set<Timestamp>(col_key, value);
    }
    void obj::set(const col_key& col_key, const std::chrono::time_point<std::chrono::system_clock>& value) {
        reinterpret_cast<Obj*>(m_obj)->set<Timestamp>(col_key, value);
    }
    lnklst obj::get_linklist(const col_key &col_key) {
        return reinterpret_cast<Obj*>(&m_obj)->get_linklist(col_key);
    }
    core_dictionary obj::get_dictionary(const col_key& col_key) {
        return reinterpret_cast<Obj*>(m_obj)->get_dictionary(col_key);
    }

    void obj::set_list_values(const col_key &col_key, const std::vector<obj_key> &values) {
        std::vector<ObjKey> v;
        for (auto& v2 : values) {
            v.push_back(v2);
        }
        reinterpret_cast<Obj*>(&m_obj)->set_list_values(col_key, v);
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<bool>& values) {
        if (values.empty())
            return;
        auto list = reinterpret_cast<Obj*>(m_obj)->get_list<bool>(col_key);
        for (size_t i = 0; i < values.size(); ++i) {
            list.add(values[i]);
        }
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<int64_t> &values) {
        reinterpret_cast<Obj*>(&m_obj)->set_list_values(col_key, values);
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<double> &values) {
        reinterpret_cast<Obj*>(&m_obj)->set_list_values(col_key, values);
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<internal::bridge::uuid> &values) {
        std::vector<UUID> v;
        for (auto& v2 : values) {
            v.push_back(v2);
        }
        reinterpret_cast<Obj*>(&m_obj)->set_list_values(col_key, v);
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<internal::bridge::object_id> &values) {
        std::vector<ObjectId> v;
        for (auto& v2 : values) {
            v.push_back(v2);
        }
        reinterpret_cast<Obj*>(&m_obj)->set_list_values(col_key, v);
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<internal::bridge::decimal128> &values) {
        std::vector<Decimal128> v;
        for (auto& v2 : values) {
            v.push_back(v2);
        }
        reinterpret_cast<Obj*>(&m_obj)->set_list_values(col_key, v);
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<binary> &values) {
        std::vector<BinaryData> v;
        for (auto& v2 : values) {
            v.push_back(v2);
        }
        reinterpret_cast<Obj*>(&m_obj)->set_list_values(col_key, v);
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<std::string> &values) {
        std::vector<StringData> v;
        for (auto& v2 : values) {
            v.emplace_back(v2);
        }
        reinterpret_cast<Obj*>(&m_obj)->set_list_values(col_key, v);
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<timestamp> &values) {
        std::vector<Timestamp> v;
        for (auto& v2 : values) {
            v.emplace_back(v2);
        }
        reinterpret_cast<Obj*>(&m_obj)->set_list_values(col_key, v);
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<mixed> &values) {
       auto list = reinterpret_cast<Obj*>(m_obj)->get_list<Mixed>(col_key);
        auto size = values.size();
        for (size_t i = 0; i < size; ++i) {
            list.insert(i, values[i].operator Mixed());
        }
    }

    void obj::set_list_values(const col_key &col_key, const std::vector<std::optional<int64_t>> &values) {
        reinterpret_cast<Obj*>(m_obj)->set_list_values(col_key, values);
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<std::optional<bool>> &values) {
        reinterpret_cast<Obj*>(m_obj)->set_list_values(col_key, values);
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<std::optional<double>> &values) {
        reinterpret_cast<Obj*>(m_obj)->set_list_values(col_key, values);
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<std::optional<std::string>> &values) {
        auto list = reinterpret_cast<Obj*>(m_obj)->get_list<StringData>(col_key);
        auto size = values.size();
        for (size_t i = 0; i < size; ++i) {
            if (values[i]) {
                list.insert(i, *values[i]);
            } else {
                list.insert_null(i);
            }
        }
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<std::optional<obj_key>> &values) {
        auto list = reinterpret_cast<Obj*>(m_obj)->get_list<ObjKey>(col_key);
        auto size = values.size();
        for (size_t i = 0; i < size; ++i) {
            if (values[i]) {
                list.insert(i, *values[i]);
            } else {
                list.insert_null(i);
            }
        }
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<std::optional<internal::bridge::uuid>> &values) {
        auto list = reinterpret_cast<Obj*>(m_obj)->get_list<std::optional<UUID>>(col_key);
        auto size = values.size();
        for (size_t i = 0; i < size; ++i) {
            if (values[i]) {
                list.insert(i, *values[i]);
            } else {
                list.insert_null(i);
            }
        }
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<std::optional<internal::bridge::object_id>> &values) {
        auto list = reinterpret_cast<Obj*>(m_obj)->get_list<std::optional<ObjectId>>(col_key);
        auto size = values.size();
        for (size_t i = 0; i < size; ++i) {
            if (values[i]) {
                list.insert(i, *values[i]);
            } else {
                list.insert_null(i);
            }
        }
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<std::optional<internal::bridge::binary>> &values) {
        auto list = reinterpret_cast<Obj*>(m_obj)->get_list<Binary>(col_key);
        auto size = values.size();
        for (size_t i = 0; i < size; ++i) {
            if (values[i]) {
                list.insert(i, *values[i]);
            } else {
                list.insert_null(i);
           }
        }
    }
    void obj::set_list_values(const col_key &col_key, const std::vector<std::optional<timestamp>> &values) {
        auto list = reinterpret_cast<Obj*>(m_obj)->get_list<Timestamp>(col_key);
        auto size = values.size();
        for (size_t i = 0; i < size; ++i) {
            if (values[i]) {
                list.insert(i, *values[i]);
            } else {
                list.insert_null(i);
            }
        }
    }

    void obj::set_null(const col_key &v) {
        reinterpret_cast<Obj*>(&m_obj)->set_null(v);
    }

    table group::get_table(const std::string &table_key) {
        return static_cast<SharedRealm>(m_realm.get())->read_group().get_table(table_name_for_object_type(table_key));
    }
    table group::get_table(uint32_t table_key) {
        return static_cast<SharedRealm>(m_realm.get())->read_group().get_table(TableKey(table_key));
    }

    obj obj::create_and_set_linked_object(const col_key &v) {
        return reinterpret_cast<Obj*>(&m_obj)->create_and_set_linked_object(v);
    }
    table_view obj::get_backlink_view(table table, col_key col_key) {
        return reinterpret_cast<Obj*>(&m_obj)->get_backlink_view(table, col_key);
    }
}

std::string realm::internal::bridge::table_name_for_object_type(const std::string &v) {
    return ObjectStore::table_name_for_object_type(v);
}
