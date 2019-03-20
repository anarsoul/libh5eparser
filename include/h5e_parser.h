// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2019 Vasily Khoruzhick <anarsoul@gmail.com>

#ifndef __PARSE_H5E_H
#define __PARSE_H5E_H

#include <stdint.h>
#include <stdbool.h>

#define H5E_PRESET_SIZE 4136
#define H5E_PRESET_MAX_AMP_NUM 2
#define H5E_PRESET_MAX_CAB_NUM 2
#define H5E_PRESET_MAX_FX_NUM 8

struct h5e_parser_ctx;

struct h5e_preset_amp {
	bool on;
	uint8_t model;
};

struct h5e_preset_cab {
	bool on;
	uint8_t model;
};

struct h5e_preset_fx {
	bool on;
	uint8_t type;
	uint8_t model;
};

struct h5e_parser_ctx *h5e_parser_init(uint8_t *blob);
void h5e_parser_exit(struct h5e_parser_ctx *ctx);
const char *h5e_parser_get_preset_name(struct h5e_parser_ctx *ctx);

int h5e_parser_get_amp(struct h5e_parser_ctx *ctx, struct h5e_preset_amp *amp, int idx);
const char *h5e_parser_get_amp_model_name(struct h5e_preset_amp *amp);

int h5e_parser_get_cab(struct h5e_parser_ctx *ctx, struct h5e_preset_cab *cab, int idx);
const char *h5e_parser_get_cab_model_name(struct h5e_preset_cab *cab);

int h5e_parser_get_fx(struct h5e_parser_ctx *ctx, struct h5e_preset_fx *fx, int idx);

const char *h5e_parser_get_fx_type_name(struct h5e_preset_fx *fx);
const char *h5e_parser_get_fx_model_name(struct h5e_preset_fx *fx);

#endif
