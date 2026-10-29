# MERROW: THE LOST PAGES

A single-player dark-fantasy adventure project targeting **Unreal Engine 5.6**.

## Browser environment preview

A separate, lightweight visual study lives in \`docs/index.html\`. It is **not the game build** and does not replace the Unreal project. It is a quick way to inspect the Ancient Forest layout in a mobile or desktop browser: trees, broken stone path, ruins, sanctuary, and adjustable emerald corruption.

To publish the preview with GitHub Pages, open the repository Settings → Pages, choose **Deploy from a branch**, select \`main\` and the \`/docs\` folder, then save. After GitHub finishes publishing, the preview should be available at:

\`https://noahderuiter2012-netizen.github.io/Merrow---The-Lost-Pages/\`

The preview loads Three.js from a public CDN, so an internet connection is required. It is a visual prototype, not a screenshot or a compiled Unreal scene.

## Current Unreal project foundation

- Unreal project descriptor and C++ game/editor targets.
- \`AMerrowAtmosphereDirector\`: adjustable fog density and colour, blending natural mist toward emerald corruption.
- \`AMerrowForestSceneDirector\`: deterministic Ancient Forest blockout generator using Unreal's built-in primitive meshes as temporary placeholders.
- \`AMerrowDiscoveryLandmark\`: editor-placeable markers for lost-page shrines, lore relics, corruption scars, ancient gates, and boss arenas, with editable clue text and optional page index.

## Build status

The Unreal source files have not been compiled or tested in Unreal Editor. A compatible Unreal Engine 5.6 installation and C++ build toolchain are required to verify compilation and run the game. The browser preview is separate and should not be described as the actual game.

## Story direction

Ancient Magic once helped shape the first life in Merrow. It fell dormant until something awakened it—and a foreign force infected it. A forbidden book was scattered across the land during the corruption. Its missing pages hold clues to the Entity's weakness and a ritual that may defeat it; every required page must be recovered.

The origin of the Corrupted King and its exact relationship to the Entity remain intentionally undecided while the story develops.
