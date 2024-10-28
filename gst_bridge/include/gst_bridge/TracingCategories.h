#pragma once

#include <perfetto.h>

PERFETTO_DEFINE_CATEGORIES(
    perfetto::Category("mav")
        .SetDescription("libmav events"),
    perfetto::Category("driver")
        .SetDescription("driver events"),
    perfetto::Category("rosimagesrc")
        .SetDescription("ros src gstreamer plugin"));
