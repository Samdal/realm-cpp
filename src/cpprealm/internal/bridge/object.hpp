#ifndef CPP_REALM_BRIDGE_OBJECT_HPP
#define CPP_REALM_BRIDGE_OBJECT_HPP

#include <any>
#include <functional>
#include <memory>
#include <unordered_map>

namespace realm {
    class Object;
    class IndexSet;
    class CollectionChangeCallback;
    struct CollectionChangeSet;
    struct NotificationToken;
}
namespace realm::internal::bridge {
    struct realm;
    struct obj;
    struct obj_link;
    struct object_schema;
    struct list;
    struct col_key;
    struct dictionary;

    struct notification_token {
        notification_token();
        notification_token(const notification_token &other) = delete;
        notification_token &operator=(const notification_token &other) = delete;
        notification_token(notification_token &&other);
        notification_token &operator=(notification_token &&other);
        notification_token(NotificationToken&&);
        operator NotificationToken() const;
        void unregister();
    private:
#ifdef __i386__
        std::aligned_storage<16, 4>::type m_token[1];
#elif __x86_64__
        std::aligned_storage<24, 8>::type m_token[1];
#elif __arm__
        std::aligned_storage<16, 8>::type m_token[1];
#elif __aarch64__
        std::aligned_storage<24, 8>::type m_token[1];
#elif _WIN32
        std::aligned_storage<24, 8>::type m_token[1];
#endif
    };

    struct index_set {
        index_set(); //NOLINT(google-explicit-constructor)
        index_set(const index_set& other) ;
        index_set& operator=(const index_set& other);
        index_set(index_set&& other);
        index_set& operator=(index_set&& other);
        ~index_set();
        index_set(const IndexSet&); //NOLINT(google-explicit-constructor)
        [[nodiscard]] bool empty() const;
        struct index_iterable_adaptor;
        // An iterator over the individual indices in the set rather than the ranges
        class index_iterator {
        public:
            index_iterator() = default;
            index_iterator(const index_iterator& other) ;
            index_iterator& operator=(const index_iterator& other);
            index_iterator(index_iterator&& other);
            index_iterator& operator=(index_iterator&& other);
            ~index_iterator();
            size_t operator*() const noexcept;
            bool operator==(index_iterator const& it) const noexcept;
            bool operator!=(index_iterator const& it) const noexcept;

            index_iterator& operator++() noexcept;

            index_iterator operator++(int) noexcept;

        private:
            friend struct index_iterable_adaptor;
#ifdef __i386__
            std::aligned_storage<16, 4>::type m_iterator[1];
#elif __x86_64__
            std::aligned_storage<32, 8>::type m_iterator[1];
#elif __arm__
            std::aligned_storage<16, 4>::type m_iterator[1];
#elif __aarch64__
            std::aligned_storage<32, 8>::type m_iterator[1];
#elif _WIN32
            #if _DEBUG
            std::aligned_storage<64, 8>::type m_iterator[1];
            #else
            std::aligned_storage<32, 8>::type m_iterator[1];
            #endif
#endif
        };

        struct index_iterable_adaptor {
            index_iterable_adaptor() = default;
            index_iterable_adaptor(const index_iterable_adaptor& other) ;
            index_iterable_adaptor& operator=(const index_iterable_adaptor& other);
            index_iterable_adaptor(index_iterable_adaptor&& other);
            index_iterable_adaptor& operator=(index_iterable_adaptor&& other);
            ~index_iterable_adaptor();
            using const_iterator = index_iterator;

            const_iterator begin() const noexcept;
            const_iterator end() const noexcept;
        private:
            friend struct index_set;
#ifdef __i386__
            std::aligned_storage<4, 4>::type m_index_iterable_adaptor[1];
#elif __x86_64__
            std::aligned_storage<8, 8>::type m_index_iterable_adaptor[1];
#elif __arm__
            std::aligned_storage<4, 4>::type m_index_iterable_adaptor[1];
#elif __aarch64__
            std::aligned_storage<8, 8>::type m_index_iterable_adaptor[1];
#elif _WIN32
            std::aligned_storage<8, 8>::type m_index_iterable_adaptor[1];
#endif
        };
        index_iterable_adaptor as_indexes() const;
    private:
#ifdef __i386__
        std::aligned_storage<24, 4>::type m_idx_set[1];
#elif __x86_64__
        std::aligned_storage<24, 8>::type m_idx_set[1];
#elif __arm__
        std::aligned_storage<24, 4>::type m_idx_set[1];
#elif __aarch64__
        std::aligned_storage<24, 8>::type m_idx_set[1];
#elif _WIN32
        #if _DEBUG
        std::aligned_storage<32, 8>::type m_idx_set[1];
        #else
        std::aligned_storage<24, 8>::type m_idx_set[1];
        #endif
#endif
    };
    struct collection_change_set {
        collection_change_set(); //NOLINT(google-explicit-constructor)
        collection_change_set(const collection_change_set& other) ;
        collection_change_set& operator=(const collection_change_set& other);
        collection_change_set(collection_change_set&& other);
        collection_change_set& operator=(collection_change_set&& other);
        ~collection_change_set();
        collection_change_set(const CollectionChangeSet&);
        operator CollectionChangeSet() const;
        [[nodiscard]] index_set deletions() const;
        [[nodiscard]] index_set modifications() const;
        [[nodiscard]] index_set insertions() const;
        [[nodiscard]] std::unordered_map<int64_t, index_set> columns() const;
        [[nodiscard]] bool empty() const;
        [[nodiscard]] bool collection_root_was_deleted() const;
    private:
#ifdef __i386__
        std::aligned_storage<84, 4>::type m_change_set[1];
#elif __x86_64__
    #if defined(__clang__)
        std::aligned_storage<168, 8>::type m_change_set[1];
    #elif defined(__GNUC__) || defined(__GNUG__)
        std::aligned_storage<184, 8>::type m_change_set[1];
    #endif
#elif __arm__
        std::aligned_storage<84, 4>::type m_change_set[1];
#elif __aarch64__
#if defined(__clang__)
        std::aligned_storage<168, 8>::type m_change_set[1];
#elif defined(__GNUC__) || defined(__GNUG__)
        std::aligned_storage<184, 8>::type m_change_set[1];
#endif
#elif _WIN32
        #if _DEBUG
        std::aligned_storage<248, 8>::type m_change_set[1];
        #else
        std::aligned_storage<192, 8>::type m_change_set[1];
        #endif
#endif
    };
    struct collection_change_callback {
        virtual void before(collection_change_set const& c) = 0;
        virtual void after(collection_change_set const& c) = 0;
    };

    struct object {
        object(); //NOLINT(google-explicit-constructor)
        object(const object& other) ;
        object& operator=(const object& other);
        object(object&& other);
        object& operator=(object&& other);
        ~object();
        object(const Object&); //NOLINT(google-explicit-constructor)
        object(const realm &realm, const obj &obj); //NOLINT(google-explicit-constructor)
        object(const realm &realm, const obj_link& link);

        operator Object() const; //NOLINT(google-explicit-constructor)

        [[nodiscard]] obj get_obj() const;

        [[nodiscard]] realm get_realm() const;

        [[nodiscard]] bool is_valid() const;

        notification_token add_notification_callback(std::shared_ptr<collection_change_callback>&& cb);

        [[nodiscard]] object_schema get_object_schema() const;

        [[nodiscard]] list get_list(const col_key&) const;
        [[nodiscard]] dictionary get_dictionary(const col_key&) const;
    private:
#ifdef __i386__
        std::aligned_storage<64, 4>::type m_object[1];
#elif __x86_64__
        std::aligned_storage<104, 8>::type m_object[1];
#elif __arm__
        std::aligned_storage<80, 8>::type m_object[1];
#elif __aarch64__
        std::aligned_storage<104, 8>::type m_object[1];
#elif _WIN32
        std::aligned_storage<104, 8>::type m_object[1];
#endif
    };
}

#endif //CPP_REALM_BRIDGE_OBJECT_HPP
