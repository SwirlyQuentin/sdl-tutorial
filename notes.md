# SDL Game Engine Topics

## 1. Window & Renderer
- Creating and managing an SDL window
- Using SDL_Renderer for GPU-accelerated 2D rendering
- Clearing and presenting frames
- Handling fullscreen, resizing, vsync, etc.

## 2. Event / Input System
- Using `SDL_Event` to capture input
- Keyboard, mouse, controller events
- Polling vs. waiting for events
- Building an abstraction layer for your engine

## 3. Textures & Sprites
- Loading images (PNG, JPG) with SDL_image
- Creating `SDL_Texture` objects
- Rendering parts of textures (sprite sheets)
- Transformations: scale, rotation, flip

## 4. Timing & Frame Rate Control
- Using `SDL_GetTicks` or `SDL_GetPerformanceCounter`
- Delta time calculation (`dt`)
- Frame limiting or vsync
- Fixed timestep vs variable timestep

## 5. Audio (SDL_mixer)
- Initializing the audio subsystem
- Loading & playing sound effects / music
- Managing channels
- Volume control and audio mixing

## 6. Files & Loading
- Using SDL_RWops for platform-independent file I/O
- Loading resources (JSON, images, audio)
- Creating an asset manager
- Abstracting OS paths

## 7. Optional: OpenGL / Vulkan Backend
- Creating an SDL window with an OpenGL/Vulkan context
- Writing a custom renderer (instead of SDL_Renderer)
- Rendering 3D or advanced 2D
- Decoupling the rendering API from the engine core
