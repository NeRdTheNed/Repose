#pragma once

#include <cstddef>

///////////////////////////////////////////////////////////////////////////////
// Note: This file overrides the engine's default SharedConfig.h.
///////////////////////////////////////////////////////////////////////////////
namespace AM
{
/**
 * Contains shared configuration constants that must be consistent between the
 * client, server, and sprite editor.
 *
 * Note: When you update the engine, you may need to add additional fields
 *       here. Refer to the engine's default SharedConfig.h.
 */
class SharedConfig
{
public:
    //-------------------------------------------------------------------------
    // Simulation
    //-------------------------------------------------------------------------
    /** The rate at which the simulation will be processed. */
    static constexpr unsigned int SIM_TICKS_PER_SECOND{30};
    static constexpr double SIM_TICK_TIMESTEP_S{
        1.0 / static_cast<double>(SIM_TICKS_PER_SECOND)};

    /** The max number of entities that we will allow. */
    static constexpr std::size_t MAX_ENTITIES{200};

    /** The x and y axis width, in world units, of our tiles. */
    static constexpr unsigned int TILE_WORLD_WIDTH{32};

    /** The x and y axis width, in tiles, of our chunks. */
    static constexpr unsigned int CHUNK_WIDTH{16};

    /** The number of tiles in a chunk. */
    static constexpr unsigned int CHUNK_TILE_COUNT{CHUNK_WIDTH * CHUNK_WIDTH};

    /** The x and y axis width, in tiles, of a cell in our spatial
        partitioning grid.
        Note: The map's size must be evenly divisible by this number. */
    static constexpr unsigned int CELL_WIDTH{4};

    /** The number of world units around an entity that are considered to be
        within the entity's "Area of Interest".
        Used in the simulation to tell if data is relevant to a client. */
    static constexpr float AOI_RADIUS{TILE_WORLD_WIDTH * 8};

    /** The squared AOI radius. Useful for checking if things are in range
        of an entity without doing a square root. */
    static constexpr float AOI_RADIUS_SQUARED{AOI_RADIUS * AOI_RADIUS};

    /** The maximum number of sprite layers a tile can have. */
    static constexpr std::size_t MAX_TILE_LAYERS{5};

    /** The string ID of the default sprite for character entities.
        This is the sprite that players and NPCs get assigned before the
        project's animation system gives them their real sprite.

        Note: This sprite's bounding box acts as the "standard collision" for
              all characters. Their Collision component will be set to this
              sprite's box, and will remain even if their sprite changes.
              However, your project may choose to set the Collision component
              to something else. */
    static constexpr const char* DEFAULT_CHARACTER_SPRITE{"ghost_south"};

    /** The speed that entities will move at. Eventually we'll support
        dynamically setting this based on stats, for now it's a constant. */
    static constexpr float MOVEMENT_VELOCITY{50};

    //-------------------------------------------------------------------------
    // Network
    //-------------------------------------------------------------------------
    /** The rate at which the network will send queued messages, or a heartbeat
        if no messages are queued. */
    static constexpr unsigned int NETWORK_TICKS_PER_SECOND{20};
    static constexpr double NETWORK_TICK_TIMESTEP_S{
        1.0 / static_cast<double>(NETWORK_TICKS_PER_SECOND)};

    /** Message batches larger than this size (in bytes) will be compressed
        before sending. */
    static constexpr std::size_t BATCH_COMPRESSION_THRESHOLD{50};

    /** The "level" value passed to zlib's compression function when
        compressing message batches.
        Can be 0 - 9, with 0 being no compression, 1 being fastest, and 9 being
        most compressed. 6 is the default. */
    static constexpr int BATCH_COMPRESSION_LEVEL{9};

    /** The max size that an uncompressed message batch can be.
        Used to allocate our message buffers.

        If it was free, we would just send the actual uncompressed size of
        each message batch over the wire. To save bytes, we instead configure
        this constant.
        Our message buffers are very small relative to available RAM, so there
        isn't much harm in raising this to be well above what we actually need.

        Note: Each simulated client in LoadTestClient instantiates a buffer,
              so you may need to be conscious of this size in that case. */
    static constexpr std::size_t MAX_BATCH_SIZE{20'000};

    //-------------------------------------------------------------------------
    // Renderer
    //-------------------------------------------------------------------------
    /** The width of a tile in screen coordinates. */
    static constexpr unsigned int TILE_SCREEN_WIDTH{256};
    /** The height of the top face of a tile in screen coordinates. */
    static constexpr unsigned int TILE_SCREEN_HEIGHT{128};

    /** The total width of a standard tile sprite. */
    static constexpr unsigned int TILE_SPRITE_WIDTH{256};
    /** The total height of a standard tile sprite. */
    static constexpr unsigned int TILE_SPRITE_HEIGHT{512};

    // Note: This solution is temporary. Eventually, the Tile concept will be
    //       replaced with 3D Blocks and this value will be derivable like the
    //       others.
    /** The value used to scale world Z-axis units to screen Y-axis units. */
    static constexpr float Z_SCREEN_SCALE{2.f};

    /** The number of world units around the player that are considered to be
        within the player's view range.
        Used to determine how much of the world should be rendered. */
    static constexpr float VIEW_RADIUS{TILE_WORLD_WIDTH * 8};

    //-------------------------------------------------------------------------
    // Project
    //-------------------------------------------------------------------------
    /** If true, tile changes will only be allowed in the "build area".
        If false, clients can change any tile in the map. */
    static constexpr bool RESTRICT_TILE_UPDATES{true};
};

} // End namespace AM
