/* David Leonard, 2002. Public domain. */
/* $Id$ */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "main.h"
#include "tag.h"
#include "flow.h"
#include "abbrev.h"

/*
 * Combine source and dest to make a combined tag unless -c flag given
 * What combining means is that we sometimes have flows which are not
 * directional. So we cnovert a->b and b->a tags to get a<->b. The left and
 * right sides are sorted lexicographically, so that tags are unambiguous.
 */
const char *
tag_combine(src, dst)
	const char *src;
	const char *dst;
{
	static char buf[TAGLEN];
	static char buf2[TAGLEN];
	const char *res;

	if (cflag) {
		snprintf(buf, sizeof buf, "%s -> %s", src, dst);
		res = abbrev_tag(buf);
	} else {
		snprintf(buf, sizeof buf, "%s <-> %s", src, dst);
		res = abbrev_tag(buf);
		if (res == buf) {
			/* The abbreviations could match a reverse combine: */
			snprintf(buf2, sizeof buf2, "%s <-> %s", dst, src);
			res = abbrev_tag(buf2);
			if (res == buf2)
				if (strcmp(src, dst) < 0)
					res = buf;
		}
	}
	return res;
}
