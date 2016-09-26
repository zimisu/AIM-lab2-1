/* Copyright (C) 2016 Gan Quan <coin2028@hotmail.com>
 * Copyright (C) 2016 David Gao <davidgao1001@gmail.com>
 *
 * This file is part of AIM.
 *
 * AIM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * AIM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <sys/types.h>
#include <aim/device.h>
#include <io-port.h>
#include <asm.h>

static void __jump_handler(void)
{
	__portio_bus_init(&early_portio_bus);
}

void portio_bus_init(struct bus_device *portio)
{
	__portio_bus_init(portio);

	if (jump_handlers_add((generic_fp)postmap_addr(__jump_handler)) != 0)
		for (;;) ;	/* panic */
}

struct bus_device early_portio_bus = {
	/* FIXME ? */
	.addr_width = 32,
	.class = DEVCLASS_BUS,
};

#ifndef RAW

#endif /* !RAW */

