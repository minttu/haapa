#include <stdbool.h>
#include "result.h"
#include "time.h"
#include "haapa.h"
#include "proc.h"
#include "acpi.h"
#include "network.h"
#include "exec.h"
#include "fs.h"
#include "uname.h"
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
