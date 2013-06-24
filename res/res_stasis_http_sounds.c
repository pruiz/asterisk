/*
 * Asterisk -- An open source telephony toolkit.
 *
 * Copyright (C) 2012 - 2013, Digium, Inc.
 *
 * David M. Lee, II <dlee@digium.com>
 *
 * See http://www.asterisk.org for more information about
 * the Asterisk project. Please do not directly contact
 * any of the maintainers of this project for assistance;
 * the project provides a web site, mailing lists and IRC
 * channels for your use.
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */

/*
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * !!!!!                               DO NOT EDIT                        !!!!!
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * This file is generated by a mustache template. Please see the original
 * template in rest-api-templates/res_stasis_http_resource.c.mustache
 */

/*! \file
 *
 * \brief Sound resources
 *
 * \author David M. Lee, II <dlee@digium.com>
 */

/*** MODULEINFO
	<depend type="module">res_stasis_http</depend>
	<depend type="module">res_stasis</depend>
	<support_level>core</support_level>
 ***/

#include "asterisk.h"

ASTERISK_FILE_VERSION(__FILE__, "$Revision$")

#include "asterisk/module.h"
#include "asterisk/stasis_app.h"
#include "stasis_http/resource_sounds.h"

/*!
 * \brief Parameter parsing callback for /sounds.
 * \param get_params GET parameters in the HTTP request.
 * \param path_vars Path variables extracted from the request.
 * \param headers HTTP headers.
 * \param[out] response Response to the HTTP request.
 */
static void stasis_http_get_sounds_cb(
    struct ast_variable *get_params, struct ast_variable *path_vars,
    struct ast_variable *headers, struct stasis_http_response *response)
{
	struct ast_get_sounds_args args = {};
	struct ast_variable *i;

	for (i = get_params; i; i = i->next) {
		if (strcmp(i->name, "lang") == 0) {
			args.lang = (i->value);
		} else
		if (strcmp(i->name, "format") == 0) {
			args.format = (i->value);
		} else
		{}
	}
	stasis_http_get_sounds(headers, &args, response);
}
/*!
 * \brief Parameter parsing callback for /sounds/{soundId}.
 * \param get_params GET parameters in the HTTP request.
 * \param path_vars Path variables extracted from the request.
 * \param headers HTTP headers.
 * \param[out] response Response to the HTTP request.
 */
static void stasis_http_get_stored_sound_cb(
    struct ast_variable *get_params, struct ast_variable *path_vars,
    struct ast_variable *headers, struct stasis_http_response *response)
{
	struct ast_get_stored_sound_args args = {};
	struct ast_variable *i;

	for (i = path_vars; i; i = i->next) {
		if (strcmp(i->name, "soundId") == 0) {
			args.sound_id = (i->value);
		} else
		{}
	}
	stasis_http_get_stored_sound(headers, &args, response);
}

/*! \brief REST handler for /api-docs/sounds.{format} */
static struct stasis_rest_handlers sounds_soundId = {
	.path_segment = "soundId",
	.is_wildcard = 1,
	.callbacks = {
		[AST_HTTP_GET] = stasis_http_get_stored_sound_cb,
	},
	.num_children = 0,
	.children = {  }
};
/*! \brief REST handler for /api-docs/sounds.{format} */
static struct stasis_rest_handlers sounds = {
	.path_segment = "sounds",
	.callbacks = {
		[AST_HTTP_GET] = stasis_http_get_sounds_cb,
	},
	.num_children = 1,
	.children = { &sounds_soundId, }
};

static int load_module(void)
{
	stasis_app_ref();
	return stasis_http_add_handler(&sounds);
}

static int unload_module(void)
{
	stasis_http_remove_handler(&sounds);
	stasis_app_unref();
	return 0;
}

AST_MODULE_INFO(ASTERISK_GPL_KEY, AST_MODFLAG_DEFAULT, "RESTful API module - Sound resources",
	.load = load_module,
	.unload = unload_module,
	.nonoptreq = "res_stasis_http,res_stasis",
	);
