/*
 * Copyright 2007 Josh Kropf
 * 
 * This file is part of Lemon Launcher.
 * 
 * Lemon Launcher is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * Lemon Launcher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Lemon Launcher; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "options.h"
#include "error.h"

#include <stdio.h>
#include <string>
#include <iostream>

namespace ll { options g_opts; }

using namespace ll;
using namespace std;

options::options() : _cfg(NULL) { }

void options::load(const char* conf_dir)
{
   _conf_dir = (char*)conf_dir;
   
   cfg_opt_t opts[] = {
      CFG_INT(KEY_LOGLEVEL, 2, CFGF_NONE),
      
      CFG_INT(KEY_SCREEN_WIDTH, 0, CFGF_NODEFAULT),
      CFG_INT(KEY_SCREEN_HEIGHT, 0, CFGF_NODEFAULT),
      CFG_INT(KEY_SCREEN_BPP, 0, CFGF_NODEFAULT),
      CFG_BOOL(KEY_FULLSCREEN, cfg_false, CFGF_NONE),
      
      CFG_STR(KEY_FONT_FILE, 0, CFGF_NODEFAULT),
      CFG_INT(KEY_TITLE_HEIGHT, 40, CFGF_NONE),
      CFG_INT(KEY_TITLE_COLOR, 0xefefef, CFGF_NONE),
      CFG_INT(KEY_LIST_HEIGHT, 30, CFGF_NONE),
      CFG_INT(KEY_MENU_COLOR, 0xc2f4ff, CFGF_NONE),
      CFG_INT(KEY_MENU_HOVER_COLOR, 0x32E4ff, CFGF_NONE),
      CFG_INT(KEY_GAME_COLOR, 0xefefef, CFGF_NONE),
      CFG_INT(KEY_GAME_HOVER_COLOR, 0xffe432, CFGF_NONE),
      CFG_INT(KEY_SNAPSHOT_ALPHA, 0xc8, CFGF_NONE),
      CFG_INT(KEY_SNAPSHOT_DELAY, 500, CFGF_NONE),
      CFG_INT(KEY_PAGE_SIZE, 15, CFGF_NONE),
      
      CFG_STR(KEY_MAME_PATH, 0, CFGF_NODEFAULT),
      CFG_STR(KEY_MAME_PARAMS, "", CFGF_NONE),
      CFG_STR(KEY_MAME_SNAPS_PATH, "", CFGF_NONE),
      
      CFG_INT(KEY_KEYCODE_EXIT, 27, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_SNAP, 49, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_RELOAD, 50, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_TOGGLE, 51, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_P1_UP, 273, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_P1_DOWN, 274, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_P1_PGUP, 275, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_P1_PGDOWN, 276, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_P1_BTN1, 306, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_P1_BTN2, 306, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_P2_UP, 114, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_P2_DOWN, 102, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_P2_PGUP, 100, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_P2_PGDOWN, 103, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_P2_BTN1, 97, CFGF_NONE),
      CFG_INT(KEY_KEYCODE_P2_BTN2, 119, CFGF_NONE),
      CFG_END()
   };
   
   string path(_conf_dir);
   path.append("/lemonlauncher.conf");
   
   _cfg = cfg_init(opts, CFGF_NONE);
   int result = cfg_parse(_cfg, path.c_str());
   
   if (result == CFG_FILE_ERROR) {
      perror(path.c_str());
      throw bad_lemon("options: file error");
   } else if (result == CFG_PARSE_ERROR) {
      throw bad_lemon("options: parse error");
   }
}

options::~options()
{ cfg_free(_cfg); }

bool options::get_bool(const char* key) const
{ return cfg_getbool(_cfg, key) == cfg_true; }

int options::get_int(const char* key) const
{ return cfg_getint(_cfg, key); }

const char* options::get_string(const char* key) const
{ return cfg_getstr(_cfg, key); }
