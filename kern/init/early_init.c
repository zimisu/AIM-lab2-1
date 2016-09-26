/* Copyright (C) 2016 David Gao <davidgao1001@gmail.com>
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
#include <aim/debug.h>
#include <aim/early_kmmap.h>
#include <aim/mmu.h>
#include <aim/init.h>
#include <aim/panic.h>

void early_mm_init(void)
{
	struct early_mapping *mapping = early_mapping_next(NULL);
	for (; mapping != NULL; mapping = early_mapping_next(mapping)) {
		kpdebug("early_mapping(P=0x%08x, V=0x%08x, S=0x%08x, %d)\n",
			(size_t)mapping->paddr, mapping->vaddr, 
			mapping->size, mapping->type);
	}

	/* initialize and apply page index */
	extern pgindex_t boot_page_index;
	page_index_init((pgindex_t *)(size_t)premap_addr((void *)&boot_page_index));
	mmu_init((pgindex_t *)(size_t)kva2pa(postmap_addr((void *)&boot_page_index)));
	mmu_handlers_apply();
}

__noreturn
void master_early_init(void)
{
	early_mapping_clear();
	mmu_handlers_clear();
	arch_early_init();
	early_mm_init();

	panic("master_early_init is returning");
}

