/*
 * Objectively: Ultra-lightweight object oriented framework for c99.
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

#ifndef _objectively_macros_h_
#define _objectively_macros_h_

#include <objectively/class.h>

/*
 * @brief Call a method.
 */
#define $(instance, method, ...) \
	instance->method(instance, ## __VA_ARGS__)

/*
 * @brief Take a constructor parameter.
 */
#define arg(args, type, def) \
	(args ? va_arg(*args, type) : def)

/*
 * @brief Override a supertype method in your type.
 */
#define override(type, instance, method, implementation) \
	((struct type *) instance)->method = implementation;

/*
 * @brief Invoke a supertype method on an instance of your type.
 */
#define super(type, instance, method, ...) \
	((struct type *) archetype(type))->method((struct type *) instance, ## __VA_ARGS__)

#endif