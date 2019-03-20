// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2019 Vasily Khoruzhick <anarsoul@gmail.com>

#ifndef __PARSE_H5E_PRIVATE_H
#define __PARSE_H5E_PRIVATE_H

#define H5E_PRESET_NAME_SIZE 16
#define H5E_PRESET_NAME_OFFSET 0x28

#define H5E_PRESET_AMP_ON_OFFSET(x) (0x58 + (x) * 0x100)
#define H5E_PRESET_AMP_MODEL_OFFSET(x) (0x53 + (x) * 0x100)

#define H5E_PRESET_CAB_ON_OFFSET(x) (0x25b + (x) * 0x100)
#define H5E_PRESET_CAB_MODEL_OFFSET(x) (0x253 + (x) * 0x100)

#define H5E_PRESET_FX_ON_OFFSET(x) (0x45b + (x) * 0x100)
#define H5E_PRESET_FX_TYPE_OFFSET(x) (0x451 + (x) * 0x100)
#define H5E_PRESET_FX_MODEL_OFFSET(x) (0x453 + (x) * 0x100)

struct h5e_parser_ctx {
	uint8_t *data;
	/* Max preset size is 16, +1 for null-terminator */
	char preset_name[H5E_PRESET_NAME_SIZE + 1];
};

#endif
