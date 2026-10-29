# MERROW: THE LOST PAGES

A dark-fantasy story game. Long-term target: Unreal Engine 5.6. This repository contains an Unreal C++ foundation and a separate browser-playable prototype.

## Browser prototype

The browser prototype is in \`docs/index.html\`. To publish with GitHub Pages, open **Settings → Pages**, select **Deploy from a branch**, choose branch \`main\` and folder \`/docs\`, then save. After Pages deploys, open:

https://noahderuiter2012-netizen.github.io/Merrow---The-Lost-Pages/

It loads Three.js from a public CDN and requires internet. It is a separate prototype, not the compiled Unreal game.

## Unreal Engine source

Current C++ foundation:

- \`AMerrowAtmosphereDirector\`: adjustable fog and emerald-corruption blending.
- \`AMerrowForestSceneDirector\`: deterministic forest blockout using built-in placeholder meshes.
- \`AMerrowDiscoveryLandmark\`: editor-placeable shrine, lore relic, corruption scar, ancient gate, and boss-arena markers.
- \`AMerrowPlayerCharacter\`: first-person camera, WASD movement, mouse look, and forward interaction trace.
- \`AMerrowLostPagePickup\`: floating page actor collectable with E.
- \`AMerrowHUD\`: objective, page count, and interaction prompt.
- \`AMerrowGameMode\`: selects the first-person pawn/HUD and temporarily spawns the forest plus first page for a quick test.
- \`Config/DefaultInput.ini\`: keyboard and basic gamepad mappings.

### First Unreal test

1. Use a compatible Windows development computer with Unreal Engine 5.6 and its C++ build tools.
2. Generate project files/open \`Merrow.uproject\` and compile the editor target.
3. Launch an empty level using the configured \`AMerrowGameMode\`. It temporarily spawns the forest blockout and first page automatically.
4. Press Play. Move with WASD, look with the mouse, aim at the glowing/page placeholder, and press E to collect it.
5. Once this bootstrapped test works, replace temporary auto-spawn with a saved authored map and proper materials/assets.

**Not verified:** this C++ source has not been compiled or run in Unreal Editor. The bootstrapped scene is a greybox, not final art. The page interaction is a first mechanic; the complete seven-page quest, gate completion, save system, enemies, and Corrupted King fight are not implemented in Unreal yet.
