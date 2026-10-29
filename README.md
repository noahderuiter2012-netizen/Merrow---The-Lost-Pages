# MERROW: THE LOST PAGES

A dark-fantasy story game. Long-term target: Unreal Engine 5.6. This repository contains both an Unreal C++ foundation and a separate browser-playable prototype.

## Browser prototype

The browser prototype is in \`docs/index.html\`. To publish with GitHub Pages, open **Settings → Pages**, select **Deploy from a branch**, choose branch \`main\` and folder \`/docs\`, then save. After Pages deploys, open:

https://noahderuiter2012-netizen.github.io/Merrow---The-Lost-Pages/

The browser version is a small separate prototype. It loads Three.js from a public CDN and needs an internet connection. It is not the compiled Unreal game.

## Unreal Engine source

The C++ project foundation currently includes:

- \`AMerrowAtmosphereDirector\`: adjustable fog and emerald-corruption blending.
- \`AMerrowForestSceneDirector\`: deterministic forest blockout generation using built-in placeholder meshes.
- \`AMerrowDiscoveryLandmark\`: editor-placeable shrine, lore relic, corruption scar, ancient gate, and boss-arena markers.
- \`AMerrowPlayerCharacter\`: first-person camera, WASD movement, mouse look, and forward interaction trace.
- \`AMerrowLostPagePickup\`: floating page actor that can be collected with E.
- \`AMerrowHUD\`: objective, page count, and interaction prompt.
- \`AMerrowGameMode\`: selects the first-person pawn and HUD.
- \`Config/DefaultInput.ini\`: keyboard and basic gamepad input mappings.

### Setting up the first Unreal playable slice

1. Use a compatible Windows development computer with Unreal Engine 5.6 and its C++ build tools installed.
2. Generate project files/open \`Merrow.uproject\` and compile the editor target.
3. Create and save an Unreal level, add a floor and an \`AMerrowForestSceneDirector\` actor, and configure the generator.
4. Add an \`AMerrowLostPagePickup\` actor where the first page should be placed.
5. Set the level's GameMode override to \`AMerrowGameMode\` (or configure it in Project Settings).
6. Press Play. The player should spawn, move with WASD, look with the mouse, and press E while aiming at the page to collect it.

The C++ code has **not been compiled or run in Unreal yet**. The steps above describe the intended setup, not a verified successful build. This source milestone does not yet include a finished map asset, title menu, save system, complete quest chain, enemies, or boss encounter.

## Story direction

A forbidden book was scattered across Merrow when corruption arrived. Its missing pages contain clues to the Entity's weakness and a ritual that may defeat it; every required page must be recovered. The Corrupted King is a major threat, but its exact connection to the Entity remains under development.
