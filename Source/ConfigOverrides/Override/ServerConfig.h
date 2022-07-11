#pragma once

///////////////////////////////////////////////////////////////////////////////
// Note: This file overrides the engine's default ServerLib/Config.h.
///////////////////////////////////////////////////////////////////////////////

#include "SharedConfig.h"
#include "ConstexprTools.h"
#include <SDL_stdinc.h>
#include <string>

namespace AM
{
namespace Server
{
/**
 * Contains configuration constants relevant to the Server.
 *
 * Note: When you update the engine, you may need to add additional fields
 *       here. Refer to the engine's default ServerLib/Config.h.
 */
class Config
{
public:
    //-------------------------------------------------------------------------
    // Network
    //-------------------------------------------------------------------------
    ////////////////////////////////////////////////////////////////////////////
    // A tick diff is the difference between a message's intended tick and our
    // current tick (a positive diff means the client is ahead of the server).
    //
    // Client connection management works as such:
    // 1. If the client is too far ahead or behind, send an adjustment.
    //    (TICKDIFF config entries mostly relate to this.)
    //
    // 2. If a single tickdiff is lower than TICKDIFF_ACCEPTABLE_BOUND_LOWER
    //    or higher than TICKDIFF_ACCEPTABLE_BOUND_UPPER, disconnect them.
    //
    // 3. If we haven't received data from the client within CLIENT_TIMEOUT_S
    //    seconds, disconnect them.
    ////////////////////////////////////////////////////////////////////////////

    /** The maximum number of clients that we will allow. */
    static constexpr unsigned int MAX_CLIENTS{1010};

    /** How long we should wait before considering the client to be timed out.
        Arbitrarily chosen. If too high, we set ourselves up to take a huge
       spike of data for a very late client. */
    static constexpr double CLIENT_TIMEOUT_S{1.5};

    /** The minimum amount of time worth of tick differences that we'll
        remember. */
    static constexpr double TICKDIFF_HISTORY_S{.5};
    /** The integer number of diffs that we'll remember in the history. */
    static constexpr unsigned int TICKDIFF_HISTORY_LENGTH{
        ConstexprTools::ceilInt(TICKDIFF_HISTORY_S
                                / SharedConfig::SIM_TICK_TIMESTEP_S)};

    /** The range of difference (inclusive) between a received message's tickNum
        and our current tickNum that we won't send an adjustment for. */
    static constexpr Sint64 TICKDIFF_ACCEPTABLE_BOUND_LOWER{1};
    static constexpr Sint64 TICKDIFF_ACCEPTABLE_BOUND_UPPER{3};
    /** The value that we'll adjust clients to if they fall outside the bounds.
     */
    static constexpr Sint64 TICKDIFF_TARGET{2};

    /** The minimum number of fresh diffs we'll use to calculate an adjustment.
        Aims to prevent thrashing. */
    static constexpr unsigned int MIN_FRESH_DIFFS{3};
};

} // End namespace Server
} // End namespace AM
