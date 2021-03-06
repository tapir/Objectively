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

#include <sys/time.h>
#include <time.h>

#include <Objectively/Object.h>

/**
 * @file
 *
 * @brief Microsecond-precision immutable dates.
 */

/**
 * @defgroup Date Date & Time
 *
 * @brief Date and time manipulation.
 */

/**
 * @brief Microseconds per second.
 */
#define MSEC_PER_SEC 1000000

/**
 * @brief Seconds per day.
 */
#define SEC_PER_DAY (60 * 60 * 24)

/**
 * @brief Time (seconds and microseconds).
 */
typedef struct timeval Time;

typedef struct Date Date;
typedef struct DateInterface DateInterface;

/**
 * @brief Microsecond-precision immutable dates.
 *
 * @extends Object
 *
 * @ingroup Date
 */
struct Date {

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
	DateInterface *interface;

	/**
	 * @brief The time.
	 */
	Time time;
};

/**
 * @brief The Date interface.
 */
struct DateInterface {

	/**
	 * @brief The parent interface.
	 */
	ObjectInterface objectInterface;

	/**
	 * @fn Order Date::compareTo(const Date *self, const Date *other)
	 *
	 * @brief Compares this Date to another.
	 *
	 * @param other The Date to compare to.
	 *
	 * @return The ordering of this Date compared to other.
	 *
	 * @memberof Date
	 */
	Order (*compareTo)(const Date *self, const Date *other);
	
	/**
	 * @static
	 *
	 * @fn Date *Date::date(void)
	 *
	 * @brief Returns a new Date with the current Time.
	 *
	 * @return The new Date, or `NULL` on error.
	 *
	 * @memberof Date
	 */
	Date *(*date)(void);
	
	/**
	 * @static
	 *
	 * @fn Date *Date::dateWithTimeSinceNow(const Time interval)
	 *
	 * @brief Returns a new Date with the given Time since now.
	 *
	 * @return The new Date, or `NULL` on error.
	 *
	 * @memberof Date
	 */
	Date *(*dateWithTimeSinceNow)(const Time *interval);


	/**
	 * @fn Date *Date::init(Date *self)
	 *
	 * Initializes a Date with the current time.
	 *
	 * @return The initialized Date, or `NULL` on error.
	 *
	 * @memberof Date
	 */
	Date *(*init)(Date *self);

	/**
	 * @fn Date *Date::initWithTime(Date *self, const Time *time)
	 *
	 * Initializes a Date with the specified time.
	 *
	 * @param time The desired Time.
	 *
	 * @return The initialized Date, or `NULL` on error.
	 *
	 * @memberof Date
	 */
	Date *(*initWithTime)(Date *self, const Time *time);
};

/**
 * @brief The Date Class.
 */
extern Class _Date;
