#ifndef NEW_PACKAGE__VISIBILITY_CONTROL_H_
#define NEW_PACKAGE__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define NEW_PACKAGE_EXPORT __attribute__((dllexport))
#define NEW_PACKAGE_IMPORT __attribute__((dllimport))
#else
#define NEW_PACKAGE_EXPORT __declspec(dllexport)
#define NEW_PACKAGE_IMPORT __declspec(dllimport)
#endif
#ifdef NEW_PACKAGE_BUILDING_LIBRARY
#define NEW_PACKAGE_PUBLIC NEW_PACKAGE_EXPORT
#else
#define NEW_PACKAGE_PUBLIC NEW_PACKAGE_IMPORT
#endif
#define NEW_PACKAGE_PUBLIC_TYPE NEW_PACKAGE_PUBLIC
#define NEW_PACKAGE_LOCAL
#else
#define NEW_PACKAGE_EXPORT __attribute__((visibility("default")))
#define NEW_PACKAGE_IMPORT
#if __GNUC__ >= 4
#define NEW_PACKAGE_PUBLIC __attribute__((visibility("default")))
#define NEW_PACKAGE_LOCAL __attribute__((visibility("hidden")))
#else
#define NEW_PACKAGE_PUBLIC
#define NEW_PACKAGE_LOCAL
#endif
#define NEW_PACKAGE_PUBLIC_TYPE
#endif

#endif  // NEW_PACKAGE__VISIBILITY_CONTROL_H_
