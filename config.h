/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FantasqueSansMono:size=13" };
static const char dmenufont[]       = "FantasqueSansMono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

/* from solarized color scheme */
static const char Base0[]     = "#839496";
static const char Base00[]    = "#657b83";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, Base0,     Base00    },
	// [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#define NOTHING 0

/* custom paths */
#define scripts         "~/.scripts/"
#define screenshots     "~/Pictures/Screenshots/"
#define format_str      "%b%d-%H:%M:%S.png"

/* dwm status bar refresh command */
#define refbar          "; " scripts "refresh_bar.sh"

/* resetting wallpaper */
#define refwall         "; " scripts "set-wallpaper"

/* rofi/dmenu command */
#define roficmd         "j4-dmenu-desktop --dmenu='rofi -dmenu -p Run -theme purple -i'"

/* external screen commands */
#define cycle_monitor   scripts "cycle-monitor.sh"  refwall
#define cycle_audio     scripts "cycle-audio.sh"    refbar

/* miscellaneous commands */
#define lock_pause      scripts "lock-n-pause.sh" refbar
#define bt_on           scripts "bton" refbar
#define change_wall     scripts "change-wallpaper.sh"

/* media commands */
#define media_play      "playerctl play-pause"
#define media_stop      "playerctl stop"
#define media_next      "playerctl next"
#define media_prev      "playerctl previous"

/* volume commands */
#define vol_up          "pactl set-sink-mute @DEFAULT_SINK@ 0 && pactl set-sink-volume @DEFAULT_SINK@ +5%"        refbar
#define vol_down        "pactl set-sink-mute @DEFAULT_SINK@ 0 && pactl set-sink-volume @DEFAULT_SINK@ -5%"        refbar
#define mute            "pactl set-sink-mute @DEFAULT_SINK@ toggle && pactl set-sink-volume @DEFAULT_SINK@ 30%"   refbar

// #define vol_up_ext      "pactl set-sink-mute 2 0 && pactl set-sink-volume 2 +5%"        refbar
// #define vol_down_ext    "pactl set-sink-mute 2 0 && pactl set-sink-volume 2 -5%"        refbar
// #define mute_ext        "pactl set-sink-mute 2 toggle && pactl set-sink-volume 2 30%"   refbar

/* brightness commands */
#define brightness_up   "xbacklight +5"
#define brightness_down "xbacklight -5"

/* screenshot commands */
#define entire_shot     "scrot "                screenshots format_str
#define window_shot     "scrot -u "             screenshots format_str
#define custom_shot     "sleep .2; scrot -s "   screenshots format_str

/* shutdown dialog */
#define shutdown_dialog "~/SimpleShutdownDialog/shutdown-dialog"

/* spotify copy to clipborad current song's link */
#define sp_clip         scripts "sp clip"



#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                 key                        function        argument */
	{ MODKEY,                   XK_Return,                 spawn,          {.v = termcmd } },
	{ MODKEY,                   XK_d,                      spawn,          SHCMD(roficmd) },
    { MODKEY,                   XK_t,                      spawn,          SHCMD(cycle_monitor) },
    { MODKEY,                   XK_y,                      spawn,          SHCMD(cycle_audio) },
    { MODKEY,                   XK_semicolon,              spawn,          SHCMD(lock_pause) },
    { MODKEY,                   XK_n,                      spawn,          SHCMD(bt_on) },
    { MODKEY,                   XK_c,                      spawn,          SHCMD(change_wall) },
    { NOTHING,                  XF86XK_AudioPlay,          spawn,          SHCMD(media_play) },
    { NOTHING,                  XF86XK_AudioStop,          spawn,          SHCMD(media_stop) },
    { NOTHING,                  XF86XK_AudioNext,          spawn,          SHCMD(media_next) },
    { NOTHING,                  XF86XK_AudioPrev,          spawn,          SHCMD(media_prev) },
    { MODKEY,                   XK_slash,                  spawn,          SHCMD(media_play) },
    { MODKEY,                   XK_period,                 spawn,          SHCMD(media_next) },
    { MODKEY,                   XK_comma,                  spawn,          SHCMD(media_prev) },
    { NOTHING,                  XF86XK_AudioRaiseVolume,   spawn,          SHCMD(vol_up) },
    { NOTHING,                  XF86XK_AudioLowerVolume,   spawn,          SHCMD(vol_down) },
    { MODKEY,                   XK_m,                      spawn,          SHCMD(mute) },
    { NOTHING,                  XF86XK_AudioMute,          spawn,          SHCMD(mute) },
    // { ShiftMask,                XF86XK_AudioRaiseVolume,   spawn,          SHCMD(vol_up_ext) },
    // { ShiftMask,                XF86XK_AudioLowerVolume,   spawn,          SHCMD(vol_down_ext) },
    // { ShiftMask,                XF86XK_AudioMute,          spawn,          SHCMD(mute_ext) },
    // { MODKEY|ShiftMask,         XK_m,                      spawn,          SHCMD(mute_ext) },
    { NOTHING,                  XF86XK_MonBrightnessUp,    spawn,          SHCMD(brightness_up) },
    { NOTHING,                  XF86XK_MonBrightnessDown,  spawn,          SHCMD(brightness_down) },
    { MODKEY,                   XK_equal,                  spawn,          SHCMD(brightness_up) },
    { MODKEY,                   XK_minus,                  spawn,          SHCMD(brightness_down) },
    { NOTHING,                  XK_Print,                  spawn,          SHCMD(entire_shot) },
    { MODKEY,                   XK_Print,                  spawn,          SHCMD(window_shot) },
    { ShiftMask,                XK_Print,                  spawn,          SHCMD(custom_shot) },
	{ MODKEY|ShiftMask,         XK_q,                      spawn,          SHCMD(shutdown_dialog) },
    { MODKEY|ShiftMask,         XK_x,                      spawn,          SHCMD(sp_clip) },
    { MODKEY,                   XK_f,                      fullscreen,     {0} },

	{ MODKEY,                   XK_b,          togglebar,      {0} },
	{ MODKEY,                   XK_j,          focusstack,     {.i = +1 } },
	{ MODKEY,                   XK_k,          focusstack,     {.i = -1 } },
	// { MODKEY,                   XK_i,          incnmaster,     {.i = +1 } },
	// { MODKEY,                   XK_p,          incnmaster,     {.i = -1 } },
	{ MODKEY,                   XK_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                   XK_l,          setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,         XK_Return,     zoom,           {0} },
	{ MODKEY,                   XK_Tab,        view,           {0} },
	{ MODKEY,                   XK_q,          killclient,     {0} },
	// { MODKEY,                   XK_t,          setlayout,      {.v = &layouts[0]} },
	// { MODKEY,                   XK_f,          setlayout,      {.v = &layouts[1]} },
	// { MODKEY,                   XK_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                   XK_space,      setlayout,      {0} },
	{ MODKEY|ShiftMask,         XK_space,      togglefloating, {0} },
	{ MODKEY,                   XK_0,          view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,         XK_0,          tag,            {.ui = ~0 } },
	// { MODKEY,                   XK_comma,      focusmon,       {.i = -1 } },
	// { MODKEY,                   XK_period,     focusmon,       {.i = +1 } },
	// { MODKEY|ShiftMask,         XK_comma,      tagmon,         {.i = -1 } },
	// { MODKEY|ShiftMask,         XK_period,     tagmon,         {.i = +1 } },
	TAGKEYS(                    XK_1,                          0)
	TAGKEYS(                    XK_2,                          1)
	TAGKEYS(                    XK_3,                          2)
	TAGKEYS(                    XK_4,                          3)
	TAGKEYS(                    XK_5,                          4)
	TAGKEYS(                    XK_6,                          5)
	TAGKEYS(                    XK_7,                          6)
	TAGKEYS(                    XK_8,                          7)
	TAGKEYS(                    XK_9,                          8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
