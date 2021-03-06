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

#include <Objectively/String.h>

/**
 * @file
 *
 * @brief Mutable UTF-8 strings.
 */

typedef struct MutableStringInterface MutableStringInterface;

/**
 * @brief Mutable UTF-8 strings.
 *
 * @extends String
 *
 * @ingroup ByteStreams
 */
struct MutableString {

	/**
	 * @brief The parent.
	 *
	 * @private
	 */
	String string;

	/**
	 * @brief The typed interface.
	 *
	 * @private
	 */
	MutableStringInterface *interface;

	/**
	 * @brief The capacity of the String, in bytes.
	 *
	 * @remarks The capacity is always `>= self->string.length`.
	 *
	 * @private
	 */
	size_t capacity;
};

/**
 * @brief The MutableString interface.
 */
struct MutableStringInterface {

	/**
	 * @brief The parent interface.
	 */
	StringInterface stringInterface;

	/**
	 * @fn void MutableString::appendCharacters(MutableString *self, const char *chars)
	 *
	 * @brief Appends the specified UTF-8 encoded C string.
	 *
	 * @param chars A UTF-encoded C string.
	 *
	 * @memberof MutableString
	 */
	void (*appendCharacters)(MutableString *self, const char *chars);

	/**
	 * @fn void MutableString::appendFormat(MutableString *self, const char *fmt, ...)
	 *
	 * @brief Appends the specified formatted string.
	 *
	 * @param fmt The format string.
	 *
	 * @memberof MutableString
	 */
	void (*appendFormat)(MutableString *self, const char *fmt, ...);

	/**
	 * @fn void MutableString::appendString(MutableString *self, const String *string)
	 *
	 * @brief Appends the specified String to this MutableString.
	 *
	 * @param other The String to append.
	 *
	 * @memberof MutableString
	 */
	void (*appendString)(MutableString *self, const String *string);
	
	/**
	 * @fn void MutableString::appendVaList(MutableString *self, const char *fmt, va_list args)
	 *
	 * @brief Appends the specified format string.
	 *
	 * @param fmt The format string.
	 * @param args The format arguments.
	 *
	 * @memberof MutableString
	 */
	void (*appendVaList)(MutableString *self, const char *fmt, va_list args);

	/**
	 * @fn void MutableString::deleteCharactersInRange(MutableString *self, const Range range)
	 *
	 * @brief Deletes the characters within `range` from this MutableString.
	 *
	 * @param range The Range of characters to delete.
	 *
	 * @memberof MutableString
	 */
	void (*deleteCharactersInRange)(MutableString *self, const Range range);

	/**
	 * @fn MutableString *MutableString::init(MutableString *self)
	 *
	 * @brief Initializes this MutableString.
	 *
	 * @return The initialized MutableString, or `NULL` on error.
	 *
	 * @memberof MutableString
	 */
	MutableString *(*init)(MutableString *self);

	/**
	 * @fn MutableString *MutableString::initWithCapacity(MutableString *self, size_t capacity)
	 *
	 * @brief Initializes this MutableString with the given `capacity`.
	 *
	 * @param capacity The capacity, in bytes.
	 *
	 * @return The initialized MutableString, or `NULL` on error.
	 *
	 * @memberof MutableString
	 */
	MutableString *(*initWithCapacity)(MutableString *self, size_t capacity);

	/**
	 * @fn MutableString *MutableString::initWithString(MutableString *self, const String *string)
	 *
	 * @brief Initializes this MutableString with the contents of `string`.
	 *
	 * @param string A String.
	 *
	 * @return The initialized MutableString, or `NULL` on error.
	 *
	 * @memberof MutableString
	 */
	MutableString *(*initWithString)(MutableString *self, const String *string);

	/**
	 * @fn void MutableString::insertCharactersAtIndex(MutableString *self, const char *chars, int index)
	 *
	 * @brief Inserts the specified String at the given index.
	 *
	 * @param chars The null-terminated UTF-8 encoded C string to insert.
	 * @param index The index.
	 *
	 * @memberof MutableString
	 */
	void (*insertCharactersAtIndex)(MutableString *self, const char *chars, int index);
	
	/**
	 * @fn void MutableString::insertStringAtIndex(MutableString *self, const String *string, int index)
	 *
	 * @brief Inserts the specified String at the given index.
	 *
	 * @param string The String to insert.
	 * @param index The index.
	 *
	 * @memberof MutableString
	 */
	void (*insertStringAtIndex)(MutableString *self, const String *string, int index);
	
	/**
	 * @fn void MutableString::replaceCharactersInRange(MutableString *self, const Range range, const char *chars)
	 *
	 * @brief Replaces the characters in `range` with the give characters.
	 *
	 * @param range The Range of characters to replace.
	 * @param chars The null-terminated UTF-8 encoded C string to substitute.
	 *
	 * @memberof MutableString
	 */
	void (*replaceCharactersInRange)(MutableString *self, const Range range, const char *chars);
	
	/**
	 * @fn void MutableString::replaceStringInRange(MutableString *self, const Range range, const String *string)
	 *
	 * @brief Replaces the characters in `range` with the contents of `string`.
	 *
	 * @param range The Range of characters to replace.
	 * @param string The String to substitute.
	 *
	 * @memberof MutableString
	 */
	void (*replaceStringInRange)(MutableString *self, const Range range, const String *string);

	/**
	 * @static
	 *
	 * @fn MutableString *MutableString::string(void)
	 *
	 * @brief Returns a new MutableString.
	 *
	 * @return The new MutableString, or `NULL` on error.
	 *
	 * @memberof MutableString
	 */
	MutableString *(*string)(void);

	/**
	 * @static
	 *
	 * @fn MutableString *MutableString::stringWithCapacity(size_t capacity)
	 *
	 * @brief Returns a new MutableString with the given `capacity`.
	 *
	 * @param capacity The desired capacity, in bytes.
	 *
	 * @return The new MutableString, or `NULL` on error.
	 *
	 * @memberof MutableString
	 */
	MutableString *(*stringWithCapacity)(size_t capacity);
};

/**
 * @brief The MutableString Class.
 */
extern Class _MutableString;

/**
 * @brief A convenience function for instantiating MutableStrings.
 *
 * @param fmt The format string.
 *
 * @return A new MutableString, or `NULL` on error.
 *
 * @relates String
 */
MutableString *mstr(const char *fmt, ...);
