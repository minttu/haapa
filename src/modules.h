#include <stdbool.h>
#include "result.h"
#include "time.h"
#include "haapa.h"
#include "proc.h"
#include "battery.h"
#include "network.h"
#ifdef INCLUDE_MPD
#include "mpd.h"
#endif
#ifdef INCLUDE_IWLIB
#include "wireless.h"
#endif
#ifdef INCLUDE_ALSA
#include "alsa.h"
#endif
#include "config.h"
