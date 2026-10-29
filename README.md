# MERROW: THE LOST PAGES

A dark-fantasy story game. Long-term target: Unreal Engine 5.6. This repository contains an Unreal C++ foundation and a separate browser-playable prototype.

## Browser prototype

The browser prototype is in \`docs/index.html\`. To publish with GitHub Pages, open **Settings → Pages**, select **Deploy from a branch**, choose branch \`main\` and folder \`/docs\`, then save. It is a separate prototype, not the compiled Unreal game.

## Unreal Engine source

Current systems include the forest blockout and atmosphere director, editor-placeable discovery landmarks, first-person movement/camera, floating lost-page pickups, a HUD, a GameMode, seven-page quest, ancient gate, stamina sprint, and keyboard/gamepad input mappings.

### Current intended first chapter

1. Start in the Ancient Forest clearing.
2. Follow the broken path and collect all seven missing pages.
3. Sprint between discoveries if needed; stamina drains while sprinting and regenerates when walking.
4. Return to the ancient gate behind the starting clearing.
5. Aim at the gate and press E / gamepad bottom face button to open it and complete the prototype chapter.

### Controls

- Keyboard: WASD/arrows to move, mouse to look, E to interact, Left Shift to sprint.
- Gamepad: left stick to move, right stick to look, bottom face button to interact, left-stick click to sprint.

### Build and test

1. Use a compatible Windows development computer with Unreal Engine 5.6 and the C++ build tools installed.
2. Open \`Merrow.uproject\` and compile the editor target.
3. Launch a test level with the configured default GameMode; it spawns the forest, seven pages, and gate.
4. Press Play and test movement, pickups, the gate lock, and the completion state.
5. Fix any compile/runtime issues before treating this as a playable build.

**Important:** The Unreal C++ source has not been compiled or tested in Unreal Editor. The forest, gate, and page use primitive placeholder meshes, and the seven-page chapter is a first gameplay slice rather than the finished story. No packaged Windows/Xbox build exists yet. Xbox packaging/release requires the appropriate platform tooling and access.
