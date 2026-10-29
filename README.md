# MERROW: THE LOST PAGES

A dark-fantasy story game project. The long-term target is Unreal Engine 5.6; the browser version below is an independently playable prototype.

## Play the browser prototype

The playable prototype is in \`docs/index.html\`. To publish it with GitHub Pages:

1. Open repository **Settings → Pages**.
2. Under **Build and deployment**, choose **Deploy from a branch**.
3. Select branch \`main\` and folder \`/docs\`, then save.
4. Wait for GitHub Pages to finish deploying, then open:
   https://noahderuiter2012-netizen.github.io/Merrow---The-Lost-Pages/

The prototype loads Three.js from a public CDN, so it requires an internet connection. Desktop controls: WASD/arrow keys, mouse to look, E to interact. Touch devices: left joystick to move, drag the right side to look, and use the on-screen interaction button.

### Current playable slice

- First-person movement and camera.
- Dark forest environment with trees, rocks, a broken stone path, ruins, crystals, and an ancient gate.
- Shrine with a glowing missing page.
- Quest state: find the page, then return to the gate to complete the chapter.
- Responsive mobile touch controls and optional generated ambient drone.

This is a small gameplay prototype, not the full story and not the compiled Unreal game. It has not yet been tested on every device/browser.

## Unreal Engine project foundation

- Unreal project descriptor and C++ game/editor targets.
- \`AMerrowAtmosphereDirector\`: adjustable fog density and colour, blending natural mist toward emerald corruption.
- \`AMerrowForestSceneDirector\`: deterministic Ancient Forest blockout generator using Unreal's built-in primitive meshes as temporary placeholders.
- \`AMerrowDiscoveryLandmark\`: editor-placeable markers for lost-page shrines, lore relics, corruption scars, ancient gates, and boss arenas, with editable clue text and optional page index.

The Unreal C++ source has not been compiled or tested in Unreal Editor. A compatible Unreal Engine 5.6 installation and C++ build toolchain are required to verify and package that version.

## Story direction

A forbidden book was scattered across Merrow when corruption arrived. Its missing pages hold clues to the Entity's weakness and a ritual that may defeat it; every required page must be recovered. The origin of the Corrupted King and its exact relationship to the Entity remain under development.
