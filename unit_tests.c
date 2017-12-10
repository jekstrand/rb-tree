/*
 * Copyright © 2017 Jason Ekstrand
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "rb_tree.h"

#include <assert.h>

unsigned test_numbers[] = {
    26, 12, 35, 15, 48, 11, 39, 23, 40, 18,
    39, 15, 40, 11, 42, 2, 5, 2, 28, 8,
    10, 22, 23, 38, 47, 12, 30, 22, 26, 39,
    9, 42, 32, 18, 36, 8, 32, 29, 9, 3,
    32, 49, 23, 11, 43, 41, 22, 42, 6, 35,
    38, 48, 5, 35, 39, 44, 22, 16, 16, 32,
    31, 50, 48, 5, 50, 8, 2, 32, 27, 34,
    42, 48, 22, 47, 10, 48, 39, 36, 28, 40,
    32, 33, 21, 17, 14, 38, 27, 6, 25, 18,
    32, 38, 19, 22, 20, 47, 50, 41, 29, 50,
};

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))

struct rb_test_node {
    unsigned key;
    struct rb_node node;
};

bool
rb_test_node_cmp(const struct rb_node *a, const struct rb_node *b)
{
    struct rb_test_node *ta = rb_node_data(struct rb_test_node, a, node);
    struct rb_test_node *tb = rb_node_data(struct rb_test_node, b, node);

    return ta->key < tb->key;
}

int main()
{
    struct rb_test_node nodes[ARRAY_SIZE(test_numbers)];
    struct rb_tree tree;

    rb_tree_init(&tree);

    for (unsigned i = 0; i < ARRAY_SIZE(test_numbers); i++) {
        nodes[i].key = test_numbers[i];
        rb_tree_insert(&tree, &nodes[i].node, rb_test_node_cmp);
        rb_tree_validate(&tree);
    }
}