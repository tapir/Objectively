/*
 * Objectively: Ultra-lightweight object oriented framework for GNU C.
 * Copyright (C) 2014 Jay Dolan <jay@jaydolan.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#pragma once

#include <ctype.h>
#include <wctype.h>
#include <stdarg.h>

#include <Objectively/Array.h>
#include <Objectively/Data.h>
#include <Objectively/Locale.h>

/**
 * @file
 *
 * @brief Immutable UTF-8 strings.
 */

/**
 * @brief The Unicode type.
 */
typedef wchar_t Unicode;

/**
 * @brief Character encodings for Strings.
 */
typedef enum {
	STRING_ENCODING_ASCII = 1,
	STRING_ENCODING_LATIN1,
	STRING_ENCODING_LATIN2,
	STRING_ENCODING_MACROMAN,
	STRING_ENCODING_UTF16,
	STRING_ENCODING_UTF32,
	STRING_ENCODING_UTF8,
	STRING_ENCODING_WCHAR,
} StringEncoding;

typedef struct StringInterface StringInterface;

/**
 * @brief Immutable UTF-8 strings.
 *
 * @remarks Because Strings are encoded using UTF-8, they must not be treated as
 * ASCII C strings. That is, a single Unicode code point will often span
 * multiple `char`s. Be mindful of this when executing Range operations.
 *
 * @extends Object
 *
 * @ingroup ByteStreams
 */
struct String {

	/**
	 * @brief The parent.
	 *
	 * @private
	 */
	Object object;

	/**
	 * @brief The typed interface.
	 *
	 * @private
	 */
	StringInterface *interface;

	/**
	 * @brief The backing null-terminated UTF-8 encoded character array.
	 */
	char *chars;

	/**
	 * @brief The length of the String in bytes.
	 */
	size_t length;
};

typedef struct MutableString MutableString;

/**
 * @brief The String interface.
 */
struct StringInterface {

	/**
	 * @brief The parent interface.
	 */
	ObjectInterface objectInterface;

	/**
	 * @fn Order String::compareTo(const String *self, const String *other, const Range range)
	 *
	 * @brief Compares this String lexicographically to another.
	 *
	 * @param other The String to compare to.
	 * @param range The character range to compare.
	 *
	 * @return The ordering of this String compared to `other`.
	 *
	 * @memberof String
	 */
	Order (*compareTo)(const String *self, const String *other, const Range range);

	/**
	 * @fn Array *String::componentsSeparatedByCharacters(const String *self, const char *chars)
	 *
	 * @brief Returns the components of this String that were separated by `chars`.
	 *
	 * @param chars The separating characters.
	 *
	 * @return An Array of substrings that were separated by `chars`.
	 *
	 * @memberof String
	 */
	Array *(*componentsSeparatedByCharacters)(const String *self, const char *chars);

	/**
	 * @fn Array *String::componentsSeparatedByString(const String *self, const String *string)
	 *
	 * @brief Returns the components of this String that were separated by `string`.
	 *
	 * @param string The separating String.
	 *
	 * @return An Array of substrings that were separated by `string`.
	 *
	 * @memberof String
	 */
	Array *(*componentsSeparatedByString)(const String *self, const String *string);

	/**
	 * @fn Data *String::getData(const String *self, StringEncoding encoding)
	 *
	 * @brief Returns a Data with this String's contents in the given encoding.
	 *
	 * @param encoding The desired StringEncoding.
	 *
	 * @return A Data with this String's contents in the given encoding.
	 *
	 * @memberof String
	 */
	Data *(*getData)(const String *self, StringEncoding encoding);

	/**
	 * @fn _Bool String::hasPrefix(const String *self, const String *prefix)
	 *
	 * @brief Checks this String for the given prefix.
	 *
	 * @param prefix The Prefix to check.
	 *
	 * @return true if this String starts with prefix, false otherwise.
	 *
	 * @memberof String
	 */
	_Bool (*hasPrefix)(const String *self, const String *prefix);

	/**
	 * @fn _Bool String::hasSuffix(const String *self, const String *suffix)
	 *
	 * @brief Checks this String for the given suffix.
	 *
	 * @param suffix The suffix to check.
	 *
	 * @return true if this String ends with suffix, false otherwise.
	 *
	 * @memberof String
	 */
	_Bool (*hasSuffix)(const String *self, const String *suffix);

	/**
	 * @fn String *String::initWithBytes(String *self, const uint8_t *bytes, size_t length, StringEncoding encoding)
	 *
	 * @brief Initializes this String by decoding `length` of `bytes`.
	 *
	 * @param bytes The bytes.
	 * @param length The length of `bytes` to decode.
	 * @param encoding The character encoding.
	 *
	 * @return The initialized String, or `NULL` on error.
	 *
	 * @memberof String
	 */
	String *(*initWithBytes)(String *self, const uint8_t *bytes, size_t length, StringEncoding encoding);

	/**
	 * @fn String *String::initWithCharacters(String *self, const char *chars)
	 *
	 * @brief Initializes this String by copying `chars`.
	 *
	 * @param chars The null-terminated, UTF-8 encoded C string.
	 *
	 * @return The initialized String, or `NULL` on error.
	 *
	 * @memberof String
	 */
	String *(*initWithCharacters)(String *self, const char *chars);

	/**
	 * @fn String *String::initWithContentsOfFile(String *self, const char *path, StringEncoding encoding)
	 *
	 * @brief Initializes this String with the contents of the FILE at `path`.
	 *
	 * @param path The path of the file to load.
	 * @param encoding The character encoding.
	 *
	 * @return The initialized String, or `NULL` on error.
	 *
	 * @memberof String
	 */
	String *(*initWithContentsOfFile)(String *self, const char *path, StringEncoding encoding);

	/**
	 * @fn String *String::initWithData(String *self, const Data *data, StringEncoding encoding)
	 *
	 * @brief Initializes this String with the given Data.
	 *
	 * @param data The Data object.
	 * @param encoding The character encoding.
	 *
	 * @return The initialized String, or `NULL` on error.
	 *
	 * @memberof String
	 */
	String *(*initWithData)(String *self, const Data *data, StringEncoding encoding);

	/**
	 * @fn String *String::initWithFormat(String *self, const char *fmt, ...)
	 *
	 * @brief Initializes this String with the specified format string.
	 *
	 * @param fmt The formatted string.
	 *
	 * @return The initialized String, or `NULL` on error.
	 *
	 * @memberof String
	 */
	String *(*initWithFormat)(String *self, const char *fmt, ...);

	/**
	 * @fn String *String::initWithMemory(String *self, const ident mem, size_t length)
	 *
	 * @brief Initializes this String with the specified buffer.
	 *
	 * @param mem The dynamically allocated null-terminated, UTF-8 encoded buffer.
	 * @param length The length of `mem` in printable characters.
	 *
	 * @return The initialized String, or `NULL` on error.
	 *
	 * @memberof String
	 */
	String *(*initWithMemory)(String *self, const ident mem, size_t length);

	/**
	 * @fn String *String::initWithVaList(String *string, const char *fmt, va_list args)
	 *
	 * @brief Initializes this String with the specified arguments list.
	 *
	 * @param fmt The format string.
	 * @param args The format arguments.
	 *
	 * @return The initialized String, or `NULL` on error.
	 *
	 * @memberof String
	 *
	 * @see vasprintf(3)
	 */
	String *(*initWithVaList)(String *string, const char *fmt, va_list args);

	/**
	 * @fn String *String::lowercaseString(const String *self)
	 *
	 * @return A lowercase representation of this String in the default Locale.
	 *
	 * @memberof String
	 */
	String *(*lowercaseString)(const String *self);

	/**
	 * @fn String *String::lowercaseStringWithLocale(const String *self, const Locale *locale)
	 *
	 * @param locale The desired Locale.
	 *
	 * @return A lowercase representation of this String in the given Locale.
	 *
	 * @memberof String
	 */
	String *(*lowercaseStringWithLocale)(const String *self, const Locale *locale);

	/**
	 * @fn MutableString *String::mutableCopy(const String *self)
	 *
	 * @return A MutableString with the contents of this String.
	 *
	 * @memberof String
	 */
	MutableString *(*mutableCopy)(const String *self);

	/**
	 * @fn Range String::rangeOfCharacters(const String *self, const char *chars, const Range range)
	 *
	 * @brief Finds and returns the first occurrence of `chars` in this String.
	 *
	 * @param chars The characters to search for.
	 * @param range The range in which to search.
	 *
	 * @return A Range specifying the first occurrence of `chars` in this String.
	 *
	 * @memberof String
	 */
	Range (*rangeOfCharacters)(const String *self, const char *chars, const Range range);

	/**
	 * @fn Range String::rangeOfString(const String *self, const String *string, const Range range)
	 *
	 * @brief Finds and returns the first occurrence of `string` in this String.
	 *
	 * @param string The String to search for.
	 * @param range The range in which to search.
	 *
	 * @return A Range specifying the first occurrence of `string` in this String.
	 *
	 * @memberof String
	 */
	Range (*rangeOfString)(const String *self, const String *string, const Range range);

	/**
	 * @static
	 *
	 * @fn String *String::stringWithBytes(const uint8_t *bytes, size_t length, StringEncoding encoding)
	 *
	 * @brief Returns a new String by decoding `length` of `bytes` to UTF-8.
	 *
	 * @param bytes The bytes.
	 * @param length The length of `bytes` to copy.
	 * @param encoding The character encoding.
	 *
	 * @return The new String, or `NULL` on error.
	 *
	 * @memberof String
	 */
	String *(*stringWithBytes)(const uint8_t *bytes, size_t length, StringEncoding encoding);

	/**
	 * @static
	 *
	 * @fn String *String::stringWithCharacters(const char *chars)
	 *
	 * @brief Returns a new String by copying `chars`.
	 *
	 * @param chars The null-terminated UTF-8 encoded C string.
	 *
	 * @return The new String, or `NULL` on error.
	 *
	 * @memberof String
	 */
	String *(*stringWithCharacters)(const char *chars);

	/**
	 * @static
	 *
	 * @fn String *String::stringWithContentsOfFile(const char *path, StringEncoding encoding)
	 *
	 * @brief Returns a new String with the contents of the FILE at `path`.
	 *
	 * @param path A path name.
	 * @param encoding The character encoding.
	 *
	 * @return The new String, or `NULL` on error.
	 *
	 * @memberof String
	 */
	String *(*stringWithContentsOfFile)(const char *path, StringEncoding encoding);

	/**
	 * @static
	 *
	 * @fn String *String::stringWithData(const Data *data, StringEncoding encoding)
	 *
	 * @brief Returns a new String with the the given Data.
	 *
	 * @param data A Data.
	 * @param encoding The character encoding.
	 *
	 * @return The new String, or `NULL` on error.
	 *
	 * @memberof String
	 */
	String *(*stringWithData)(const Data *data, StringEncoding encoding);

	/**
	 * @static
	 *
	 * @fn String *String::stringWithFormat(const char *fmt)
	 *
	 * @brief Returns a new String with the given format string.
	 *
	 * @param fmt The format string.
	 *
	 * @return The new String, or `NULL` on error.
	 *
	 * @memberof String
	 */
	String *(*stringWithFormat)(const char *fmt, ...);

	/**
	 * @static
	 *
	 * @fn String *String::stringWithMemory(const ident mem, size_t length)
	 *
	 * @brief Returns a new String with the given buffer.
	 *
	 * @param mem A dynamically allocated, null-terminated UTF-8 encoded buffer.
	 * @param length The length of `mem` in bytes.
	 *
	 * @return The new String, or `NULL` on error.
	 *
	 * @memberof String
	 */
	String *(*stringWithMemory)(const ident mem, size_t length);

	/**
	 * @fn String *String::substring(const String *string, const Range range)
	 *
	 * @brief Creates a new String from a subset of this one.
	 *
	 * @param range The character range.
	 *
	 * @return The new String.
	 *
	 * @memberof String
	 */
	String *(*substring)(const String *self, const Range range);

	/**
	 * @fn String *String::uppercaseString(const String *self)
	 *
	 * @return An uppercase representation of this String in the default Locale.
	 *
	 * @memberof String
	 */
	String *(*uppercaseString)(const String *self);

	/**
	 * @fn String *String::uppercaseStringWithLocale(const String *self, const Locale *locale)
	 *
	 * @param locale The desired Locale.
	 *
	 * @return A uppercase representation of this String in the given Locale.
	 *
	 * @memberof String
	 */
	String *(*uppercaseStringWithLocale)(const String *self, const Locale *locale);

	/**
	 * @fn _Bool String::writeToFile(const String *self, const char *path, StringEncoding encoding)
	 *
	 * @brief Writes this String to `path`.
	 *
	 * @param path The path of the file to write.
	 * @param encoding The character encoding.
	 *
	 * @return `true` on success, `false` on error.
	 *
	 * @memberof String
	 */
	_Bool (*writeToFile)(const String *self, const char *path, StringEncoding encoding);
};

/**
 * @brief The String Class.
 */
extern Class _String;

/**
 * @param encoding A StringEncoding.
 *
 * @return The canonical name for the given encoding.
 * 
 * @relates String
 */
const char *NameForStringEncoding(StringEncoding encoding);

/**
 * @param name The case-insensitive name of the encoding.
 *
 * @return The StringEncoding for the given `name`.
 *
 * @relates String
 */
StringEncoding StringEncodingForName(const char *name);

/**
 * @brief A convenience function for instantiating Strings.
 *
 * @param fmt The format string.
 *
 * @return A new String, or `NULL` on error.
 *
 * @relates String
 */
String *str(const char *fmt, ...);
