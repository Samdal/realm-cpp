x.y.z Release notes (yyyy-MM-dd)
=============================================================

### Fixed
* Windows would not compile under Release build configuration as `aligned_storage` parameters were
  incorrectly set.
* The default schema mode was incorrectly set to Automatic and not AdditiveDiscovered when using a Synced Realm.

### Enhancements
* Add support for the Decimal128 data type (`realm::decimal128`).

### Breaking Changes
* None

### Compatibility
* Fileformat: Generates files with format v22.

### Internals
* None

----------------------------------------------

0.2.0 Preview Release notes (2023-06-21)
=============================================================

### Enhancements
This preview introduces a new way to declare your object model, bringing you closer to feeling like you're interfacing with POCO's.
```
namespace realm::experimental {
    struct Address {
        std::string street;
        std::string city;
        std::string country;
    };
    REALM_EMBEDDED_SCHEMA(Address, street, city, country)

    struct Person {
        primary_key<int64_t> _id;
        std::string name;
        int64_t age;
        Address* address = nullptr;
    };
    REALM_SCHEMA(Person, _id, name, age, address)
}
```
This also allows for automatic schema discovery, so opening a realm is now achieved with `realm::experimental::db(std::move(some_realm_config)`.
These new features are available under the `realm::experimental` namespace.
New API usage is as follows:
```
  #include <cpprealm/experimental/sdk.hpp>
  using namespace realm::experimental;
  ...
  auto realm = db(std::move(config));
  
  auto address = Address();
  address.city = "New York";
  auto person = Person();
  person.name = "John";
  person.address = &address;
  
  auto managed_person = realm.write([&person, &realm] {
      return realm.add(std::move(person));
  });
  
  // Note that `person` has been consumed as an rvalue and `managed_person` 
  // should now be used for any data access or observation.
```

### Other API enhancements:

- Object links are now declared with pointer syntax.
- Added support for linking objects:
  ```
    struct Dog;
    struct Person {
        primary_key<int64_t> _id;
        ...
        Dog* dog;
    };
    REALM_SCHEMA(Person, _id, name, age, dog)
    struct Dog {
        ...
        linking_objects<&Person::dog> owners;
    };
  
    // Sample Usage:
    my_realm.objects<experimental::Dog>()[0].owners.size();
  ```
- Primary keys of `int64_t`, `std::string` and `realm::uuid` and their optional counterparts are now supported.

Usage of Realm under this namespace is also compatible with Windows (MSVC 19.30 and greater).

### Breaking Changes
The following functions now return `std::future` instead of `std::promise`
  - `realm::App::login`
  - `realm::App::register_user`
  - `realm::user::logout`,
  - `realm::sync_subscription_set::update`
  - `realm::sync_session::wait_for_upload_completion`
  - `realm::sync_session::wait_for_download_completion`

### Compatibility
* Fileformat: Generates files with format v22.

### Internals
* Upgraded to Core v13.15.1

----------------------------------------------

0.1.1 Release notes (2023-04-28)
=============================================================

### Fixed
* Address memory leaks reported by instruments caused by some classes not implementing rule of 5 when using
  `std::aligned_storage` ([#69](https://github.com/realm/realm-cpp/pull/69)), since v0.1.0).
* Dereferencing a property on an object link or embedded object would not return any value ([#71](https://github.com/realm/realm-cpp/pull/71)), since v0.1.0).

### Compatibility
* Fileformat: Generates files with format v22.

### Internals
* Upgraded to Core v13.9.2

----------------------------------------------