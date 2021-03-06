#!/bin/ksh -p
#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#

#
# Copyright (c) 2013 by Delphix. All rights reserved.
#
. $STF_SUITE/include/libtest.shlib
. $STF_SUITE/tests/functional/userquota/userquota_common.kshlib

#
#
# DESCRIPTION:
#       Check whether chattr works as expected
#
#
# STRATEGY:
#       1. Create 3 files
#       2. Use chattr to make them writable, immutable and appendonly
#       3. Try to write and append to each file
#

set -A files writable immutable append

function cleanup
{
	for i in ${files[*]}; do
		log_must chattr -ia $TESTDIR/$i
		log_must rm -f $TESTDIR/$i
	done
}

log_onexit cleanup

log_assert "Check whether chattr works as expected"

log_must touch $TESTDIR/writable
log_must touch $TESTDIR/immutable
log_must touch $TESTDIR/append

log_must chattr -i $TESTDIR/writable
log_must chattr +i $TESTDIR/immutable
log_must chattr +a $TESTDIR/append

log_must echo test > $TESTDIR/writable
log_must echo test >> $TESTDIR/writable
log_mustnot echo test > $TESTDIR/immutable
log_mustnot echo test >> $TESTDIR/immutable
log_mustnot echo test > $TESTDIR/append
log_must echo test >> $TESTDIR/append

log_pass "chattr works as expected"
