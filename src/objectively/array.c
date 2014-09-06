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

#include <assert.h>
#include <stdlib.h>

#include <objectively/array.h>

#define ARRAY_CHUNK_SIZE 64

#pragma mark - Object

static void dealloc(Object *self) {

	free(((Array *) self)->elements);

	super(Object, self, dealloc);
}

#pragma mark - Array

static void addObject(Array *self, const id obj) {

	Object *object = cast(Object, obj);

	assert(object);

	if (self->count == self->capacity) {
		self->elements = realloc(self->elements, self->capacity + ARRAY_CHUNK_SIZE * sizeof(id));
		assert(self->elements);
	}

	self->elements[self->count++] = object;
}

static BOOL containsObject(const Array *self, const id obj) {

	return $(self, indexOfObject, obj) != -1;
}

static int indexOfObject(const Array *self, const id obj) {

	Object *object = cast(Object, obj);

	assert(object);

	for (size_t i = 0; i < self->count; i++) {
		if ($(object, isEqual, (Object * ) self->elements[i])) {
			return (int) i;
		}
	}

	return -1;
}

static void removeObject(Array *self, const id obj) {

	int index = $(self, indexOfObject, obj);

	if (index != -1) {
		for (size_t i = index; i < self->count; i++) {
			self->elements[i] = self->elements[i + 1];
		}

		self->count--;
	}
}

static void removeAllObjects(Array *self) {
	self->count = 0;
}

#pragma mark - Initializer

static id init(id obj, va_list *args) {

	Array *self = (Array *) super(Object, obj, init, args);
	if (self) {
		override(Object, self, dealloc, dealloc);
		override(Object, self, init, init);

		self->addObject = addObject;
		self->containsObject = containsObject;
		self->indexOfObject = indexOfObject;
		self->removeObject = removeObject;
		self->removeAllObjects = removeAllObjects;

		self->capacity = arg(args, size_t, ARRAY_CHUNK_SIZE);
		self->elements = malloc(self->capacity * sizeof(id));
	}

	return self;
}

static Array array;

static Class class = { .name = "Array", .size = sizeof(Array), .superclass = &__Object, .archetype =
		&array, .init = init, };

const Class *__Array = &class;