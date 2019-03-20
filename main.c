// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2019 Vasily Khoruzhick <anarsoul@gmail.com>

#include <stdio.h>
#include <stdlib.h>

#include <h5e_parser.h>

int main(int argc, char *argv[])
{
	FILE *in;
	uint8_t buf[H5E_PRESET_SIZE];
	ssize_t s;
	struct h5e_parser_ctx *ctx;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	in = fopen(argv[1], "rb");
	if (!in) {
		fprintf(stderr, "Failed to open %s for read\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	s = fread(buf, sizeof(buf), 1, in);
	if (!s) {
		fprintf(stderr, "Failed to read %ld bytes from %s\n", sizeof(buf), argv[1]);
		exit(EXIT_FAILURE);
	}

	ctx = h5e_parser_init(buf);
	if (!ctx) {
		fprintf(stderr, "Failed to init parser\n");
		exit(EXIT_FAILURE);
	}

	printf("Name: %s\n", h5e_parser_get_preset_name(ctx));

	for (int i = 0; i < H5E_PRESET_MAX_AMP_NUM; i++) {
		struct h5e_preset_amp amp;
		h5e_parser_get_amp(ctx, &amp, i);
		printf("Amp %d: %s\n", i, amp.on ? "on" : "off");
		if (!amp.on)
			continue;
		printf("Amp %d model: %s\n", i, h5e_parser_get_amp_model_name(&amp));
	}

	for (int i = 0; i < H5E_PRESET_MAX_CAB_NUM; i++) {
		struct h5e_preset_cab cab;
		h5e_parser_get_cab(ctx, &cab, i);
		printf("Cab %d: %s\n", i, cab.on ? "on" : "off");
		if (!cab.on)
			continue;
		printf("Cab %d model: %s\n", i, h5e_parser_get_cab_model_name(&cab));
	}

	for (int i = 0; i < H5E_PRESET_MAX_FX_NUM; i++) {
		struct h5e_preset_fx fx;
		h5e_parser_get_fx(ctx, &fx, i);
		printf("FX %d: %s\n", i, fx.on ? "on" : "off");
		if (!fx.on)
			continue;
		printf("FX %d type: %s\n", i, h5e_parser_get_fx_type_name(&fx));
		printf("FX %d model: %s\n", i, h5e_parser_get_fx_model_name(&fx));
	}
}
