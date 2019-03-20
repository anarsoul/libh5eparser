// SPDX-License-Identifier: BSD-3-Clause
// Copyright (C) 2019 Vasily Khoruzhick <anarsoul@gmail.com>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "h5e_parser.h"
#include "h5e_parser_priv.h"

struct h5e_parser_ctx *h5e_parser_init(uint8_t *data)
{
	struct h5e_parser_ctx *ctx;

	ctx = malloc(sizeof(*ctx));
	if (!ctx)
		goto exit;

	ctx->data = malloc(H5E_PRESET_SIZE);
	if (!ctx->data)
		goto exit_free_ctx;

	memcpy(ctx->data, data, H5E_PRESET_SIZE);

	return ctx;

exit_free_ctx:
	free(ctx);
exit:
	return NULL;
}

void h5e_parser_exit(struct h5e_parser_ctx *ctx)
{
	free(ctx->data);
	free(ctx);
}

const char *h5e_parser_get_preset_name(struct h5e_parser_ctx *ctx)
{
	memcpy(ctx->preset_name, ctx->data + H5E_PRESET_NAME_OFFSET, H5E_PRESET_NAME_SIZE);
	ctx->preset_name[H5E_PRESET_NAME_SIZE] = 0;

	return (const char *)ctx->preset_name;
}

int h5e_parser_get_amp(struct h5e_parser_ctx *ctx, struct h5e_preset_amp *amp, int idx)
{
	if (!ctx || !amp)
		return -EINVAL;

	if (idx < 0 || idx > 1)
		return -EINVAL;

	amp->on = ctx->data[H5E_PRESET_AMP_ON_OFFSET(idx)];
	amp->model = ctx->data[H5E_PRESET_AMP_MODEL_OFFSET(idx)];

	return 0;
}

int h5e_parser_get_cab(struct h5e_parser_ctx *ctx, struct h5e_preset_cab *cab, int idx)
{
	if (!ctx || !cab)
		return -EINVAL;

	if (idx < 0 || idx > 1)
		return -EINVAL;

	cab->on = ctx->data[H5E_PRESET_CAB_ON_OFFSET(idx)];
	cab->model = ctx->data[H5E_PRESET_CAB_MODEL_OFFSET(idx)];

	return 0;
}

int h5e_parser_get_fx(struct h5e_parser_ctx *ctx, struct h5e_preset_fx *fx, int idx)
{
	if (!ctx || !fx)
		return -EINVAL;

	if (idx < 0 || idx > 8)
		return -EINVAL;

	fx->on = ctx->data[H5E_PRESET_FX_ON_OFFSET(idx)];
	fx->type = ctx->data[H5E_PRESET_FX_TYPE_OFFSET(idx)];
	fx->model = ctx->data[H5E_PRESET_FX_MODEL_OFFSET(idx)];

	return 0;
}

const char *h5e_parser_get_amp_model_name(struct h5e_preset_amp *amp)
{
	if (!amp)
		return NULL;

	switch (amp->model) {
	case 0x05:
		return "Blackface Dbl Nrm";
	case 0x06:
		return "Blackface Dbl Vib";
	case 0x08:
		return "Highway 100";
	case 0x0E:
		return "Super 0";
	case 0x14:
		return "Gibtone 185";
	case 0x01:
		return "Tweed B-Man Nrm";
	case 0x02:
		return "Tweed B-Man Brt";
	case 0x03:
		return "Blackface 'Lux Nrm";
	case 0x04:
		return "Blackface 'Lux Vib";
	case 0x12:
		return "Divide 9/15";
	case 0x00:
		return "PhD Motorway";
	case 0x10:
		return "Class A-15";
	case 0x11:
		return "Class A-30 TB";
	case 0x09:
		return "Brit J-45 Nrm";
	case 0x0A:
		return "Brit J-45 Brt";
	case 0x55:
		return "Plexi Lead 100 Nrm";
	case 0x58:
		return "Plexi Lead 100 Brt";
	case 0x0C:
		return "Brit P-75 Nrm";
	case 0x0D:
		return "Brit P-75 Brt";
	case 0x15:
		return "Brit J-800";
	case 0x17:
		return "Bomber Uber";
	case 0x0B:
		return "Treadplate";
	case 0x19:
		return "Angel F-Ball";
	case 0x52:
		return "Line 6 Elektrik";
	case 0x5E:
		return "Solo-100 Clean";
	case 0x61:
		return "Solo-100 Crunch";
	case 0x64:
		return "Solo-100 Overdrive";
	case 0x67:
		return "Line 6 Doom";
	case 0x6A:
		return "Line 6 Epic";
	case 0x5B:
		return "Flip Top";

	/* Pre */
	case 0x20:
		return "Blackface Dbl Nrm Pre";
	case 0x21:
		return "Blackface Dbl Vib Pre";
	case 0x23:
		return "Highway 100 Pre";
	case 0x29:
		return "Super 0 Pre";
	case 0x2F:
		return "Gibtone 185 Pre";
	case 0x1C:
		return "Tweed B-Man Nrm Pre";
	case 0x1D:
		return "Tweed B-Man Brt Pre";
	case 0x1E:
		return "Blackface 'Lux Nrm Pre";
	case 0x1F:
		return "Blackface 'Lux Vib Pre";
	case 0x2D:
		return "Divide 9/15 Pre";
	case 0x1B:
		return "PhD Motorway Pre";
	case 0x2B:
		return "Class A-15 Pre";
	case 0x2C:
		return "Class A-30 TB Pre";
	case 0x24:
		return "Brit J-45 Nrm Pre";
	case 0x25:
		return "Brit J-45 Brt Pre";
	case 0x56:
		return "Plexi Lead 100 Nrm Pre";
	case 0x59:
		return "Plexi Lead 100 Brt Pre";
	case 0x27:
		return "Brit P-75 Nrm Pre";
	case 0x28:
		return "Brit P-75 Brt Pre";
	case 0x30:
		return "Brit J-800 Pre";
	case 0x32:
		return "Bomber Uber Pre";
	case 0x26:
		return "Treadplate Pre";
	case 0x34:
		return "Angel F-Ball Pre";
	case 0x53:
		return "Line 6 Elektrik";
	case 0x5F:
		return "Solo-100 Clean Pre";
	case 0x62:
		return "Solo-100 Chrunch Pre";
	case 0x65:
		return "Solo-100 Overdive Pre";
	case 0x68:
		return "Line 6 Doom Pre";
	case 0x6B:
		return "Line 6 Epic Pre";
	case 0x5C:
		return "Flip Top Pre";
	default:
		return "Unknown";
	}
}

const char *h5e_parser_get_cab_model_name(struct h5e_preset_cab *cab)
{
	if (!cab)
		return NULL;

	switch (cab->model) {
	case 0x00:
		return "2x12 PhD Ported";
	case 0x01:
		return "1x(6x9)Super O";
	case 0x02:
		return "1x12 Celest 12-H";
	case 0x03:
		return "1x12 Blackface 'Lux";
	case 0x04:
		return "1x12 Gibtone F-Coil";
	case 0x05:
		return "1x12 Blue Bell";
	case 0x06:
		return "2x12 Blackface Dbl";
	case 0x08:
		return "2x12 Silver Bell";
	case 0x09:
		return "4x10 Tweed B-Man";
	case 0x0A:
		return "4x12 Uber";
	case 0x0B:
		return "4x12 XXL V-30";
	case 0x0C:
		return "4x12 Hiway";
	case 0x0E:
		return "4x12 Greenback 25";
	case 0x11:
		return "4x12 Blackback 30";
	case 0x10:
		return "4x12 Tread V-30";
	case 0x0F:
		return "4x12 Brit T-75";
	case 0x12:
		return "4x12 Flip Top";
	default:
		return "Unknown";
	}
}

const char *h5e_parser_get_fx_type_name(struct h5e_preset_fx *fx)
{
	switch (fx->type) {
	case 0x0:
		return "Dyn";
	case 0x5:
		return "Dist";
	case 0x3:
		return "Mod";
	case 0xa:
		return "Filter";
	case 0x9:
		return "Pitch";
	case 0xc:
		return "Pre+EQ";
	case 0x2:
		return "Delay";
	case 0x4:
		return "Reverb";
	case 0x7:
		return "VolPan";
	case 0x6:
		return "Wah";
	case 0x8:
		return "FXLoop";

	default:
		return "Unknown";
	}
}

static const char *h5e_parset_get_fx_dyn_model(struct h5e_preset_fx *fx)
{
	switch (fx->model) {
	case 0x11:
		return "Noise Gate";
	case 0x13:
		return "Hard Gate";
	case 0x0E:
		return "Tube Comp";
	case 0x0B:
		return "Red Comp";
	case 0x0C:
		return "Blue Comp";
	case 0x0D:
		return "Blue Comp Treb";
	case 0x0F:
		return "Vetta Comp";
	case 0x10:
		return "Vetta Juice";
	case 0x12:
		return "Boost Comp";
	default:
		return "Unknown";
	}
}

static const char *h5e_parset_get_fx_dist_model(struct h5e_preset_fx *fx)
{
	switch (fx->model) {
	case 0x0D:
		return "Tube Drive";
	case 0x0E:
		return "Screamer";
	case 0x10:
		return "Overdrive";
	case 0x0B:
		return "Classic Distortion";
	case 0x16:
		return "Heavy Distorion";
	case 0x18:
		return "Color Drive";
	case 0x15:
		return "Buzz Saw";
	case 0x11:
		return "Facial Fuzz";
	case 0x17:
		return "Jumbo Fuzz";
	case 0x0F:
		return "Fuzz Pi";
	case 0x0A:
		return "Jet Fuzz";
	case 0x13:
		return "Line 6 Drive";
	case 0x12:
		return "Line 6 Distortion";
	case 0x14:
		return "Sub Octave Fuzz";
	case 0x0C:
		return "Octave Fuzz";
	default:
		return "Unknown";
	}
}

static const char *h5e_parset_get_fx_mod_model(struct h5e_preset_fx *fx)
{
	switch (fx->model) {
	case 0x43:
		return "Pattern Tremolo";
	case 0x2F:
		return "Panner";
	case 0x21:
		return "Bias Tremolo";
	case 0x20:
		return "Opto Tremolo";
	case 0x45:
		return "Script Phase";
	case 0x24:
		return "Panned Phaser";
	case 0x40:
		return "Barberpole Phaser";
	case 0x23:
		return "Dual Phaser";
	case 0x25:
		return "U-Vibe";
	case 0x22:
		return "Phaser";
	case 0x2D:
		return "Pitch Vibrato";
	case 0x2B:
		return "Dimension";
	case 0x2A:
		return "Analog Chorus";
	case 0x2C:
		return "Tri Chorus";
	case 0x28:
		return "Analog Flanger";
	case 0x29:
		return "Jet Flanger";
	case 0x47:
		return "AC Flanger";
	case 0x49:
		return "80A Flanger";
	case 0x42:
		return "Frequency Shifter";
	case 0x2E:
		return "Ring Modulator";
	case 0x26:
		return "Rotary Drum";
	case 0x27:
		return "Rotary Dum & Horn";
	default:
		return "Unknown";
	}
}

static const char *h5e_parset_get_fx_filter_model(struct h5e_preset_fx *fx)
{
	switch (fx->model) {
	case 0x1D:
		return "Voice Box";
	case 0x1E:
		return "V-Tron";
	case 0x14:
		return "Q-Filter";
	case 0x26:
		return "Vocoder";
	case 0x11:
		return "Seeker";
	case 0x12:
		return "Obi Wah";
	case 0x0F:
		return "Tron Up";
	case 0x10:
		return "Tron Down";
	case 0x15:
		return "Throbber";
	case 0x13:
		return "Slow Filter";
	case 0x16:
		return "Spin Cycle";
	case 0x17:
		return "Comet Trails";
	case 0x18:
		return "Octisynth";
	case 0x1A:
		return "Synth-O-Matic";
	case 0x1B:
		return "Attack Synth";
	case 0x1C:
		return "Synth String";
	case 0x19:
		return "Growler";
	default:
		return "Unknown";
	}
}

static const char *h5e_parset_get_fx_pitch_model(struct h5e_preset_fx *fx)
{
	switch (fx->model) {
	case 0x04:
		return "Bass Octaver";
	case 0x02:
		return "Pitch Glide";
	case 0x03:
		return "Smart Harmony";
	default:
		return "Unknown";
	}
}

static const char *h5e_parset_get_fx_pre_eq_model(struct h5e_preset_fx *fx)
{
	switch (fx->model) {
	case 0x09:
		return "Graphic EQ";
	case 0x0B:
		return "Parametric EQ";
	case 0x0A:
		return "Studio EQ";
	case 0x0C:
		return "4-Band Shift EQ";
	case 0x0D:
		return "Mid Focus EQ";
	case 0x0E:
		return "Vintage Pre";
	default:
		return "Unknown";
	}
}

static const char *h5e_parset_get_fx_delay_model(struct h5e_preset_fx *fx)
{
	switch (fx->model) {
	case 0x20:
		return "Ping Pong";
	case 0x22:
		return "Dynamic Delay";
	case 0x13:
		return "Stereo Delay";
	case 0x11:
		return "Digital Delay";
	case 0x12:
		return "Digital Delay w/Mod";
	case 0x21:
		return "Reverse Delay";
	case 0x1D:
		return "Lo Res Delay";
	case 0x2A:
		return "Tube Echo";
	case 0x2B:
		return "Tube Echo Dry";
	case 0x2C:
		return "Tape Echo";
	case 0x2D:
		return "Tape Echo Dry";
	case 0x2E:
		return "Sweep Echo";
	case 0x2F:
		return "Sweep Echo Dry";
	case 0x30:
		return "Echo Platter";
	case 0x31:
		return "Echo Platter Dry";
	case 0x15:
		return "Analog Delay w/Mod";
	case 0x14:
		return "Analog Echo";
	case 0x23:
		return "Auto-Volume";
	case 0x1A:
		return "Multi-Head Delay";
	default:
		return "Unknown";
	}
}

static const char *h5e_parset_get_fx_reverb_model(struct h5e_preset_fx *fx)
{
	switch (fx->model) {
	case 0x1E:
		return "Plate";
	case 0x1F:
		return "Room";
	case 0x20:
		return "Chamber";
	case 0x21:
		return "Hall";
	case 0x26:
		return "Echo";
	case 0x25:
		return "Tile";
	case 0x24:
		return "Cave";
	case 0x22:
		return "Ducking";
	case 0x23:
		return "Octo";
	case 0x1D:
		return "Spring";
	case 0x1C:
		return "'63 Spring";
	case 0x27:
		return "Particle Verb";
	default:
		return "Unknown";
	}
}

static const char *h5e_parset_get_fx_volpan_model(struct h5e_preset_fx *fx)
{
	switch (fx->model) {
	case 0x04:
		return "Volume Pedal";
	case 0x05:
		return "Pan";
	default:
		return "Unknown";
	}
}

static const char *h5e_parset_get_fx_wah_model(struct h5e_preset_fx *fx)
{
	switch (fx->model) {
	case 0x0C:
		return "Fassel";
	case 0x11:
		return "Conductor";
	case 0x10:
		return "Throaty";
	case 0x12:
		return "Colorful";
	case 0x0B:
		return "Vetta Wah";
	case 0x0E:
		return "Chrome";
	case 0x0F:
		return "Chrome Custom";
	case 0x0D:
		return "Wheeper";
	default:
		return "Unknown";
	}
}

static const char *h5e_parset_get_fx_loop_model(struct h5e_preset_fx *fx)
{
	switch (fx->model) {
	case 0x00:
		return "FXLoop";
	default:
		return "Unknown";
	}
}

const char *h5e_parser_get_fx_model_name(struct h5e_preset_fx *fx)
{
	if (!fx)
		return NULL;

	switch (fx->type) {
	case 0x0:
		// Dyn
		return h5e_parset_get_fx_dyn_model(fx);
	case 0x5:
		// Dist
		return h5e_parset_get_fx_dist_model(fx);
	case 0x3:
		// Mod
		return h5e_parset_get_fx_mod_model(fx);
	case 0xa:
		// Filter
		return h5e_parset_get_fx_filter_model(fx);
	case 0x9:
		// Pitch
		return h5e_parset_get_fx_pitch_model(fx);
	case 0xc:
		// Pre+EQ
		return h5e_parset_get_fx_pre_eq_model(fx);
	case 0x2:
		// Delay
		return h5e_parset_get_fx_delay_model(fx);
	case 0x4:
		// Reverb
		return h5e_parset_get_fx_reverb_model(fx);
	case 0x7:
		// VolPan
		return h5e_parset_get_fx_volpan_model(fx);
	case 0x6:
		// Wah
		return h5e_parset_get_fx_wah_model(fx);
	case 0x8:
		// FXLoop
		return h5e_parset_get_fx_loop_model(fx);

	default:
		return "Unknown";
	}
}
