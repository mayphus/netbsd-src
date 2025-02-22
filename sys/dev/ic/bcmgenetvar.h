/* $NetBSD: bcmgenetvar.h,v 1.6 2024/10/04 10:41:58 skrll Exp $ */

/*-
 * Copyright (c) 2020 Jared McNeill <jmcneill@invisible.ca>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Broadcom GENETv5
 */

#ifndef _BCMGENETVAR_H
#define _BCMGENETVAR_H

#include <dev/ic/bcmgenetreg.h>

enum genet_phy_mode {
	GENET_PHY_MODE_RGMII,
	GENET_PHY_MODE_RGMII_ID,
	GENET_PHY_MODE_RGMII_TXID,
	GENET_PHY_MODE_RGMII_RXID,
};

struct genet_bufmap {
	bus_dmamap_t		map;
	struct mbuf		*mbuf;
};

struct genet_ring {
	bus_dma_tag_t		buf_tag;
	struct genet_bufmap	buf_map[GENET_DMA_DESC_COUNT];
	u_int			next, queued;
	uint32_t		cidx, pidx;
};

struct genet_softc {
	device_t		sc_dev;
	bus_space_tag_t		sc_bst;
	bus_space_handle_t	sc_bsh;
	bus_dma_tag_t		sc_dmat;
	int			sc_phy_id;
	enum genet_phy_mode	sc_phy_mode;

	struct ethercom		sc_ec;
	struct mii_data		sc_mii;
	callout_t		sc_stat_ch;
	kmutex_t		sc_lock;
	kmutex_t		sc_txlock;

	u_short			sc_if_flags;
	bool			sc_txrunning;

	struct genet_ring	sc_tx;
	struct genet_ring	sc_rx;

	krndsource_t		sc_rndsource;
};

int	genet_attach(struct genet_softc *);
int	genet_intr(void *);

#endif /* !_BCMGENETVAR_H */
