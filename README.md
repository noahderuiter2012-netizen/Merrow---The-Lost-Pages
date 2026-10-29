# MERROW: THE LOST PAGES

A dark-fantasy story game. Long-term target: Unreal Engine 5.6. This repository contains an Unreal C++ foundation and a separate browser-playable prototype.

## Browser prototype

The browser prototype is in \`docs/index.html\`. To publish with GitHub Pages, open **Settings → Pages**, select **Deploy from a branch**, choose branch \`main\` and folder \`/docs\`, then save. It is a separate prototype, not the compiled Unreal game.

## Unreal Engine source

Current systems include the forest blockout and atmosphere director, editor-placeable discovery landmarks, first-person movement/camera, floating lost-page pickups, a simple HUD, a GameMode, and a basic ancient gate.

### Current intended first chapter

1. Start in the Ancient Forest clearing.
2. Follow the broken path and collect all seven missing pages.
3. Return to the ancient gate behind the starting clearing.
4. Aim at the gate and press E to open it; the HUD shows a chapter-complete state.

### Build and test

1. Use a compatible Windows development computer with Unreal Engine 5.6 and the C++ build tools installed.
2. Open \`Merrow.uproject\` and compile the editor target.
3. Launch an empty test level with the configured default GameMode; it should spawn the forest, seven pages, and gate.
4. Press Play. Use WASD to move, mouse to look, and E to interact.
5. Fix any compile/runtime issues before treating this as a playable build.

**Important:** The Unreal C++ source has not been compiled or tested in Unreal Editor. The forest and gate use primitive placeholder meshes, and the seven-page chapter is a first gameplay slice rather than the finished story. No packaged Windows/Xbox build exists yet. Xbox packaging and release require the appropriate platform tooling and access.
